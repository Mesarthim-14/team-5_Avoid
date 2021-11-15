#ifndef _WAVE_H_
#define _WAVE_H_
//=============================================================================
//
// 波クラス [wave.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "shader_square.h"

//=============================================================================
// クラス定義
//=============================================================================
class CWave : public CShaderSquare
{
public:
	CWave(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters);	// コンストラクタ
	CWave(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height);				// コンストラクタ
	~CWave();																	// デストラクタ
	void Uninit();																// 終了処理
	void Restore();																// リストア
	HRESULT Load();																// ロード
	void SetWaveSpeed(float SpringPower);										// 波の速度
	void AddWave(float Pos_X, float Pos_Y, float Height);						// 波を与える処理
	LPDIRECT3DTEXTURE9 Draw();													// 描画処理
	HRESULT SetVertexDecl(LPDIRECT3DDEVICE9 pd3dDevice,							// 頂点データの再生成
		const D3DVERTEXELEMENT9 *pDecl, LPD3DXMESH &meshWater, 
		const LPD3DXMESH &mesh);
	LPD3DXEFFECT GetEffect() { return m_pEffect; };

private:
	LPD3DXEFFECT m_pEffect;
	D3DXHANDLE m_pTechnique, m_pTexOffset, m_pSpringPower, m_pAddWavePos, m_pAddWaveHeight;
	//波マップ
	LPDIRECT3DTEXTURE9 m_pWaveMapTexture[2];
	LPDIRECT3DSURFACE9 m_pWaveMapSurface[2];
	//法線マップ
	LPDIRECT3DTEXTURE9 m_pBumpMapTexture;
	LPDIRECT3DSURFACE9 m_pBumpMapSurface;
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	//波マップのインデックス
	int m_RenderTargetIndex;
};

#endif