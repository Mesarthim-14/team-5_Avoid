//=============================================================================
//
// 当たり判定モデル(カプセル)の処理 [collisionModel_Capsule.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "collisionModel_Capsule.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCollisionModelCapsule::CCollisionModelCapsule(PRIORITY Priority) :CScene(Priority)
{
    memset(&m_apMesh, 0, sizeof(m_apMesh));
    memset(&m_apBuffMat, 0, sizeof(m_apBuffMat));
    memset(&m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCollisionModelCapsule::~CCollisionModelCapsule()
{
}

//*****************************************************************************
// ロード
//*****************************************************************************
void CCollisionModelCapsule::Load()
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // 円柱の作成
    D3DXCreateCylinder(
        pDevice,            // デバイス情報
        0.5f,               // 手前の円の半径
        0.5f,               // 奥の円の半径
        1.0f,               // 円柱の長さ
        10,                 // スライス(円の超点数)
        1,                  // スタック(円柱の分割数)
        &m_apMesh[0],       // メッシュ情報
        &m_apBuffMat[0]);   // バッファ情報

    // 球の作成
    D3DXCreateSphere(
        pDevice,            // デバイス情報
        0.5f,               // 半径
        10,                 // スライスの数
        10,                 // スタック数
        &m_apMesh[1],       // メッシュ情報
        &m_apBuffMat[1]);   // バッファ情報

    // 球の作成
    D3DXCreateSphere(
        pDevice,            // デバイス情報
        0.5f,               // 半径
        10,                 // スライスの数
        10,                 // スタック数
        &m_apMesh[2],       // メッシュ情報
        &m_apBuffMat[2]);   // バッファ情報
}

//*****************************************************************************
// アンロード処理
//*****************************************************************************
void CCollisionModelCapsule::Unload()
{
    for (int nCount = 0; nCount < TYPE_MAX; nCount++)
    {
        if (m_apMesh[nCount])
        {
            //メッシュの破棄
            m_apMesh[nCount]->Release();
            m_apMesh[nCount] = nullptr;
        }

        if (m_apBuffMat[nCount])
        {
            //バッファの破棄
            m_apBuffMat[nCount]->Release();
            m_apBuffMat[nCount] = nullptr;
        }
    }
}

//*****************************************************************************
// 当たり判定モデルの生成
//*****************************************************************************
CCollisionModelCapsule * CCollisionModelCapsule::Create(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot)
{
    CCollisionModelCapsule *pCollisionModelSphere = new CCollisionModelCapsule;

    if (pCollisionModelSphere)
    {
        //当たり判定モデル情報の設定
        pCollisionModelSphere->m_info.pos = pos;
        pCollisionModelSphere->m_info.radius = radius;
        pCollisionModelSphere->m_info.length = length;
        pCollisionModelSphere->m_info.rot = rot;

        //当たり判定モデルの初期化処理
        pCollisionModelSphere->Init();

        return pCollisionModelSphere;
    }

    return nullptr;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CCollisionModelCapsule::Init()
{
    // ロード処理
    Load();

    for (int nCount = 0; nCount < TYPE_MAX; nCount++)
    {
        // 角度の設定
        SetRot(nCount);

        // 大きさの設定
        SetSize(nCount);

        // 位置の設定
        SetPos(nCount);
    }

    return E_NOTIMPL;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CCollisionModelCapsule::Uninit()
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
void CCollisionModelCapsule::Update()
{
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CCollisionModelCapsule::Draw()
{
#ifdef _DEBUG
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    for (int nCount = 0; nCount < TYPE_MAX; nCount++)
    {
        //色の設定
        D3DXMATERIAL* mat = (D3DXMATERIAL*)m_apBuffMat[nCount]->GetBufferPointer();
        mat->MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
        mat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
        mat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
        mat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

        //ワイヤーフレームで描画
        pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

        //ワールドマトリックスの初期化
        D3DXMatrixIdentity(&m_mtxWorld);

        D3DXMATRIX mtxTrans, mtxScale, mtxRot;
        memset(&mtxTrans, 0, sizeof(mtxTrans));
        memset(&mtxScale, 0, sizeof(mtxScale));
        memset(&mtxRot, 0, sizeof(mtxRot));

        //ワールドマトリックスの初期化
        D3DXMatrixIdentity(&m_mtxWorld);

        // ワールドマトリックスの設定
        SetMtx(nCount);

        //ワールドマトリックスの設定
        pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

        D3DMATERIAL9 matDef;    //現在のマテリアル保持用
        memset(&matDef, 0, sizeof(matDef));

        //現在のマテリアルを取得する
        pDevice->GetMaterial(&matDef);

        //マテリアルデータへのポインタ
        D3DXMATERIAL*pMat = nullptr;

        //マテリアルデータへのポインタを取得
        pMat = (D3DXMATERIAL*)m_apBuffMat[nCount]->GetBufferPointer();

        //マテリアルのアンビエントにディフューズカラーを設定
        pMat->MatD3D.Ambient = pMat->MatD3D.Diffuse;

        //マテリアルの設定
        pDevice->SetMaterial(&pMat->MatD3D);

        if (m_apMesh)
        {
            //モデルパーツの描画
            m_apMesh[nCount]->DrawSubset(0);
        }

        pDevice->SetTexture(0, nullptr);

        //保持していたマテリアルを戻す
        pDevice->SetMaterial(&matDef);
        pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
    }

    //ワイヤーフレームをもどす
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif
}

//*****************************************************************************
// 位置/半径/長さ/角度の設定
//*****************************************************************************
void CCollisionModelCapsule::SetInfo(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot)
{
    m_info.pos = pos;
    m_info.radius = radius;
    m_info.length = length;
    m_info.rot = rot;

    for (int nCount = 0; nCount < TYPE_MAX; nCount++)
    {
        // 角度の設定
        SetRot(nCount);

        // 大きさの設定
        SetSize(nCount);

        // 位置の設定
        SetPos(nCount);
    }
}

//*****************************************************************************
// 位置の設定
//*****************************************************************************
void CCollisionModelCapsule::SetPos(const int &nCount)
{
    switch (nCount)
    {
    case TYPE_CYLINDER:

        m_info.detail.cylinder.pos = D3DXVECTOR3(m_info.pos.x, m_info.pos.y, m_info.pos.z);

        break;

    case TYPE_SPHERE_1:

        // 回転量が0のときの座標を原点を中心に設定
        m_info.detail.sphere1.pos = D3DXVECTOR3(0.0f, ((m_info.length / 2) - m_info.radius), 0.0f);

        // 点の三次元回転処理
        CLibrary::Rotate3D(m_info.detail.sphere1.pos, m_info.rot);

        // 円柱の座標に足して、正確な位置に設定する
        m_info.detail.sphere1.pos += m_info.pos;

        // 線分の始点の設定
        m_info.P0 = m_info.detail.sphere1.pos;

        break;

    case TYPE_SPHERE_2:

        // 回転量が0のときの座標を原点を中心に設定
        m_info.detail.sphere2.pos = D3DXVECTOR3(0.0f, -((m_info.length / 2) - m_info.radius), 0.0f);

        // 点の三次元回転処理
        CLibrary::Rotate3D(m_info.detail.sphere2.pos, m_info.rot);

        // 円柱の座標に足して、正確な位置に設定する
        m_info.detail.sphere2.pos += m_info.pos;

        // 線分の終点の設定
        m_info.P1 = m_info.detail.sphere2.pos;

        break;

    default:

        break;
    }
}

//*****************************************************************************
// 大きさの設定
//*****************************************************************************
void CCollisionModelCapsule::SetSize(const int &nCount)
{
    switch (nCount)
    {
    case TYPE_CYLINDER:

        m_info.detail.cylinder.radius = m_info.radius * 2;
        m_info.detail.cylinder.length = m_info.length - (m_info.radius * 2);

        break;

    case TYPE_SPHERE_1:

        m_info.detail.sphere1.radius = m_info.radius;

        break;

    case TYPE_SPHERE_2:

        m_info.detail.sphere2.radius = m_info.radius;

        break;

    default:

        break;
    }
}

//*****************************************************************************
// 角度の設定
//*****************************************************************************
void CCollisionModelCapsule::SetRot(const int &nCount)
{
    switch (nCount)
    {
    case TYPE_CYLINDER:

        m_info.detail.cylinder.rot = D3DXVECTOR3(m_info.rot.x + D3DXToRadian(90.0f), m_info.rot.y, m_info.rot.z);

        break;

    case TYPE_SPHERE_1:

        m_info.detail.sphere1.rot = D3DXVECTOR3(m_info.rot.x, m_info.rot.y, m_info.rot.z);

        break;

    case TYPE_SPHERE_2:

        m_info.detail.sphere2.rot = D3DXVECTOR3(m_info.rot.x, m_info.rot.y, m_info.rot.z);

        break;

    default:

        break;
    }
}

//*****************************************************************************
// ワールドマトリックスの設定
//*****************************************************************************
void CCollisionModelCapsule::SetMtx(const int &nCount)
{
    D3DXMATRIX mtxTrans, mtxScale, mtxRot;
    memset(&mtxTrans, 0, sizeof(mtxTrans));
    memset(&mtxScale, 0, sizeof(mtxScale));
    memset(&mtxRot, 0, sizeof(mtxRot));

    switch (nCount)
    {
    case TYPE_CYLINDER:

        //向きを反映
        D3DXMatrixRotationYawPitchRoll(&mtxRot, m_info.detail.cylinder.rot.y, m_info.detail.cylinder.rot.x, m_info.detail.cylinder.rot.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

        // 拡大率を反映
        D3DXMatrixScaling(&mtxScale, m_info.detail.cylinder.radius, m_info.detail.cylinder.length, m_info.detail.cylinder.radius);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

        //位置を反映
        D3DXMatrixTranslation(&mtxTrans, m_info.detail.cylinder.pos.x, m_info.detail.cylinder.pos.y, m_info.detail.cylinder.pos.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

        break;

    case TYPE_SPHERE_1:

        //向きを反映
        D3DXMatrixRotationYawPitchRoll(&mtxRot, m_info.detail.sphere1.rot.y, m_info.detail.sphere1.rot.x, m_info.detail.sphere1.rot.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

        // 拡大率を反映
        D3DXMatrixScaling(&mtxScale, m_info.detail.sphere1.radius * 2, m_info.detail.sphere1.radius * 2, m_info.detail.sphere1.radius * 2);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

        //位置を反映
        D3DXMatrixTranslation(&mtxTrans, m_info.detail.sphere1.pos.x, m_info.detail.sphere1.pos.y, m_info.detail.sphere1.pos.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

        break;

    case TYPE_SPHERE_2:

        //向きを反映
        D3DXMatrixRotationYawPitchRoll(&mtxRot, m_info.detail.sphere2.rot.y, m_info.detail.sphere2.rot.x, m_info.detail.sphere2.rot.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

        // 拡大率を反映
        D3DXMatrixScaling(&mtxScale, m_info.detail.sphere2.radius * 2, m_info.detail.sphere2.radius * 2, m_info.detail.sphere2.radius * 2);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

        //位置を反映
        D3DXMatrixTranslation(&mtxTrans, m_info.detail.sphere2.pos.x, m_info.detail.sphere2.pos.y, m_info.detail.sphere2.pos.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

        break;

    default:

        break;
    }
}