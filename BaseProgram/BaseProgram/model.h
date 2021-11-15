#ifndef _MODEL_H_
#define _MODEL_H_
//=============================================================================
//
// モデルクラス [model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModelInfo;

//=============================================================================
// モデルクラス
//=============================================================================
class CModel : public CScene
{
public:
	CModel(PRIORITY Priority);	// コンストラクタ
	virtual ~CModel();

	virtual HRESULT Init(void);									// 初期化処理
	virtual void Uninit(void);									// 終了処理
	virtual void Update(void);									// 更新処理
	virtual void Draw(void);									// 描画処理
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// インスタンス生成

	// Get関数
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetRot();
	CModelInfo* GetModelInfo(void) { return m_pModelInfo; }		// モデルの情報

protected:
	bool PlayerDisCollision(const float &fDistanse);							// プレイヤーとの距離の当たり判定

	// Set関数
	void SetMove(const D3DXVECTOR3 move)	{ m_move = move; }					// 移動量の設定
	void SetSize(D3DXVECTOR3 size)			{ m_size = size; }					// サイズの設定
	void SetTexPattern(int TexPattern)		{ m_nTexPattern = TexPattern; }		// テクスチャのパターン
	void SetLife(int nLife)					{ m_nLife = nLife; }				// ライフの設定
	void SetScale(D3DXVECTOR3 scale)		{ m_scale = scale; }				// 拡大率

	D3DXVECTOR3 &GetMove(void)			{ return m_move; }				// 移動量の情報
	D3DXVECTOR3 GetSize(void)const		{ return m_size; }				// サイズの設定
	int GetTexPattern(void)				{ return m_nTexPattern; }		// テクスチャ
	int GetLife(void)					{ return m_nLife; }				// ライフの設定

private:
	// private関数
	void HasPtrDelete(void);									// 保持ポインタの開放処理
	void CreateInfoPtr(void);									// 情報のポインタ生成

	// メンバ変数
	CModelInfo* m_pModelInfo;			// モデルの情報
	D3DXVECTOR3 m_move;					// 移動量
	D3DXVECTOR3 m_size;					// サイズ
	D3DXVECTOR3 m_scale;				// 拡大率
	int m_nTexPattern;					// テクスチャのパターン数
	int m_nLife;						// ライフ
};
#endif 