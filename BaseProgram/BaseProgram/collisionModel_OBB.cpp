//=============================================================================
//
// 当たり判定モデル(直方体)の処理 [collisionModelOBB.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "collisionModel_OBB.h"
#include "library.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCollisionModelOBB::CCollisionModelOBB(PRIORITY Priority) :CCollisionModel(Priority)
{
    memset(&m_DirVect, 0, sizeof(m_DirVect));
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCollisionModelOBB::~CCollisionModelOBB()
{
}

//*****************************************************************************
// 当たり判定モデルの生成
//*****************************************************************************
CCollisionModelOBB * CCollisionModelOBB::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot)
{
    CCollisionModelOBB *pCollisionModelOBB = new CCollisionModelOBB(PRIORITY_COLLISION);

    if (pCollisionModelOBB)
    {
        //当たり判定モデル情報の設定
        pCollisionModelOBB->SetInfo(pos, size, rot);
        pCollisionModelOBB->SetType(TYPE_OBB);

        //当たり判定モデルの初期化処理
        pCollisionModelOBB->Init();

        return pCollisionModelOBB;
    }

    return nullptr;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CCollisionModelOBB::Init()
{
    CCollisionModel::Init();

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
void CCollisionModelOBB::Uninit()
{
    CCollisionModel::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CCollisionModelOBB::Update()
{
    CCollisionModel::Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CCollisionModelOBB::Draw()
{
#ifdef _DEBUG
    CCollisionModel::Draw();
#endif
}