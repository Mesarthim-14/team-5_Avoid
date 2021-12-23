//=====================================================================
//
// リスポーン状態 [state_player_respawn.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player_respawn.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "game.h"
#include "gimmick_factory.h"
#include "check_point.h"
#include "state_player_normal.h"
#include "move_scaffold.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define END_LIMIT   (60)   // 終了の時間

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateRespawn::CPlayerStateRespawn()
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CPlayerStateRespawn::~CPlayerStateRespawn()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CPlayerStateRespawn * CPlayerStateRespawn::Create()
{
    // メモリ確保
    CPlayerStateRespawn *pState = new CPlayerStateRespawn;
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
void CPlayerStateRespawn::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CGame* pGame = (CGame*)CManager::GetInstance()->GetModePtr();
    if (!pPlayer || !pGame)
    {
        return;
    }
    D3DXVECTOR3 CheckPointPos = pGame->GetGimmickFactory()->GetCheckPoint()->GetPointPos();
    // 座標の取得
    pPlayer->SetPos(D3DXVECTOR3(CheckPointPos.x, CheckPointPos.y + (600 / 2), CheckPointPos.z));

    // 座標の取得
    pPlayer->SetPos(pGame->GetGimmickFactory()->GetCheckPoint()->GetPointPos());
    pPlayer->SetMove(ZeroVector3);
    pPlayer->SetCollision(false);

    // 状態の設定
    pPlayer->SetState(CPlayer::RESPAWN);

    CMoveScaffold* pScaffold = pGame->GetGimmickFactory()->GetMoveScaffold();
    if (pScaffold)
    {
        pScaffold->Respawn();
    }
}

//=====================================================================
// 更新処理
//=====================================================================
void CPlayerStateRespawn::Update()
{
    // プレイヤー情報取得
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        // 終了フラグを立てる
        if (CounterFunc(END_LIMIT, this))
        {
            pPlayer->ChangeState(CPlayerStateNormal::Create());
        }
    }
}