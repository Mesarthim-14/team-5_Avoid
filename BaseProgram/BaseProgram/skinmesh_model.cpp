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

const char * CSkinmeshModel::m_aParam[MODEL_MAX] =
{
	"data/Model/Hierarchy/player/slime_50.x",
	"data/Model/Hierarchy/player/slime_50.x",
	"data/Model/Hierarchy/player/slime_100.x",
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
HRESULT CSkinmeshModel::Init(void)
{
	// 情報の生成
	CreateInfoPtr();

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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

		// フレーム内にボーンIDとオフセット行列を埋め込む
		SkinMesh::setFrameId(m_pRootFrame, m_cont[i]->pSkinInfo);
	}

	return S_OK;
}

//=============================================================================
//モデルクラスの終了処理
//=============================================================================
void CSkinmeshModel::Uninit(void)
{
	// 影の終了処理
	HasPtrDelete();

	
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// モデルクラスの更新処理
//=============================================================================
void CSkinmeshModel::Update(void)
{
	// 寿命を減らす
	m_nLife--;

	// 座標の更新
	m_pModelInfo->GetPos() += m_move;

	////仮
	////アニメーション変更
	////m_HLcontroller->ChangeAnimation(0);
	////ループ時間
	//m_HLcontroller->SetLoopTime(1, 60);
	//m_HLcontroller->SetLoopTime(0, 60);

	//////アニメーション変更
	////m_HLcontroller->ChangeAnimation(0);

	////アニメーションのシフトにかかる時間
	//m_HLcontroller->SetShiftTime(1, 10);
	//m_HLcontroller->SetShiftTime(0, 10);

	////m_HLcontroller->ChangeAnimation(1);
	
}

//=============================================================================
// モデルクラスの描画処理
//=============================================================================
void CSkinmeshModel::Draw(void)
{
	if (m_bIsDraw)
	{
		//デバイス情報の取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		D3DMATERIAL9 matDef;
		D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxWorld;
		D3DXVECTOR3 pos = m_pModelInfo->GetPos();
		D3DXVECTOR3 rot = m_pModelInfo->GetRot();

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// 拡大率を反映
		D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		//現在フレーム(fps)のワールド変換行列
		std::map<DWORD, D3DXMATRIX> combMatrixMap;

		//// 時間を進めて姿勢更新
		//m_pAnimetionController->AdvanceTime(0.0001f, 0);
		//m_pAnimetionController->SetTrackAnimationSet(0, 0);
		//アニメーション更新
		m_HLcontroller->AdvanceTime(1);

		SkinMesh::updateCombMatrix(combMatrixMap, mtxWorld, m_pRootFrame);

		for (DWORD BCombiId = 0; BCombiId < m_cont.size(); BCombiId++)
		{
			for (DWORD AttribId = 0; AttribId < m_cont[BCombiId]->numBoneCombinations; AttribId++)
			{
				DWORD boneCount = 0;

				for (DWORD Count = 0; Count < m_cont[BCombiId]->maxFaceInfl; Count++)
				{
					//ボーンコンビネーションテーブルからボーンIDを抽出
					DWORD BoneId = m_combs[BCombiId][AttribId].BoneId[Count];

					//ボーンIDが存在している
					if (BoneId != UINT_MAX)
					{
						// インデックス付きワールドマトリックスの設定
						pDevice->SetTransform(D3DTS_WORLDMATRIX(Count), &combMatrixMap[BoneId]);
						boneCount++;
					}
				}

				pDevice->SetRenderState(D3DRS_VERTEXBLEND, boneCount - 1);

				m_cont[BCombiId]->pMaterials->MatD3D.Ambient = WhiteColor;
				pDevice->SetMaterial(&m_cont[BCombiId]->pMaterials->MatD3D);
				//メッシュコンテナ内のメッシュデータ
				m_cont[BCombiId]->MeshData.pMesh->DrawSubset(AttribId);

			}
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

		// 影の描画
		m_pModelInfo->ShadowDraw(rot);
	}
}

//=============================================================================
// モデル情報の設定
//=============================================================================
void CSkinmeshModel::HasPtrDelete(void)
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
void CSkinmeshModel::CreateInfoPtr(void)
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