#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
// 3Dポリゴンクラスヘッダー [scene3D.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene_base.h"

//=========================================================================
// 3Dポリゴンクラス
//=========================================================================
class CScene3D :public CSceneBase
{
public:
	CScene3D(PRIORITY Priority = PRIORITY_EFFECT);	// コンストラクタ
	virtual ~CScene3D();							// デストラクタ
	
	virtual HRESULT Init(void);						// 初期化処理
	virtual void Uninit(void);						// 終了処理
	virtual void Update(void);						// 更新処理
	virtual void Draw(void) = 0;					// 描画処理

protected:
	void SetVertexPos(void);						// 座標の更新

	// Set関数
	void SubAlpha(float fAlphaNum);												// 透明度の減算
	void InitAnimation(int nPatternNum, int nSpeed, int nLoop);					// アニメーション情報初期化
	void SetColor(D3DXCOLOR color);												// カラーの設定
	void ScaleUp(float fScale);													// 拡大処理
	void SetMove(D3DXVECTOR3 move)			{ m_move = move; }					// 移動量
	void SetAlpha(bool bAlpha)				{ m_bAlpha = bAlpha; }				// アルファテスト
	void SetAlphaNum(int nAlphaNum)			{ m_nAlphaTestNum = nAlphaNum; }	// アルファテストの値
	void SetBlend(bool bBlend)				{ m_bBlend = bBlend; }				// 加算合成
	void SetMtxWorld(D3DXMATRIX mtxWorld)	{ m_mtxWorld = mtxWorld; }			// ワールドマトリクスの設定

	// Get関数
	D3DXMATRIX GetMtxWorld(void)	{ return m_mtxWorld; }				// ワールドマトリクス
	int GetAlphaTestNum(void)		{ return m_nAlphaTestNum; }			// アルファテストの値

private:
	// private関数
	void CreateVertex(void);						// 頂点の設定
	void UpdateAnimation(void);						// アニメーションの更新

	// メンバ変数
	D3DXMATRIX	m_mtxWorld;		// ワールドマトリクス
	D3DXVECTOR3 m_move;			// 移動量
	int m_nLife;				// ライフ
	int m_nAlphaTestNum;		// 透明の値
	float m_fScaleNum;			// 拡大値
	float m_fAlphaNum;			// 透明度
	bool m_bAlpha;				// 透明を使うフラグ
	bool m_bBlend;				// 加算合成
};
#endif