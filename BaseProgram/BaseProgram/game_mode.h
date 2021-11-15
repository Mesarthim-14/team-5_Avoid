#ifndef _GAME_MODE_H_
#define _GAME_MODE_H_
//=======================================================================================
//
// ゲームモードクラス [game_mode.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// ゲームクラス
//=======================================================================================
class CGameMode
{
public:

	// ゲームのモード
	enum GAME_MODE
	{
		GAME_MOVE_NONE = -1,	// 初期値
		GAME_MOVE_NORMAL,		// 通常状態
		GAME_MOVE_CANNON,		// 大砲を打ってる状態
		GAME_MOVE_MAX			// 最大値
	};

	CGameMode();		// コンストラクタ
	~CGameMode();		// デストラクタ

	static CGameMode* Create();												// インスタンス生成
	HRESULT Init();															// 初期化処理
	void Update();															// 更新処理
	void SetMode(const GAME_MODE &GameMode) { m_GameMode = GameMode; }	// ゲームモードの設定
	inline GAME_MODE GetMode()const			{ return m_GameMode; }		// ゲームモードの状態
	
private:
	void NormalUpdate();
	void CannonUpdate();

	GAME_MODE m_GameMode;			// ゲームモード

	typedef void (CGameMode::*UPDATE_FUNC)();
	vector<UPDATE_FUNC> m_UpdateMode = 
	{ &CGameMode::NormalUpdate, &CGameMode::CannonUpdate};
};
#endif