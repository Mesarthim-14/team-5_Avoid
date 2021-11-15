#ifndef _WATER_FRESNELH_
#define _WATER_FRESNELH_
//=============================================================================
//
// フレネル反射水クラス [water_fresnel.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CWave;
class CParallaxMapping2;
class CBlurFilter;
class CFrenelLambert;
class CShaderSquare;
class CReflect;
class CMask;

//=========================================================================
// クラス定義
//=========================================================================
class CWaterFresnel : public CModel
{
public:
	CWaterFresnel(PRIORITY = PRIORITY_0);	// コンストラクタ
	~CWaterFresnel();						// デストラクタ

	static CWaterFresnel *Create(void);	// インスタンス生成
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 初期化処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画
	void ShowInfo();					// ImgUi

private:
	CWave *m_pWave;					// 海
	CParallaxMapping2 *m_pParallax;	// 視差マップ
	LPD3DXMESH m_WaterMesh;			// 水を移すメッシュ
	CBlurFilter *m_pBlurFilter;		// ブラー
	CFrenelLambert *m_pLambert;			// ランバート
	CShaderSquare *m_pSquObj;		// 平面オブジェクト
	CMask *m_pMask;					// マスク
	CReflect *m_pReflect;			// 反射
	//シーンのレンダリング
	LPDIRECT3DTEXTURE9    m_pColorTexture;
	LPDIRECT3DSURFACE9    m_pColorSurface;
	//反射マップ
	LPDIRECT3DTEXTURE9    m_pReflectTexture;
	LPDIRECT3DSURFACE9    m_pReflectSurface;
	//水面のマスクマップ
	LPDIRECT3DTEXTURE9    m_pWaterTexture;
	LPDIRECT3DSURFACE9    m_pWaterSurface;
	//ブラー処理
	LPDIRECT3DTEXTURE9    m_pBlurFilterTexture;
	LPDIRECT3DSURFACE9    m_pBlurFilterSurface;

	float m_fWaveSpeed;					// 波の速度
	D3DXVECTOR4 m_ReflectPlayerAmbiend;	// 反射の色
	D3DXVECTOR4 m_ReflectSkyAmbiend;	// 反射の色
	float m_fReflectHeight;				// 反射の高さ
	D3DXVECTOR4 m_LambertPlayerAmbiend;	// 反射光の色
	D3DXVECTOR4 m_LambertSkyAmbiend;	// 反射光の色
	D3DXVECTOR4 m_ParallaxAmbiend;		// 視差マップの色
	float m_fParallaxSpecular;			// 広さ
	float m_fParallaxSpecularPower;		// 強さ
	float m_fParallaxHeight;			// 高さ
	float m_fParallaxRefraction;		// 適応度
	float m_fZdistance;					// 最遠近距離
};

#endif