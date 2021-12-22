//=============================================================================
//
// 当たり判定モデル(ポリゴン)の処理 [collisionModel_Polygon.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "collisionModel_Polygon.h"
#include "library.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCollisionModelPolygon::CCollisionModelPolygon(PRIORITY Priority) :CCollisionModel(Priority)
{
    m_norVec = ZeroVector3;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCollisionModelPolygon::~CCollisionModelPolygon()
{
}

//*****************************************************************************
// 当たり判定モデルの生成
//*****************************************************************************
CCollisionModelPolygon * CCollisionModelPolygon::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR2 &size, const D3DXVECTOR3 &rot)
{
    CCollisionModelPolygon *pColModelPolygon = new CCollisionModelPolygon(PRIORITY_COLLISION);

    if (pColModelPolygon)
    {
        //当たり判定モデル情報の設定
        pColModelPolygon->SetInfo(pos, D3DXVECTOR3(size.x, 0.0f, size.y), rot);
        pColModelPolygon->SetType(TYPE_POLYGON);

        //当たり判定モデルの初期化処理
        pColModelPolygon->Init();

        return pColModelPolygon;
    }

    return nullptr;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CCollisionModelPolygon::Init()
{
    CCollisionModel::Init();

    // 法線ベクトルの設定
    m_norVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    CLibrary::Rotate3D(m_norVec, GetInfo().rot);

    //各軸の回転前座標の設定(回転していないXYZ軸に大きさだけを適応)
    m_DirVect[0] = D3DXVECTOR3(GetInfo().size.x / 2, 0.0f, 0.0f);
    m_DirVect[1] = D3DXVECTOR3(0.0f, GetInfo().size.y / 2, 0.0f);
    m_DirVect[2] = D3DXVECTOR3(0.0f, 0.0f, GetInfo().size.z / 2);

    //各軸の方向ベクトルの計算
    for (int nCount = 0; nCount < AXIS_NUM_OBB; nCount++)
    {
        CLibrary::Rotate3D(m_DirVect[nCount], GetInfo().rot);
    }

    return E_NOTIMPL;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CCollisionModelPolygon::Uninit()
{
    CCollisionModel::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CCollisionModelPolygon::Update()
{
    CCollisionModel::Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CCollisionModelPolygon::Draw()
{
#ifdef _DEBUG
    CCollisionModel::Draw();
#endif
}