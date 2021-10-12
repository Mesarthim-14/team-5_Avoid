#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
//=============================================================================
//
// ゲームカメラクラスヘッダー [camera_game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "camera.h"

//=============================================================================
// カメラクラス
//=============================================================================
class CCameraGame : public CCamera
{
public:
	CCameraGame();					// コンストラクタ
	~CCameraGame();					// デストラクタ

	HRESULT Init(void);					// 初期化処理
	static CCameraGame*Create(void);	// クリエイト

private:
	// private関数
	void NomalUpdate(void) override;
	void Tracking(const float &fDistance, float &fVartical,
		float &fHorizontal, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerRot);	// 追従
	void KeyBoardMove(const float &fDistance, float &fVartical,
		float &fHorizontal, D3DXVECTOR3 PlayerPos);											// キーボードの動き
};
#endif 