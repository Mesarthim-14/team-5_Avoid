#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_
//=============================================================================
//
// シーンベースクラスヘッダー [scene_base.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CTextureAnimation;

//=============================================================================
// シーンベースクラス
//=============================================================================
class CSceneBase : public CScene
{
public:
	CSceneBase(PRIORITY Priority = PRIORITY_0);										// コンストラクタ
	virtual ~CSceneBase();															// デストラクタ

	virtual void Uninit(void);														// 終了処理
	virtual void Update(void);														// 更新処理
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	// テクスチャの設定

	// 純粋仮想関数
	virtual HRESULT Init(void) = 0;												// 初期化処理
	virtual void Draw(void) = 0;												// 描画処理
	virtual void InitAnimation(int nPatternNum, int nSpeed, int nLoop) = 0;		// アニメーションの設定
	virtual void UpdateAnimation(void) = 0;										// アニメーションの更新

protected:
	void SetSceneInfo(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// シーン情報の設定

	// Set関数
	virtual void SetPos(const D3DXVECTOR3 &pos)					{ m_pos = pos; }				// 座標
	virtual void SetSize(const D3DXVECTOR3 &size)				{ m_size = size; }				// サイズ
	virtual void SetRot(const D3DXVECTOR3 &rot)					{ m_rot = rot; }				// 角度		
	virtual void SetColor(const D3DXCOLOR &col)					{ m_col = col; }				// 色
	void BindVtxBuff(const LPDIRECT3DVERTEXBUFFER9 pVtxBuff)	{ m_pVtxBuff = pVtxBuff; }		// 頂点バッファ
	void SetTextureAnimationPtr(CTextureAnimation* pPtr)		{ m_pTextureAnimation = pPtr; }	// ポインタ取得

	// Get関数
	D3DXVECTOR3 GetPos(void)const					{ return m_pos; }				// 座標
	D3DXVECTOR3 GetSize(void)const					{ return m_size; }				// サイズ
	D3DXVECTOR3 GetRot(void)const					{ return m_rot; }				// 回転量
	D3DXCOLOR &GetColor(void)						{ return m_col; }				// 色
	LPDIRECT3DTEXTURE9 GetTexture(void)				{ return m_pTexture; }			// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void)		{ return m_pVtxBuff; }			// バッファ情報
	CTextureAnimation*GetTextureAnimationPtr(void)	{ return m_pTextureAnimation; }	// テクスチャポインタ

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// バッファ
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_size;						// サイズ
	D3DXCOLOR m_col;						// 色
	D3DXVECTOR3 m_rot;						// 回転量
	CTextureAnimation* m_pTextureAnimation;	// テクスチャアニメーションの情報
};

#endif