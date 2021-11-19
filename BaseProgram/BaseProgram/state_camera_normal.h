#ifndef _STATE_CAMERA_NORMAL_H_
#define _STATE_CAMERA_NORMAL_H_
//=====================================================================
//
//	通常カメラ状態管理クラス [state_camera_normal.h]
//	Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_camera.h"

//=====================================================================
// 前方宣言
//=====================================================================
class CCamera;

//=====================================================================
// クラス定義
//=====================================================================
class CCameraStateNormal : public CCameraState
{
public:
	CCameraStateNormal();					// コンストラクタ
	~CCameraStateNormal();					// デストラクタ
	static CCameraStateNormal* Create();	// インスタンス生成

	void Init();			// 初期化処理
	void Update()override;	// 更新処理

private:
	// private関数
	void MouseUpdate(CCamera* &pCamera);	// マウスの更新処理
	void KeyBoardMove(CCamera* &pCamera);	// キーボードの更新処理
	void ShowInfo();						// 情報

	// メンバ変数
	bool m_bMouseCountrol;					// マウスのフラグ
};
#endif