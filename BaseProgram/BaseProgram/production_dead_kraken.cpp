//=======================================================================================
//
// クラーケンが死ぬ演出 [production_dead_kraken.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "production_dead_kraken.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "gimmick_factory.h"
#include "player.h"
#include "camera_game.h"
#include "state_player_not_move.h"
#include "state_player_normal.h"
#include "state_camera_normal.h"
#include "state_camera_angry_kraken.h"
#include "state_kraken_dead.h"
#include "kraken.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CProductionDeadKraken::CProductionDeadKraken()
{
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CProductionDeadKraken::~CProductionDeadKraken()
{
}

//=======================================================================================
// インスタンス生成
//=======================================================================================
CProductionDeadKraken * CProductionDeadKraken::Create()
{
    // メモリ確保
    CProductionDeadKraken *pProductionCannon = new CProductionDeadKraken;
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
void CProductionDeadKraken::Init()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
    CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    CreateState(pPlayer, CPlayerStateNotMove::Create());
    CreateState(pCamera, CCameraStateAngryKraken::Create());
    CreateState(pKraken, CKrakenStateDead::Create());
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CProductionDeadKraken::Uninit()
{
    CProduction::Uninit();
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CProductionDeadKraken::Update()
{
    TimeCounter(200);

    if (GetEnd())
    {
        CManager::GetInstance()->GetGame()->GameEnd();
    }
}