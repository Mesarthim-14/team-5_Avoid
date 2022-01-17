//=============================================================================
//
// 当たり判定モデルの親クラス処理 [collisionModel.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "collisionModel.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCollisionModel::CCollisionModel(PRIORITY Priority) :CScene(Priority)
{
    m_pMesh = nullptr;
    m_pBuffMat = nullptr;
    memset(&m_info, 0, sizeof(m_info));
    m_type = TYPE_NONE;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCollisionModel::~CCollisionModel()
{
}

//*****************************************************************************
// ロード
//*****************************************************************************
void CCollisionModel::Load(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    switch (m_type)
    {
    case TYPE_POLYGON:

#if false
        // ポリゴンの作成
        D3DXCreatePolygon(
            pDevice,        // デバイス情報
            1.0f,           // 辺の長さ
            4,              // 辺の数
            &m_pMesh,       // メッシュ情報
            &m_pBuffMat);   // バッファ情報
#else
        // 直方体の作成(Yサイズ：0.0f)
        D3DXCreateBox(
            pDevice,        // デバイス情報
            1.0f,           // 横幅
            1.0f,           // 立幅
            1.0f,           // 奥幅
            &m_pMesh,       // メッシュ情報
            &m_pBuffMat);   // バッファ情報
#endif
        break;

    case TYPE_OBB:

        // 直方体の作成
        D3DXCreateBox(
            pDevice,        // デバイス情報
            1.0f,           // 横幅
            1.0f,           // 立幅
            1.0f,           // 奥幅
            &m_pMesh,       // メッシュ情報
            &m_pBuffMat);   // バッファ情報

        break;

    case TYPE_SPHERE:

        // 球の作成
        D3DXCreateSphere(
            pDevice,        // デバイス情報
            0.5f,           // 半径
            10,             // スライスの数
            10,             // スタック数
            &m_pMesh,       // メッシュ情報
            &m_pBuffMat);   // バッファ情報

        break;

    case TYPE_CYLINDER:

        // 円柱の作成
        D3DXCreateCylinder(
            pDevice,        // デバイス情報
            0.5f,           // 手前の円の半径
            0.5f,           // 奥の円の半径
            1.0f,           // 円柱の長さ
            10,             // スライス(円の超点数)
            1,              // スタック(円柱の分割数)
            &m_pMesh,       // メッシュ情報
            &m_pBuffMat);   // バッファ情報

        break;

    default:

        break;
    }
}

//*****************************************************************************
// アンロード
//*****************************************************************************
void CCollisionModel::Unload()
{
    if (m_pMesh)
    {
        //メッシュの破棄
        m_pMesh->Release();
        m_pMesh = nullptr;
    }

    if (m_pBuffMat)
    {
        //バッファの破棄
        m_pBuffMat->Release();
        m_pBuffMat = nullptr;
    }
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CCollisionModel::Init()
{
    //ロード処理
    Load();

    return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CCollisionModel::Uninit()
{
    //アンロード処理
    Unload();

    //ワールドマトリックスの初期化
    memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));

    //単数リリース
    Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CCollisionModel::Update()
{
    // ワールドマトリックスの設定
    SetMtx();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CCollisionModel::Draw()
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    if (m_pBuffMat)
    {
        // 色の設定
        D3DXMATERIAL* mat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
        mat->MatD3D.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
        mat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
        mat->MatD3D.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
        mat->MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
    }

    // ワイヤーフレームで描画
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    D3DMATERIAL9 matDef;    // 現在のマテリアル保持用

    // ワールドマトリックスの設定
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    // 現在のマテリアルを取得する
    pDevice->GetMaterial(&matDef);

    if (m_pBuffMat)
    {
        // マテリアルデータへのポインタ
        D3DXMATERIAL*pMat;

        // マテリアルデータへのポインタを取得
        pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

        // マテリアルのアンビエントにディフューズカラーを設定
        pMat->MatD3D.Ambient = pMat->MatD3D.Diffuse;

        // マテリアルの設定
        pDevice->SetMaterial(&pMat->MatD3D);
    }

    if (m_pMesh)
    {
        // モデルパーツの描画
        m_pMesh->DrawSubset(0);
    }

    pDevice->SetTexture(0, nullptr);

    // 保持していたマテリアルを戻す
    pDevice->SetMaterial(&matDef);
    pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

    // ワイヤーフレームをもどす
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//*****************************************************************************
// ワールドマトリックスの設定
//*****************************************************************************
void CCollisionModel::SetMtx()
{
    // ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxWorld);

    D3DXMATRIX mtxRot, mtxTrans, mtxScale;

    // 拡大率を反映
    D3DXMatrixScaling(&mtxScale, m_info.size.x, m_info.size.y, m_info.size.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

    // 向きを反映
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_info.rot.y, m_info.rot.x, m_info.rot.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    // 位置を反映
    D3DXMatrixTranslation(&mtxTrans, m_info.pos.x, m_info.pos.y, m_info.pos.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}