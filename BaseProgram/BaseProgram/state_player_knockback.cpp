//=====================================================================
//
//    気絶状態管理クラス [state_player_knockback.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player_knockback.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "state_player_normal.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define KNOCK_TIME  (150)   // ノックの時間

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateKnockback::CPlayerStateKnockback()
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CPlayerStateKnockback::~CPlayerStateKnockback()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CPlayerStateKnockback * CPlayerStateKnockback::Create(const D3DXVECTOR3& move)
{
    // メモリ確保
    CPlayerStateKnockback *pState = new CPlayerStateKnockback;
    if (pState)
    {
        // 初期化処理
        pState->SetMove(move);
        pState->Init();
        return pState;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CPlayerStateKnockback::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
    CLibrary::SetSound(CSound::SOUND_SE_DAMAGE);
}

//=====================================================================
// 更新処理
//=====================================================================
void CPlayerStateKnockback::Update()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    if (pPlayer->GetLanding())
    {
        pPlayer->ChangeState(CPlayerStateNormal::Create());
    }
}

//=====================================================================
// 移動量設定
//=====================================================================
void CPlayerStateKnockback::SetMove(const D3DXVECTOR3 &move)
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    pPlayer->SetMove(move);
    pPlayer->SetLanding(false);
}