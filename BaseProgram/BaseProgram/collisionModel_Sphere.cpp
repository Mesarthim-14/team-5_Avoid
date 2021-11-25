//=============================================================================
//
// 当たり判定モデル(球体)の処理 [collisionModel_Sphere.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "collisionModel_Sphere.h"
#include "library.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCollisionModelSphere::CCollisionModelSphere(PRIORITY)
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCollisionModelSphere::~CCollisionModelSphere()
{
}

//*****************************************************************************
// 当たり判定モデルの生成
//*****************************************************************************
CCollisionModelSphere * CCollisionModelSphere::Create(const D3DXVECTOR3 & pos, const float &radius, const D3DXVECTOR3 & rot)
{
    CCollisionModelSphere *pCollisionModelSphere = new CCollisionModelSphere;

    if (pCollisionModelSphere)
    {
        //当たり判定モデル情報の設定
        pCollisionModelSphere->SetInfo(pos, D3DXVECTOR3(radius, radius, radius), rot);
        pCollisionModelSphere->SetType(TYPE_SPHERE);

        //当たり判定モデルの初期化処理
        pCollisionModelSphere->Init();

        return pCollisionModelSphere;
    }

    return nullptr;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CCollisionModelSphere::Init()
{
    CCollisionModel::Init();

    return E_NOTIMPL;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CCollisionModelSphere::Uninit()
{
    CCollisionModel::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CCollisionModelSphere::Update()
{
    CCollisionModel::Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CCollisionModelSphere::Draw()
{
    CCollisionModel::Draw();
}