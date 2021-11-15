#ifndef _BULR_FILTER_H_
#define _BULR_FILTER_H_
//=============================================================================
//
// ブラークラス [blur_filter.h]
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
class CBlurFilter : public CShaderSquare
{
public:
	CBlurFilter(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters);
	CBlurFilter(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height);
	~CBlurFilter();
	void Uninit();
	void Restore();
	HRESULT Load();
	void SetTexel(float TU, float TV);
	void Render(UINT Pass);
	BOOL IsOK();
	LPD3DXEFFECT GetEffect() { return m_pEffect; };

private:
	LPD3DXEFFECT m_pEffect;
	D3DXHANDLE m_pTechnique, m_pTU, m_pTV;
	LPDIRECT3DDEVICE9 m_pd3dDevice;
};
#endif