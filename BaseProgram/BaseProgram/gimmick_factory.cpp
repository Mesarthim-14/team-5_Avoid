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
#include "plane_vortex.h"
#include "plane_vortex2.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGimmickFactory::CGimmickFactory()
{
    m_pCheckPoint = nullptr;
    m_pBarrelFactory = nullptr;
    m_pHeel = nullptr;
    m_pCannonManager = nullptr;
    m_pMoveScaffold = nullptr;
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
    CreateEffect();

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
    if (m_pMoveScaffold)
    {
        m_pMoveScaffold->Uninit();
        m_pMoveScaffold = nullptr;
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
// エフェクト生成
//=======================================================================================
void CGimmickFactory::CreateEffect()
{
    CreateSwirlEffect();    // 渦エフェクト
}

//=======================================================================================
// 動く床ギミック
//=======================================================================================
void CGimmickFactory::CreateMoveScaffold()
{
    if (!m_pMoveScaffold)
    {
        m_pMoveScaffold = CMoveScaffold::Create(D3DXVECTOR3(-54035.3f, 0.0f, -13141.0f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));
    }
    CRubble1::Create(D3DXVECTOR3(-30141.4f, 500.0f, 11044.3f), D3DXVECTOR3(0.0f, D3DXToRadian(-53.0f), 0.0f));
    CRubble1::Create(D3DXVECTOR3(-23208.7f, 500.0f, 30815.4f), D3DXVECTOR3(0.0f, D3DXToRadian(-53.0f), 0.0f));
    CRubble1::Create(D3DXVECTOR3(-9112.1f, 500.0f, 43736.2f), D3DXVECTOR3(0.0f, D3DXToRadian(-53.0f), 0.0f));
    CRubble1::Create(D3DXVECTOR3(-8504.7f, 500.0f, 54964.4f), D3DXVECTOR3(0.0f, D3DXToRadian(-53.0f), 0.0f));

    CRubble2::Create(D3DXVECTOR3(-40179.2f, 1200.0f, 2725.8f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));
    CRubble2::Create(D3DXVECTOR3(-43521.4f, 1200.0f, 4912.3f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));
    CRubble2::Create(D3DXVECTOR3(-36836.8f, 1200.0f, 539.6f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));
    
    CRubble2::Create(D3DXVECTOR3(-27445.0f, 1200.0f, 21874.1f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));
    CRubble2::Create(D3DXVECTOR3(-30787.2f, 1200.0f, 24060.3f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));
    CRubble2::Create(D3DXVECTOR3(-24102.8f, 1200.0f, 19687.9f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));

    CRubble2::Create(D3DXVECTOR3(-15391.1f, 1200.0f, 36226.8f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));
    CRubble2::Create(D3DXVECTOR3(-18733.2f, 1200.0f, 38413.0f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));
    CRubble2::Create(D3DXVECTOR3(-12048.9f, 1200.0f, 34040.4f), D3DXVECTOR3(0.0f, D3DXToRadian(-143.0f), 0.0f));

    //x = 3342.2, z = 2186.2
}

//=======================================================================================
// 回転ギミック
//=======================================================================================
void CGimmickFactory::CreateRotateGimmick()
{
    CRotateGimmick::Create(D3DXVECTOR3(-10676.8f, 2000.0f, -47242.9f));
 //   CRotateGimmick::Create(D3DXVECTOR3(-31838.1f, 800.0f, -17180.4f));
}

//=======================================================================================
// 坂道の生成
//=======================================================================================
void CGimmickFactory::CreateSlope()
{
    CSlope::Create(D3DXVECTOR3(-12503.1f, 2700.0f, -74892.9f), D3DXVECTOR3(0.0f, D3DXToRadian(278.0f), 0.0f));
    CSlope::Create(D3DXVECTOR3(53518.3f, 2200.0f, -36190.0f), D3DXVECTOR3(D3DXToRadian(-4.0f), D3DXToRadian(243.0f), 0.0f));
    CSlope::Create(D3DXVECTOR3(2961.4f, 2700.0f, -62761.8f), D3DXVECTOR3(0.0f, D3DXToRadian(6.0f), 0.0f));
    CSlope::Create(D3DXVECTOR3(11661.5f, 2700.0f, 58025.7f), D3DXVECTOR3(0.0f, D3DXToRadian(118.0f), 0.0f));
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
    CBridge::Create(D3DXVECTOR3(13890.0f, 4700.0f, -49270.0f), D3DXVECTOR3(0.0f, D3DXToRadian(7.0f), 0.0f));
}

//=======================================================================================
// 渦
//=======================================================================================
void CGimmickFactory::CreateSwirl()
{
    CSwirlScaffold::Create(D3DXVECTOR3(50244.2f, 0.0f, -18862.9f));
    CSwirlScaffold::Create(D3DXVECTOR3(59435.2f, 0.0f, -23429.4f));
}

//=======================================================================================
// 渦の下のエフェクト
//=======================================================================================
void CGimmickFactory::CreateSwirlEffect()
{
    CPlaneVortex::Create(D3DXVECTOR3(50244.2f, 0.0f, -18862.9f));
    CPlaneVortex::Create(D3DXVECTOR3(59435.2f, 0.0f, -23429.4f));
    CPlaneVortex2::Create(D3DXVECTOR3(50244.2f, 0.0f, -18862.9f));
    CPlaneVortex2::Create(D3DXVECTOR3(59435.2f, 0.0f, -23429.4f));
}