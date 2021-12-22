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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ROT (D3DXVECTOR3(D3DXToRadian(90), 0.0f, 0.0f))

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCollisionModelCylinder::CCollisionModelCylinder(PRIORITY Priority) :CCollisionModel(Priority)
{
    float m_radius = 0.0f;
    float m_length = 0.0f;
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
    CCollisionModelCylinder *pColModelCylinder = new CCollisionModelCylinder(PRIORITY_COLLISION);

    if (pColModelCylinder)
    {
        //当たり判定モデル情報の設定
        pColModelCylinder->m_radius = radius;
        pColModelCylinder->m_length = length;
        pColModelCylinder->SetInfo(pos, D3DXVECTOR3(radius * 2, radius * 2, length), ROT + rot);
        pColModelCylinder->SetType(TYPE_CYLINDER);

        //当たり判定モデルの初期化処理
        pColModelCylinder->Init();

        return pColModelCylinder;
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
#ifdef _DEBUG
    CCollisionModel::Draw();
#endif
}