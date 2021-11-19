#ifndef _STATE_PLAYER_CANNON_H_
#define _STATE_PLAYER_CANNON_H_
//=====================================================================
//
//	大砲時状態管理クラス [state_player_cannon.h]
//	Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player.h"

//=====================================================================
// 前方宣言
//=====================================================================
class CPlayer;

//=====================================================================
// クラス定義
//=====================================================================
class CPlayerStateCannon : public CPlayerState
{
public:
	CPlayerStateCannon();		// コンストラクタ
	~CPlayerStateCannon();		// デストラクタ

	static CPlayerStateCannon* Create();	// インスタンス生成
	void Init();							// 初期化処理
	void Update()override;					// 更新処理
	void TrackingCannon(CPlayer* &pPlayer);	// 大砲の後ろへ追従
private:
	int m_nStunCount;
};
#endif