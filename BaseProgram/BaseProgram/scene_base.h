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

	virtual void Uninit();															// 終了処理
	virtual void Update();															// 更新処理
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	// テクスチャの設定

	// 純粋仮想関数
	virtual HRESULT Init() = 0;																		// 初期化処理
	virtual void Draw() = 0;																		// 描画処理
	virtual void InitAnimation(const int &nPatternNum, const int &nSpeed, const int &nLoop) = 0;	// アニメーションの設定
	virtual void UpdateAnimation() = 0;																// アニメーションの更新

protected:
	void SetSceneInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);	// シーン情報の設定

	// Set関数
	inline virtual void SetPos(const D3DXVECTOR3 &pos)					{ m_pos = pos; }				// 座標
	inline virtual void SetSize(const D3DXVECTOR3 &size)				{ m_size = size; }				// サイズ
	inline virtual void SetRot(const D3DXVECTOR3 &rot)					{ m_rot = rot; }				// 角度		
	inline virtual void SetColor(const D3DXCOLOR &col)					{ m_col = col; }				// 色
	inline void BindVtxBuff(const LPDIRECT3DVERTEXBUFFER9 pVtxBuff)		{ m_pVtxBuff = pVtxBuff; }		// 頂点バッファ
	inline void SetTextureAnimationPtr(CTextureAnimation* pPtr)			{ m_pTextureAnimation = pPtr; }	// ポインタ取得

	// Get関数
	inline D3DXVECTOR3 GetPos()const						{ return m_pos; }				// 座標
	inline D3DXVECTOR3 GetSize()const						{ return m_size; }				// サイズ
	inline D3DXVECTOR3 GetRot()const						{ return m_rot; }				// 回転量
	inline D3DXCOLOR &GetColor()							{ return m_col; }				// 色
	inline LPDIRECT3DTEXTURE9 GetTexture()const				{ return m_pTexture; }			// テクスチャ
	inline LPDIRECT3DVERTEXBUFFER9 GetVtxBuff()const		{ return m_pVtxBuff; }			// バッファ情報
	inline CTextureAnimation*GetTextureAnimationPtr()const	{ return m_pTextureAnimation; }	// テクスチャポインタ

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