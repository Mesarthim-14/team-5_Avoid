#ifndef _TEXTURE_ANIMATION_H_
#define _TEXTURE_ANIMATION_H_
//=============================================================================
//
// テクスチャのアニメーションクラス [texture_animation.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// クラス定義
//=============================================================================
class CTextureAnimation
{
public:
	CTextureAnimation();	// コンストラクタ
	~CTextureAnimation();	// デストラクタ

	static CTextureAnimation *Create(D3DXVECTOR2 m_tex[NUM_VERTEX]);						// インスタンス生成
	void Update(void);																		// 更新処理

	void InitAnimationInfo(const int nPatternNum, const int nSpeed, const int nLoop);		// アニメーションの情報設定
	void InitScroll(const int nSpeed, const float fDivision);								// スクロール情報の設定
	void UpdateAnimation(void);																// アニメーションの更新
	void UpdateScroll(void);																// スクロールの更新
	
	// Set関数
	void SetCountAnim(const int nCountAnim)			{ m_nCountAnim = nCountAnim; }				// アニメーションのカウンタ設定
	void SetCountPattern(const int nCountPattern)	{ m_nCountAnimPattern = nCountPattern; }	// アニメーションパターンのカウント
	void SetScrollCounter(const int nScrollCounter)	{ m_nScrollCounter = nScrollCounter; }		// スクロールの情報
	void SetUpdateFlag(const bool bFlag)			{ m_bUpdate = bFlag; }						// 更新のフラグ設定

	// Get関数
	D3DXVECTOR2 GetTex(int nCount)	{ return m_tex[nCount]; }	// テクスチャ座標の情報
	bool GetEnd(void)				{ return m_bEnd; }			// 終了フラグ
	bool GetUpdate(void)			{ return m_bUpdate; }		// 更新されたかのフラグ

private:
	D3DXVECTOR2 m_tex[NUM_VERTEX];		// 頂点数分のテクスチャ情報
	int m_nCountAnim;					// アニメーションのカウンタ
	int m_nCountAnimPattern;			// アニメーションのパターン
	int m_nPatternNum;					// アニメーションのカウンター
	int m_nAnimSpeed;					// アニメーションのパターン数
	int m_nLoop;						// ループするかどうか
	int m_nSpeedTexture;				// テクスチャの移動速度
	int m_nScrollCounter;				// スクロールのカウンタ
	float m_fDivisionCounter;			// スクロールのカウンター
	float m_fDivisionBaseNum;			// スクロールの間隔
	bool m_bEnd;						// 終了フラグ
	bool m_bUpdate;						// テクスチャが更新されたかのフラグ
};

#endif