//=============================================================================
//
// 当たり判定モデル(円柱)の処理 [collisionModel_Cylinder.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "collisionModel_Cylinder.h"
#include "library.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCollisionModelCylinder::CCollisionModelCylinder(PRIORITY Priority) :CCollisionModel(Priority)
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCollisionModelCylinder::~CCollisionModelCylinder()
{
}

//*****************************************************************************
// 当たり判定モデルの生成
//*****************************************************************************
CCollisionModelCylinder * CCollisionModelCylinder::Create(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot)
{
    CCollisionModelCylinder *pCollisionModelCylinder = new CCollisionModelCylinder;

    if (pCollisionModelCylinder)
    {
        //当たり判定モデル情報の設定
        pCollisionModelCylinder->SetInfo(pos, D3DXVECTOR3(radius * 2, radius * 2, length), rot);
        pCollisionModelCylinder->SetType(TYPE_CYLINDER);

        //当たり判定モデルの初期化処理
        pCollisionModelCylinder->Init();

        return pCollisionModelCylinder;
    }

    return nullptr;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CCollisionModelCylinder::Init()
{
    CCollisionModel::Init();

    return E_NOTIMPL;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CCollisionModelCylinder::Uninit()
{
    CCollisionModel::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CCollisionModelCylinder::Update()
{
    CCollisionModel::Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CCollisionModelCylinder::Draw()
{
    CCollisionModel::Draw();
}