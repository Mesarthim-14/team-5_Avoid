//=====================================================================
//
//	通常状態管理クラス [state_player_normal.h]
//	Author : Konishi Yuuto
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

	// キーボード移動処理
	MoveByKeyboard(pPlayer);
}