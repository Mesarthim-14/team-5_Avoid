#ifndef _MODEL_INFO_H_
#define _MODEL_INFO_H_
//=============================================================================
//
// モデルの情報クラス[model_info.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "xfile.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CShadow;

//=============================================================================
//階層モデルクラス
//=============================================================================
class CModelInfo
{
public:
	CModelInfo();		// コンストラクタ
	~CModelInfo();		// デストラクタ

	static CModelInfo *Create(void);	// インスタンス生成

	HRESULT Init(void);					// 初期化処理
	void Draw(D3DXVECTOR3 rot);			// 描画処理
	void ShadowDraw(D3DXVECTOR3 rot);	// 影の描画
	void CreateShadowPtr(void);			// 影の生成

	// Set関数
	void SetPos(const D3DXVECTOR3 pos)		{ m_pos = pos; }					// 座標
	void SetRot(const D3DXVECTOR3 rot)		{ m_rot = rot; }					// 向き設定
	void SetModel(CXfile::MODEL model)		{ m_model = model; }				// モデル情報の設定
	void SetMtxWorld(D3DXMATRIX mtxWorld)	{ m_mtxWorld = mtxWorld; }			// マトリクスワールド設定
	void SetModelStatus(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model);	// モデル情報の設定
	D3DXMATRIX SetShadowInfo(D3DXVECTOR3 rot, D3DXMATRIX pParent);				// 影の情報の設定

	// Get情報
	D3DXVECTOR3 &GetPos(void)			{ return m_pos; }					// 座標情報
	D3DXVECTOR3 &GetRot(void)			{ return m_rot; }					// 角度の情報
	D3DXMATRIX GetMtxWorld(void)		{ return m_mtxWorld; }				// ワールドマトリクス情報
	D3DXMATRIX GetOldMtxWorld(void)		{ return m_OldMtxWorld; }			// 古いワールドマトリクスの情報
	LPD3DXMESH GetMesh(void)			{ return m_model.pMesh; }			// モデル情報取得
	LPD3DXBUFFER GetBuffMat(void)		{ return m_model.pBuffMat; }		// バッファ情報
	DWORD GetNumMat(void)				{ return m_model.dwNumMat; }		// マトリクスの数
	CXfile::MODEL GetModel(void)		{ return m_model; }					// モデルの情報
	CShadow* GetShadow(void)			{ return m_pShadow; }				// 影のポインタ
	D3DXVECTOR3 GetMtxPos(void);											// マトリクス座標

private:
	// private関数
	void HasPtrDelete(void);			// 保持ポインタの開放処理

	// メンバ変数
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	D3DXMATRIX m_OldMtxWorld;	// 古いワールド座標
	CXfile::MODEL m_model;		// モデル情報

	// 影の生成用
	CShadow *m_pShadow;		// 影のポインタ
	bool m_bUseShadow;		// 影の使用フラグ
};

#endif 