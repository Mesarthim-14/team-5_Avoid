//=======================================================================================
//
// 会話時の演出 [production_npc_talk.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "production_npc_talk.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "gimmick_factory.h"
#include "player.h"
#include "camera_game.h"
#include "state_player_normal.h"
#include "state_camera_normal.h"
#include "cannon_bullet.h"
#include "cannon.h"
#include "cannon_manager.h"
#include "kraken.h"
#include "state_kraken_not_attack.h"
#include "state_kraken_normal.h"
#include "state_player_not_move.h"
#include "state_camera_talk.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CProductionNpcTalk::CProductionNpcTalk()
{
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CProductionNpcTalk::~CProductionNpcTalk()
{
}

//=======================================================================================
// インスタンス生成
//=======================================================================================
CProductionNpcTalk * CProductionNpcTalk::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // メモリ確保
    CProductionNpcTalk *pProductionCannon = new CProductionNpcTalk;
    if (pProductionCannon)
    {
        // インスタンス生成
        pProductionCannon->Init(pos, rot);
        return pProductionCannon;
    }

    return nullptr;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
void CProductionNpcTalk::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CreateState(pPlayer, CPlayerStateNotMove::Create());

    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
    CreateState(pCamera, CCameraStateTalk::Create(pos, rot));

    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    CreateState(pKraken, CKrakenStateNotAttack::Create());
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CProductionNpcTalk::Uninit()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CreateState(pPlayer, CPlayerStateNormal::Create());

    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
    CreateState(pCamera, CCameraStateNormal::Create());

    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    CreateState(pKraken, CKrakenStateNormal::Create());

    CProduction::Uninit();
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CProductionNpcTalk::Update()
{

}