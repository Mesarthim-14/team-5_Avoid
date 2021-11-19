#ifndef _SHADER_SQUARE_H_
#define _SHADER_SQUARE_H_
//=============================================================================
//
// シェーダ用のポリゴン生成クラス [shader_square.h]
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
class CShaderSquare
{
public:
	CShaderSquare(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters);	// コンストラクタ
	CShaderSquare(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height);				// コンストラクタ
	~CShaderSquare();																	// デストラクタ
	void Uninit();																		// 終了処理

	//2Dポリゴンのサイズを取得
	UINT GetWidth();
	UINT GetHeight();
	//2Dポリゴンのサイズを変更
	HRESULT Resize(UINT Width, UINT Height);
	HRESULT Resize(D3DPRESENT_PARAMETERS* pd3dParameters);
	//初期化
	HRESULT Load();
	//2Dポリゴンをレンダリング
	void Draw();

private:
	//頂点フォーマット
	DWORD D3D2DFVF;

	typedef struct _D3D2DVERTEX
	{
		float x, y, z, rhw;	//頂点座標
		DWORD color;		//頂点カラー
		float tu, tv;		//テクセル
	}D3D2DVERTEX;

	LPDIRECT3DVERTEXBUFFER9 m_pd3d2DVertex;
	LPDIRECT3DDEVICE9 m_pd3dDevice;

	//２Ｄポリゴンのサイズ
	UINT m_Width, m_Height;
};

#endif