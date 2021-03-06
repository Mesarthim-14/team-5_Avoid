//=====================================================================
//
//    回避状態管理クラス [state_player_avoid.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player_avoid.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "mouse.h"
#include "state_player_normal.h"
#include "state_player_stun.h"
#include "gauge.h"
#include "sound.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define AVOID_CONSUME (5)   // 回避した時のライフ減少量

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateAvoid::CPlayerStateAvoid()
{
    m_fAvoidValueY = 15.0f;
    m_fAvoidValueXZ = 50.0f;
}

//=====================================================================
// デストラクタ
//=====================================================================
CPlayerStateAvoid::~CPlayerStateAvoid()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CPlayerStateAvoid * CPlayerStateAvoid::Create()
{
    // メモリ確保
    CPlayerStateAvoid *pStateAvoid = new CPlayerStateAvoid;
    if (pStateAvoid)
    {
        // 初期化処理
        pStateAvoid->Init();
        return pStateAvoid;
    }

    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CPlayerStateAvoid::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_AVOID), 60);
    SetMove();
    Update();

    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        // 状態の設定
        pPlayer->SetState(CPlayer::AVOID);
    }
}

//=====================================================================
// 更新処理
//=====================================================================
void CPlayerStateAvoid::Update()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    if (pPlayer->GetLanding())
    {
        pPlayer->ChangeState(CPlayerStateStun::Create());
    }
}

//=====================================================================
// 移動量設定
//=====================================================================
void CPlayerStateAvoid::SetMove()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    CGauge *pGauge = CManager::GetInstance()->GetGame()->GetGauge();
    if (!pPlayer)
    {
        return;
    }

    D3DXVECTOR3 move = pPlayer->GetMove();

    float fRot = pPlayer->GetRot().y;
    move.y += m_fAvoidValueY;
    move.x += sinf(fRot) * -m_fAvoidValueXZ;
    move.z += cosf(fRot) * -m_fAvoidValueXZ;
    pPlayer->SetMove(move);
    pPlayer->SetLanding(false);

    pPlayer->SubLife(AVOID_CONSUME);
    pGauge->SetDown((float)AVOID_CONSUME);
    pGauge->SetHitDown(true);
    CLibrary::SetSound(CSound::SOUND_SE_AVOID);
}
