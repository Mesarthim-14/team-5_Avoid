//=====================================================================
//
//    通常状態管理クラス [state_player_normal.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player_normal.h"
#include "player.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "mouse.h"
#include "state_player_avoid.h"
#include "state_player_jump.h"

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateNormal::CPlayerStateNormal()
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CPlayerStateNormal::~CPlayerStateNormal()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CPlayerStateNormal * CPlayerStateNormal::Create()
{
    // メモリ確保
    CPlayerStateNormal *pStateNormal = new CPlayerStateNormal;
    if (pStateNormal)
    {
        // 初期化処理
        pStateNormal->Init();
        return pStateNormal;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CPlayerStateNormal::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);

    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        // 状態の設定
        pPlayer->SetState(CPlayer::NORMAL);
    }
}

//=====================================================================
// 更新処理
//=====================================================================
void CPlayerStateNormal::Update()
{
    // メモリ確保
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    pPlayer->SetCollision(true);
    // キーボード移動処理
    MoveByKeyboard(pPlayer);
    Jump(pPlayer);
    Avoidance(pPlayer);
}

//=====================================================================
// ジャンプ処理
//=====================================================================
void CPlayerStateNormal::Jump(CPlayer* &pPlayer)
{
    if (pPlayer)
    {
        if (pPlayer->GetBoolJump())
        {
            // ためジャンプ
            if (CLibrary::KeyboardTrigger(DIK_SPACE))
            {
                // 状態の設定
                pPlayer->ChangeState(CPlayerStateJump::Create());
            }
        }
    }
}

//=====================================================================
// 回避処理
//=====================================================================
void CPlayerStateNormal::Avoidance(CPlayer* &pPlayer)
{
    CMouse *pMouse = CManager::GetInstance()->GetMouse();   // マウス
    if (pPlayer->GetLanding() == true && pMouse->GetButtonTrigger(CMouse::MOUSE_LEFT))//回避
    {
        if (pPlayer->GetSlimeState() != CPlayer::SLIME_LITTLESIZE)
        {
            pPlayer->ChangeState(CPlayerStateAvoid::Create());
        }
    }
}