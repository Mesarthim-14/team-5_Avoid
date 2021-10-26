#ifndef _GAUGE_H_
#define _GAUGE_H_
//=====================================================================
//
//	ゲージ処理[gauge.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "scene2d.h"

//=====================================================================
// クラス定義
//=====================================================================
class CGauge : public CScene2D
{
public:
	CGauge();
	~CGauge();
	//========================
	// メンバ関数
	//========================
	static CGauge * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetDown(float down) { m_fDown = down; }
	float GetDown(void) { return m_fDown; }

private:
	void SetVertexGauge(void);		// ゲージ減算処理
	void SetDownUp(void);			// テスト減る処理

	//========================
	// メンバ変数
	//========================
	float m_fDown;		// ゲージ量
	float m_fSave;		// 減る量
};


#endif // !_GAUGE_H_