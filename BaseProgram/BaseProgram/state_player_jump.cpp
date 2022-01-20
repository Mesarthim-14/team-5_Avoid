//=====================================================================
//
//    ジャンプ状態管理クラス [state_player_jump.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player_jump.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "state_player_normal.h"
#include "gauge.h"
#include "plane_jump.h"
#include "plane_jumpreservoir.h"
#include "mouse.h"
#include "state_player_avoid.h"
#include "sound.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define CHARGEJUMP_MAX      (100)   // タメカウント最大
#define PARTICLE_STRAT      (30)    // 溜めエフェクト発生開始までの時間
#define HIGHJUMP_CONSUME    (20)    // ためジャンプした時のライフ減少量
#define SOUND_INTER         (60)    // 音の間隔

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateJump::CPlayerStateJump()
{
    m_fJumpTimeCount = 0.0f;
    m_bJumpCheck = false;
    m_nChargeJumpCount = 0;
    m_bIsReadyChargeJump = false;
    m_fJumpValue = 30.0f;
    m_fDushJumpValue = 1.0f;
    m_bJumpEffect = true;
    m_nCntEffect = 0;
}

//=====================================================================
// デストラクタ
//=====================================================================
CPlayerStateJump::~CPlayerStateJump()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CPlayerStateJump * CPlayerStateJump::Create()
{
    // メモリ確保
    CPlayerStateJump *pStateJump = new CPlayerStateJump;
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
void CPlayerStateJump::Init()
{
    //// アニメーション設定
    //SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_JUMP), 60);

    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        // 状態の設定
        pPlayer->SetState(CPlayer::JUMP);
    }
}

//=====================================================================
// 更新処理
//=====================================================================
void CPlayerStateJump::Update()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    // 着地時の処理
    if (pPlayer->GetLanding() && m_bJumpCheck)
    {
        pPlayer->ChangeState(CPlayerStateNormal::Create());
        return;
    }

    // ジャンプ処理
    JumpProcess(pPlayer);

    // ジャンプ処理
    Avoidance(pPlayer);

    if (m_bJumpCheck)
    { // ジャンプし始めているとき
        // ジャンプ時間をカウント
        m_fJumpTimeCount++;
    }
}

//=====================================================================
// ライフの減算
//=====================================================================
void CPlayerStateJump::SubLife(CPlayer* &pPlayer)
{
    CGauge * pGauge = CManager::GetInstance()->GetGame()->GetGauge();

    // Hp消費
    pPlayer->SubLife(HIGHJUMP_CONSUME);
    pGauge->SetDown((float)HIGHJUMP_CONSUME);
    pGauge->SetHitDown(true);
}

//=====================================================================
// ジャンプ中の処理
//=====================================================================
void CPlayerStateJump::JumpProcess(CPlayer* &pPlayer)
{
    // キーボード移動処理
    MoveByKeyboard(pPlayer);
    D3DXVECTOR3 move = pPlayer->GetMove();
    D3DXVECTOR3 pos = pPlayer->GetPos();

    if (CLibrary::KeyboardPress(DIK_SPACE) && !m_bJumpCheck)
    {
        m_nChargeJumpCount++;

		// アニメーション設定
		SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_TAME), CHARGEJUMP_MAX, false);

        // エフェクトの発生時間
        if (m_nChargeJumpCount >= PARTICLE_STRAT && m_nChargeJumpCount <= CHARGEJUMP_MAX && m_bJumpEffect)
        {
            m_bJumpEffect = false;
            CPlaneJumpReservoir::Create(pos);
        }
        if (!m_bJumpEffect)
        {
            JumpEffect();
        }

        if (m_nChargeJumpCount > CHARGEJUMP_MAX)
        {
            // アニメーション設定
            SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_TAME_END), 60);
        }

        // 音の再生
        if (m_nChargeJumpCount % SOUND_INTER == 0)
        {
            CLibrary::SetSound(CSound::SOUND_SE_JUMP_CHARGE);
        }
    }

    if (CLibrary::KeyboardRelease(DIK_SPACE) && !m_bJumpCheck)//通常ジャンプ
    {
        //エフェクト発生
        if (m_nChargeJumpCount >= CHARGEJUMP_MAX)
        {
            m_bIsReadyChargeJump = true;
            pPlayer->SetLanding(false);

            CPlaneJump::Create(D3DXVECTOR3(pos.x, pos.y, pos.z));
            m_bJumpCheck = true;
            move.y += m_fJumpValue * 3;
            move.x += move.x * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
            move.z += move.z * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
            //    pPlayer->SetState(CPlayer::STATE_JUMP);
            m_nChargeJumpCount = 0;
            m_bIsReadyChargeJump = false;

            // ライフの減算
            SubLife(pPlayer);

            CLibrary::SetSound(CSound::SOUND_SE_SUPER_JUMP);
        }
        else
        {
            m_bJumpCheck = true;
            move.y += m_fJumpValue;
            m_nChargeJumpCount = 0;
            CLibrary::SetSound(CSound::SOUND_SE_JUMP);
        }
        pPlayer->SetLanding(false);
    }
    // 移動量の設定
    pPlayer->SetMove(move);
}

//=====================================================================
// 回避処理
//=====================================================================
void CPlayerStateJump::Avoidance(CPlayer* &pPlayer)
{
    CMouse *pMouse = CManager::GetInstance()->GetMouse();   // マウス
    if (pMouse->GetButtonTrigger(CMouse::MOUSE_LEFT))//回避
    {
        if (pPlayer->GetSlimeState() != CPlayer::SLIME_LITTLESIZE)
        {
            pPlayer->ChangeState(CPlayerStateAvoid::Create());
        }
    }
}

//=====================================================================
// エフェクト処理
//=====================================================================
void CPlayerStateJump::JumpEffect()
{
    m_nCntEffect++;
    if (m_nCntEffect >= 20)
    {
        m_bJumpEffect = true;
        m_nCntEffect = 0;
    }
}
