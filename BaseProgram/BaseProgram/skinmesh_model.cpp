//=============================================================================
//
// モデルクラス [model.cpp]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "skinmesh_model.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"
#include "model_info.h"
#include "skinmesh.h"
#include "animation_skinmesh.h"
#include "toon_shader.h"
#include "edge_filter.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"
#include "camera.h"
#include "light.h"

const char * CSkinmeshModel::m_aParam[MODEL_MAX] =
{
    "data/Model/Hierarchy/player/slime_10.x",
    "data/Model/Hierarchy/player/slime_50_tex.x",
    "data/Model/Hierarchy/player/slime_100_tex.x",
    "data/Model/Hierarchy/enemy/boss/takohead.x",
};


//=============================================================================
// コンストラクタ
//=============================================================================
CSkinmeshModel::CSkinmeshModel(PRIORITY Priority) : CScene(Priority)
{
    m_move = ZeroVector3;
    m_size = ZeroVector3;
    m_scale = MODEL_DEFAULT_SIZE;
    m_nTexPattern = 0;
    m_nLife = 0;
    m_pModelInfo = nullptr;
    m_pAnimetionController = 0;
    m_pRootFrame = 0;
    m_HLcontroller = nullptr;
    m_ModelNum = MODEL_PLAYER_100;
    m_bIsDraw = true;
    m_ToonAmbient = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

}

//=============================================================================
// デストラクタ
//=============================================================================
CSkinmeshModel::~CSkinmeshModel()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CSkinmeshModel * CSkinmeshModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL modelNum)
{
    //モデルクラスのポインタ変数
    CSkinmeshModel *pModel = new CSkinmeshModel;

    // nullcheck
    if (pModel)
    {
        pModel->m_ModelNum = modelNum;
        //初期化処理呼び出し
        pModel->Init();
        pModel->GetModelInfo()->SetPos(pos);
        return pModel;
    }

    return nullptr;
}

//=============================================================================
//モデルクラスの初期化処理
//=============================================================================
HRESULT CSkinmeshModel::Init()
{
    // 情報の生成
    CreateInfoPtr();

    //デバイス情報の取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // スキンメッシュ情報をXファイル保存用
    SkinMesh::AllocateHierarchy allocater;

    //メモリ確保(アニメーション）
    m_HLcontroller = new IHighLevelAnimController;

    //エラー確認用
    HRESULT model = D3DERR_WRONGTEXTUREFORMAT;
    //仮モデル
    model = D3DXLoadMeshHierarchyFromX((m_aParam[m_ModelNum]), D3DXMESH_MANAGED, pDevice, &allocater, 0, (D3DXFRAME**)&m_pRootFrame, &m_pAnimetionController);

    if (model == D3DERR_INVALIDCALL)
    {
        return 0;
    }

    //アニメーションコントローラーのコピー
    m_HLcontroller->SetAnimationController(m_pAnimetionController);

    //メッシュコンテナ取得関数
    SkinMesh::getMeshContainer(m_pRootFrame, &m_cont);

    for (unsigned int i = 0; i < m_cont.size(); i++)
    {
        m_combs.push_back((D3DXBONECOMBINATION*)m_cont[i]->boneCombinationTable->GetBufferPointer());

        m_cont[i]->pSkinInfo->ConvertToBlendedMesh(
            m_cont[i]->MeshData.pMesh,
            0,
            0,
            0,
            0,
            0,
            &m_cont[i]->maxFaceInfl,
            &m_cont[i]->numBoneCombinations,
            &m_cont[i]->boneCombinationTable,
            &m_cont[i]->MeshData.pMesh);

        // フレーム内にボーンIDとオフセット行列を埋め込む
        SkinMesh::setFrameId(m_pRootFrame, m_cont[i]->pSkinInfo);

        SkinMesh::createBlendIndex(
            &m_pBlendIndex,
            (D3DXBONECOMBINATION*)m_cont[i]->boneCombinationTable->GetBufferPointer(),
            m_cont[i]->numBoneCombinations);
    }

    return S_OK;
}

//=============================================================================
//モデルクラスの終了処理
//=============================================================================
void CSkinmeshModel::Uninit()
{
    // 影の終了処理
    HasPtrDelete();

    //オブジェクトの破棄
    Release();
}

//=============================================================================
// モデルクラスの更新処理
//=============================================================================
void CSkinmeshModel::Update()
{
    // 寿命を減らす
    m_nLife--;

    // 座標の更新
    m_pModelInfo->GetPos() += m_move;
}

//=============================================================================
// モデルクラスの描画処理
//=============================================================================
void CSkinmeshModel::Draw()
{
    if (m_bIsDraw)
    {
        CToonShader* pToonShader = CManager::GetInstance()->GetRenderer()->GetToonShader();

        CTexture *pTexture = GET_TEXTURE_PTR;
        D3DXVECTOR3 CameraPos = CManager::GetInstance()->GetCamera()->GetposV();
        D3DXVECTOR4 EyePos = D3DXVECTOR4(CameraPos, 1.0f);
        D3DXVECTOR4 LightDir = D3DXVECTOR4(CManager::GetInstance()->GetLight()->GetLightDir(), 0.0f);

        //デバイス情報の取得
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
        D3DMATERIAL9 matDef;
        D3DXMATRIX mtxWorld;
        D3DXVECTOR3 pos = m_pModelInfo->GetPos();
        D3DXVECTOR3 rot = m_pModelInfo->GetRot();
        D3DXMATRIX *worldMatAry[4] = {};
        LightDir.x = sinf(rot.y);
        LightDir.y = cosf(rot.y);

        // マトリクスの設定
        CLibrary::ConfigMatrix(&mtxWorld, pos, rot);

        D3DXMATRIX mtxProj = CManager::GetInstance()->GetCamera()->GetMtxProj();
        D3DXMATRIX mtxView = CManager::GetInstance()->GetCamera()->GetMtxView();

        //アニメーション更新
        m_HLcontroller->AdvanceTime(1);

        pToonShader->BeginSurface();
        //オブジェクトのテクスチャーをステージ０にセットする
        pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_WHITE));

        //現在フレーム(fps)のワールド変換行列
        std::map<DWORD, D3DXMATRIX> combMatrixMap;
        SkinMesh::updateCombMatrix(combMatrixMap, mtxWorld, m_pRootFrame);

        for (DWORD BCombiId = 0; BCombiId < m_cont.size(); BCombiId++)
        {
            // シェーダ開始
            pToonShader->Begin();

            for (DWORD AttribId = 0; AttribId < m_cont[BCombiId]->numBoneCombinations; AttribId++)
            {
                SkinMesh::BlendIndex& blendIndex = m_pBlendIndex[AttribId];
                pDevice->SetRenderState(D3DRS_VERTEXBLEND, blendIndex.boneNum - 1);
                for (int b = 0; b < blendIndex.boneNum; b++)
                {
                    worldMatAry[b] = &combMatrixMap[blendIndex.index[b]];
                }
                for (int b = blendIndex.boneNum; b < 4; b++)
                {
                    worldMatAry[b] = &mtxWorld;
                }

                pToonShader->SetVertexBlendInfo(
                    worldMatAry, mtxView, mtxProj, blendIndex.boneNum);

                D3DXVECTOR4 Diffuse = ZeroVector4;
                Diffuse.x = m_cont[BCombiId]->pMaterials[AttribId].MatD3D.Diffuse.r;
                Diffuse.y = m_cont[BCombiId]->pMaterials[AttribId].MatD3D.Diffuse.g;
                Diffuse.z = m_cont[BCombiId]->pMaterials[AttribId].MatD3D.Diffuse.b;
                Diffuse.w = m_cont[BCombiId]->pMaterials[AttribId].MatD3D.Diffuse.a;

                pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_SLIME));
                pToonShader->SetDiffuse(Diffuse);
                pToonShader->Begin(CToonShader::TOON_PASS_SKINMESH_TEX, mtxWorld, &LightDir);

                m_cont[BCombiId]->MeshData.pMesh->DrawSubset(AttribId);
                pToonShader->EndPass();
            }

            pToonShader->End();
        }

        //保持していたマテリアルを戻す
        pDevice->SetMaterial(&matDef);
        pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

        pToonShader->DrawEdgeFilter();
    }
}

//=============================================================================
// モデル情報の設定
//=============================================================================
void CSkinmeshModel::HasPtrDelete()
{
    if (m_pModelInfo)
    {
        m_pModelInfo->Uninit();
        m_pModelInfo = nullptr;
    }
}

//=============================================================================
// 情報のポインタ生成
//=============================================================================
void CSkinmeshModel::CreateInfoPtr()
{
    if (!m_pModelInfo)
    {
        m_pModelInfo = CModelInfo::Create(CModelInfo::MODEL_TYPE_NONE);
    }
}

//=============================================================================
// 情報のポインタ生成
//=============================================================================
void CSkinmeshModel::SetModelNumber(MODEL model)
{
    m_ModelNum = model;
}