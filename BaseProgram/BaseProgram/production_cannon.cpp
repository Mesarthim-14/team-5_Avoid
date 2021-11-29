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
#include "kraken.h"
#include "state_kraken_not_attack.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define SHOT_BULLET_TIME    (60)    // 弾を打つ時間
#define END_TIME            (240)   // 終了時間

//=======================================================================================
// コンストラクタ
//=======================================================================================
CProductionCannon::CProductionCannon()
{
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
void CProductionCannon::Init()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CreateState(pPlayer, CPlayerStateCannon::Create());

    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
    CreateState(pCamera, CCameraStateCannon::Create());

    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    CreateState(pKraken, CKrakenStateNotAttack::Create());
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CProductionCannon::Update()
{
    if (TimeCounter(END_TIME) == SHOT_BULLET_TIME)
    {
        CCannon* pCannon = CManager::GetInstance()->GetGame()->GetGimmickFactory()->GetCannonManager()->GetCurrentCannon();
        CCannonBullet::Create(pCannon->GetPos(), pCannon->GetRot());
    }
}