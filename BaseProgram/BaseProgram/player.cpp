//=============================================================================
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "fade.h"
#include "resource_manager.h"
#include "motion.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define PLAYER_SPEED			(10.0f)									// プレイヤーの移動量
#define PLAYER_ROT_SPEED		(0.1f)									// キャラクターの回転する速度
#define SIZE					(D3DXVECTOR3 (1200.0f,1000.0f,1200.0f))	// サイズ

//=============================================================================
// 生成処理関数
// Author : Konishi Yuuto
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// メモリ確保
	CPlayer *pPlayer = new CPlayer;

	// nullcheck
	if (pPlayer)
	{
		// 初期化処理
		pPlayer->SetCharacterInfo(pos, rot);
		pPlayer->Init();
		return pPlayer;

	}

	// CPlayerを返す
	return nullptr;
}

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
}

//=============================================================================
// デストラクタ
// Author : Konishi Yuuto
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CPlayer::Init(void)
{
	// CXfile取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// nullcheck
	if (pXfile)
	{
		SetUseShadow();									// 影の使用
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_TEST);	// モデルの生成
		SetShadowRotCalculation();						// 影の向き
	}

	// 初期化処理
	CCharacter::Init();

	// 初期化
	m_rotDest = GetRot();			// 向き
	SetSize(SIZE);					// サイズ設定
	SetSpeed(PLAYER_SPEED);			// スピード設定
	SetType(CHARACTER_TYPE_PLAYER);	// プレイヤー

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();
}

//=============================================================================
// 更新関数処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Update(void)
{
	// 更新
	CCharacter::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 古い位置設定
	SetPosOld(pos);

	// 状態更新
	UpdateState();

	// プレイヤー処理
	PlayerControl();

	// 角度の更新処理
	RotFix();
}

//=============================================================================
// 描画処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画
	CCharacter::Draw();
}

//=============================================================================
// 状態更新
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// プレイヤーの処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PlayerControl()
{

}

//=============================================================================
// 向き更新処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::RotFix(void)
{
	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// 向き
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// 向き設定
	SetRot(rot);
}

//=============================================================================
// 移動処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Move(void)
{

}