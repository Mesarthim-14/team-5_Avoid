//=======================================================================================
//
// クラーケンが怒る演出 [production_angry_kraken.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "production_angry_kraken.h"
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
#include "kraken.h"
#include "state_kraken_normal.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CProductionAngryKraken::CProductionAngryKraken()
{
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CProductionAngryKraken::~CProductionAngryKraken()
{
}

//=======================================================================================
// インスタンス生成
//=======================================================================================
CProductionAngryKraken * CProductionAngryKraken::Create()
{
    // メモリ確保
    CProductionAngryKraken *pProductionCannon = new CProductionAngryKraken;
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
void CProductionAngryKraken::Init()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();

    CreateState(pPlayer, CPlayerStateNotMove::Create());
    CreateState(pCamera, CCameraStateAngryKraken::Create());

    CLibrary::SetSound(CSound::SOUND_SE_SCREAM);
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CProductionAngryKraken::Uninit()
{
    CProduction::Uninit();
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CProductionAngryKraken::Update()
{
    TimeCounter(100);

    if (GetEnd())
    {
        CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
        CreateState(pPlayer, CPlayerStateNormal::Create());

        CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
        CreateState(pCamera, CCameraStateNormal::Create());

        CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
        CreateState(pKraken, CKrakenStateNormal::Create());
    }
}