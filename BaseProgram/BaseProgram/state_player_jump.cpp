//=====================================================================
//
//	ジャンプ状態管理クラス [state_player_jump.h]
//	Author : Konishi Yuuto
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

//=====================================================================
// マクロ定義
//=====================================================================
#define CHARGEJUMP_MAX		(100)							// タメカウント最大
#define HIGHJUMP_CONSUME	(1)								// ためジャンプした時のライフ減少量

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateJump::CPlayerStateJump()
{
	m_fJumpTimeCount = 0.0f;
	m_bJumpCheck = false;
	m_nChargeJumpCount = 0;
	m_bIsReadyChargeJump = false;
	m_fJumpValue = 72.0f;
	m_fDushJumpValue = 0.0f;
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
	// アニメーション設定
	SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_JUMP), 60);
//	Update();
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

	// ジャンプ処理
	JumpProcess(pPlayer);

	// 着地時の処理
	if (pPlayer->GetLanding() && m_bJumpCheck)
	{
		pPlayer->ChangeState(CPlayerStateNormal::Create());
	}
}

//=====================================================================
// ライフの減算
//=====================================================================
void CPlayerStateJump::SubLife(CPlayer* &pPlayer)
{
	// Hp消費
	pPlayer->SubLife(HIGHJUMP_CONSUME);
}

//=====================================================================
// ジャンプ中の処理
//=====================================================================
void CPlayerStateJump::JumpProcess(CPlayer* &pPlayer)
{
	// キーボード移動処理
	MoveByKeyboard(pPlayer);
	D3DXVECTOR3 move = pPlayer->GetMove();

	//ジャンプ中の処理
	//	JumpProcess(move);

	if (CLibrary::KeyboardPress(DIK_SPACE))
	{
		m_nChargeJumpCount++;

		//エフェクト発生
		if (m_nChargeJumpCount >= CHARGEJUMP_MAX)
		{
			m_bIsReadyChargeJump = true;
			pPlayer->SetLanding(false);
		}
	}

	if (CLibrary::KeyboardPress(DIK_SPACE) && m_bIsReadyChargeJump == true)//ため状態で離したら
	{
		m_bJumpCheck = true;
		move.y += m_fJumpValue * 3;
		move.x += move.x * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
		move.z += move.z * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
		//	pPlayer->SetState(CPlayer::STATE_JUMP);
		m_nChargeJumpCount = 0;
		m_bIsReadyChargeJump = false;

		// ライフの減算
		SubLife(pPlayer);
	}

	else if (CLibrary::KeyboardRelease(DIK_SPACE))//通常ジャンプ
	{
		m_bJumpCheck = true;
		move.y += m_fJumpValue;
		//move.x += move.x * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
		//move.z += move.z * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
		//m_fJumpTimeCount += 1.0f;
		//move.y = 0.5f * CGame::GetGravity()*m_fJumpTimeCount*m_fJumpTimeCount + m_fJumpValue*m_fJumpTimeCount;
		//SetState(STATE_JUMP);
		m_nChargeJumpCount = 0;
		pPlayer->SetLanding(false);
	}

	// 移動量の設定
	pPlayer->SetMove(move);
}