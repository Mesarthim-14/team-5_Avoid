//=======================================================================================
//
// ギミック生成クラス [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "gimmick_factory.h"
#include "manager.h"
#include "resource_manager.h"
#include "check_point.h"
#include "move_scaffold.h"
#include "rubble1.h"
#include "rubble2.h"
#include "rotate_gimmick.h"
#include "barrel.h"
#include "slope.h"
#include "barrel_factory.h"
#include "heel.h"
#include "cannon.h"
#include "bridge.h"
#include "cannon_manager.h"
#include "swirl_scaffold.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGimmickFactory::CGimmickFactory()
{
    m_pCheckPoint = nullptr;
    m_pBarrelFactory = nullptr;
    m_pHeel = nullptr;
    m_pCannonManager = nullptr;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGimmickFactory::~CGimmickFactory()
{
}

//=======================================================================================
// インスタンス生成
//=======================================================================================
CGimmickFactory * CGimmickFactory::Create()
{
    CGimmickFactory *pGimmickFactory = new CGimmickFactory;
    if (pGimmickFactory)
    {
        pGimmickFactory->Init();
        return pGimmickFactory;
    }
    return nullptr;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGimmickFactory::Init()
{
    CreateCheckPoint();
    CreateGimmick();

    return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGimmickFactory::Uninit()
{
    // チェックポイント
    if (m_pCheckPoint)
    {
        m_pCheckPoint->Uninit();
        delete m_pCheckPoint;
        m_pCheckPoint = nullptr;
    }
    if (m_pBarrelFactory)
    {
        delete m_pBarrelFactory;
        m_pBarrelFactory = nullptr;

    }
    if (m_pHeel)
    {
        m_pHeel->Uninit();
        delete m_pHeel;
        m_pHeel = nullptr;
    }
    if (m_pCannonManager)
    {
        m_pCannonManager->Uninit();
        delete m_pCannonManager;
        m_pCannonManager = nullptr;
    }
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGimmickFactory::Update()
{
    // チェックポイント
    if (m_pCheckPoint)
    {
        m_pCheckPoint->Update();
    }
    if (m_pBarrelFactory)
    {
        m_pBarrelFactory->Update();
    }
    if (m_pHeel)
    {
        m_pHeel->Update();
    }
    if (m_pCannonManager)
    {
        m_pCannonManager->Update();
    }
}

//=======================================================================================
// 情報表示
//=======================================================================================
void CGimmickFactory::CreateCheckPoint()
{
    if (!m_pCheckPoint)
    {
        m_pCheckPoint = CCheckPoint::Create();
    }
}

//=======================================================================================
// マップの生成
//=======================================================================================
void CGimmickFactory::CreateGimmick()
{
    // 動く床
    CreateMoveScaffold();
    CreateRotateGimmick();
    CreateSlope();
    CreateCannon();
    CreateBridge();
    CreateSwirl();

    if (!m_pBarrelFactory)
    {
        m_pBarrelFactory = CBarrelFactory::Create();
    }
    if (!m_pHeel)
    {
        m_pHeel = CHeel::Create();
    }
}

//=======================================================================================
// 動く床ギミック
//=======================================================================================
void CGimmickFactory::CreateMoveScaffold()
{
    CMoveScaffold::Create();
    CRubble1::Create();
    CRubble2::Create();
}

//=======================================================================================
// 回転ギミック
//=======================================================================================
void CGimmickFactory::CreateRotateGimmick()
{
    CRotateGimmick::Create(D3DXVECTOR3(-12126.1f, 810.0f, -16003.8f));
    CRotateGimmick::Create(D3DXVECTOR3(-31838.1f, 800.0f, -17180.4f));

}

//=======================================================================================
// 坂道の生成
//=======================================================================================
void CGimmickFactory::CreateSlope()
{
    CSlope::Create(D3DXVECTOR3(-6562.7f, -200.0f, -13120.3f), D3DXVECTOR3(0.0f, D3DXToRadian(-75.0f), 0.0f));
    CSlope::Create(D3DXVECTOR3(-9662.7f, -200.0f, -23596.1f), D3DXVECTOR3(0.0f, D3DXToRadian(-15.0f), 0.0f));
}

//=======================================================================================
// 大砲の生成
//=======================================================================================
void CGimmickFactory::CreateCannon()
{
    if (!m_pCannonManager)
    {
        m_pCannonManager = CCannonManager::Create();
    }
}

//=======================================================================================
// 橋の生成
//=======================================================================================
void CGimmickFactory::CreateBridge()
{
    CBridge::Create(D3DXVECTOR3(-25423.0f, 1000.0f, -18907.5f), D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f));
}

//=======================================================================================
// 渦
//=======================================================================================
void CGimmickFactory::CreateSwirl()
{
    CSwirlScaffold::Create(D3DXVECTOR3(-5788.6f, 0.0f, -22500.4f));
}