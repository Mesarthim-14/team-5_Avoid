#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=====================================================
//
// ビルボードクラスヘッダー [billboard.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "scene_base.h"

//=====================================================
// ビルボードクラス
//=====================================================
class CBillboard : public CSceneBase
{
public:
	CBillboard(PRIORITY Priority = PRIORITY_EFFECT);			// コンストラクタ
	~CBillboard();												// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	virtual void Uninit(void);									// 終了処理
	virtual void Update(void);									// 更新処理
	virtual void Draw(void);									// 描画処理
	
	void InitAnimation(D3DXVECTOR2 TexInfo, int nLoop);			// アニメーション情報初期化
	void UpdateAnimation(void);									// アニメーションの更新
	
	// Set関数
	void SetMove(D3DXVECTOR3 move)			{ m_move = move; }				// 移動量設定
	void SetSizeBase(D3DXVECTOR3 sizeBase)	{ m_sizeBase = sizeBase; }		// サイズのベース
	void SetAlphaNum(int nAlphaNum)			{ m_nAlphaNum = nAlphaNum; }	// アルファテストの値
	void SetBlend(bool bBlend)				{ m_bBlend = bBlend; }			// 加算合成
	void SetLife(int nLife)					{ m_nLife = nLife; }			// 体力の設定
	void SetColor(D3DXCOLOR col);											// 色の設定

	// Get関数
	D3DXVECTOR3 GetMove(void)				{ return m_move; }				// 移動量情報
	int GetLife(void)						{ return m_nLife; }				// ライフの情報

private:
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_sizeBase;		// サイズのベース
	D3DXMATRIX m_mtxWorld;		// 行列計算用
	int m_nCountAnim;			// アニメーションテクスチャ
	int m_nCountAnimPattern;	// アニメーションのパターン
	int m_nCounterAnim;			// アニメーションのカウンター
	int m_nPatternAnim;			// アニメーションのパターン数
	int m_nLoop;				// ループするか
	int m_nLife;				// ライフ
	int m_nAlphaNum;			// アルファテストの値
	bool m_bBlend;				// 加算合成
};

#endif