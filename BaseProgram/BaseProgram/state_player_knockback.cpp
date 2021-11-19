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
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "state_player_normal.h"

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateKnockback::CPlayerStateKnockback()
{
    m_nStanCount = 0;
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
CPlayerStateKnockback * CPlayerStateKnockback::Create()
{
    // メモリ確保
    CPlayerStateKnockback *pStateJump = new CPlayerStateKnockback;
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
void CPlayerStateKnockback::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
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

    D3DXVECTOR3 move = pPlayer->GetMove();
}