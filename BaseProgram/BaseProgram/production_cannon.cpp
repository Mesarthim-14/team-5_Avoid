//=======================================================================================
//
// 大砲時の演出 [production_cannon.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "production_cannon.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "gimmick_factory.h"
#include "player.h"
#include "camera_game.h"
#include "state_player_cannon.h"
#include "state_player_normal.h"
#include "state_camera_cannon.h"
#include "state_camera_normal.h"
#include "cannon_bullet.h"
#include "cannon.h"
#include "cannon_manager.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define SHOT_BULLET_TIME    (60)    // 弾を打つ時間
#define END_TIME            (240)    // 終了時間

//=======================================================================================
// コンストラクタ
//=======================================================================================
CProductionCannon::CProductionCannon()
{
    m_pPlayerState = nullptr;
    m_pCameraState = nullptr;
    m_nCounter = 0;
    m_bEnd = false;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CProductionCannon::~CProductionCannon()
{
}

//=======================================================================================
// インスタンス生成
//=======================================================================================
CProductionCannon * CProductionCannon::Create()
{
    // メモリ確保
    CProductionCannon *pProductionCannon = new CProductionCannon;
    if (pProductionCannon)
    {
        // インスタンス生成
        pProductionCannon->Init();
        return pProductionCannon;
    }

    return nullptr;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CProductionCannon::Init()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();

    if (!m_pPlayerState)
    {
        // プレイヤーの状態生成
        m_pPlayerState = CPlayerStateCannon::Create();
        pPlayer->ChangeState(m_pPlayerState);
    }
    if (!m_pCameraState)
    {
        // カメラの状態生成
        m_pCameraState = CCameraStateCannon::Create();
        pCamera->ChangeState(m_pCameraState);
    }

    return S_OK;
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CProductionCannon::Update()
{
    m_nCounter++;

    // 弾の発射
    if (m_nCounter == SHOT_BULLET_TIME)
    {
        CCannon* pCannon = CManager::GetInstance()->GetGame()->GetGimmickFactory()->GetCannonManager()->GetCurrentCannon();
        CCannonBullet::Create(pCannon->GetPos(), pCannon->GetRot());
    }

    // 終了フラグ
    if (m_nCounter >= END_TIME)
    {
        m_pPlayerState = nullptr;
        m_pCameraState = nullptr;
        CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
        CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
        pPlayer->ChangeState(CPlayerStateNormal::Create());
        pCamera->ChangeState(CCameraStateNormal::Create());
        m_bEnd = true;
    }
}