//=====================================================================
//
//    気絶状態管理クラス [state_player_stun.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player_stun.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "state_player_normal.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define MAX_STAN_COUNT (120)    // 復帰までのカウント

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateStun::CPlayerStateStun()
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CPlayerStateStun::~CPlayerStateStun()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CPlayerStateStun * CPlayerStateStun::Create()
{
    // メモリ確保
    CPlayerStateStun *pStateJump = new CPlayerStateStun;
    if (pStateJump)
    {
        // 初期化処理
        pStateJump->Init();
        return pStateJump;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CPlayerStateStun::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);

    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        // 状態の設定
        pPlayer->SetState(CPlayer::STUN);
    }
}

//=====================================================================
// 更新処理
//=====================================================================
void CPlayerStateStun::Update()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    // 慣性
    D3DXVECTOR3 move = pPlayer->GetMove();
    if (abs(move.x) > 0.0f)//滑らせる
    {
        if (move.x > 0.0f)
        {
            move.x -= 2.0f;
        }
        if (move.x < 0.0f)
        {
            move.x += 2.0f;
        }
    }
    if (abs(move.z) > 0.0f)
    {
        if (move.z > 0.0f)
        {
            move.z -= 2.0f;
        }
        if (move.z < 0.0f)
        {
            move.z += 2.0f;
        }
    }

    // 移動量設定
    move += (pPlayer->GetInertia() - move) * pPlayer->GetInertiaNum();
    pPlayer->SetMove(move);

    // 状態カウンタ
    if (CounterFunc(MAX_STAN_COUNT, this))
    {
        pPlayer->ChangeState(CPlayerStateNormal::Create());// スタン状態解除（起き上がり）
    }
}