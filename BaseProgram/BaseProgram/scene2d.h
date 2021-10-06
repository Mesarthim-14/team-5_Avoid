#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//=======================================================================================
// 
// 2Dポリゴンクラス処理 [scene2d.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "scene_base.h"

//=======================================================================================
// シーン2Dクラス定義
//=======================================================================================
class CScene2D : public CSceneBase
{
public:
	CScene2D(PRIORITY Priority = PRIORITY_0);									// コンストラクタ
	~CScene2D();																// デストラクタ

	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// インスタンス生成
	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fFadeNum);	// インスタンス生成(フェード有り)

	HRESULT Init(void);													// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理

protected:
	void SetVertexPos(void);												// 頂点の設定
	void InitAnimation(int nPatternNum, int nSpeed, int nLoop);			// アニメーション情報初期化
	void InitScroll(int nSpeed, float fDivision);						// 画像スクロールの設定
	void ScaleUp(float fScaleUp);										// 拡大関数
	void FlashPolygon(int nFlashFlame);									// ポリゴンの点滅

	// Set関数
	void SetColor(const D3DXCOLOR &col) override;						// 色の設定
	void SetRotation(float rotasion);									// 回転の設定
	void SetScale(const float &fScale);									// 拡大の値設定
	void SetSubFlashNum(float fSubNum) { m_fSubNum = fSubNum; }			// 点滅の値設定

	// Get関数
	float GetScale(void) { return m_fScaleNum; }						// 拡大の値情報
private:
	// private関数
	void CreateVertex(void);											// 頂点の生成
	void UpdateAnimation(void);											// アニメーションの更新
	void UpdateScroll(void);											// 画像スクロールの更新
	void FadeOut(float fSpeed);											// フェードアウト

	// メンバ変数
	int m_nFlashFlame;			// 点灯用のカウンター
	float m_fRotasion;			// 回転用変数
	float m_fScaleNum;			// 拡大用変数
	float m_fSubFlashNum;		// ポリゴンの点灯用
	float m_fSubNum;			// ポリゴンの点灯用
	float m_fFadeSpeedNum;		// フェードのスピード
	bool m_bDisappearFlag;		// 点滅用のフラグ
	bool m_bFadeOut;			// フェードのフラグ
};

#endif // !_SCENE2D_H_