//=====================================================================
//
// プレイヤー動けない状態 [state_player_not_move.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player_not_move.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateNotMove::CPlayerStateNotMove()
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CPlayerStateNotMove::~CPlayerStateNotMove()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CPlayerStateNotMove * CPlayerStateNotMove::Create()
{
    // メモリ確保
    CPlayerStateNotMove *pState = new CPlayerStateNotMove;
    if (pState)
    {
        // 初期化処理
        pState->Init();
        return pState;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CPlayerStateNotMove::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        pPlayer->SetMove(ZeroVector3);
        pPlayer->SetCollision(false);
    }
}

//=====================================================================
// 更新処理
//=====================================================================
void CPlayerStateNotMove::Update()
{

}