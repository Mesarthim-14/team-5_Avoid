#ifndef _PRODUCTION_CANNON_H_
#define _PRODUCTION_CANNON_H_
//=======================================================================================
//
// 大砲時の演出クラス [production_cannon.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// 前方宣言
//=======================================================================================
class CPlayerStateCannon;
class CCameraStateCannon;
class CCannon;

//=======================================================================================
// ゲームクラス
//=======================================================================================
class CProductionCannon
{
public:
	CProductionCannon();		// コンストラクタ
	~CProductionCannon();		// デストラクタ

	static CProductionCannon* Create();			// インスタンス生成
	HRESULT Init();								// 初期化処理
	void Update();								// 更新処理
	inline bool GetEnd()const{ return m_bEnd; }	// 終了フラグ

private:
	CPlayerStateCannon *m_pPlayerState;		// プレイヤーの状態
	CCameraStateCannon *m_pCameraState;		// カメラの状態
	int m_nCounter;							// カウンター
	bool m_bEnd;
};
#endif