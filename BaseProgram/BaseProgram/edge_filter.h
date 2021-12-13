#ifndef _EDGE_FILTER_H_
#define _EDGE_FILTER_H_
//=============================================================================
//
// エッジフィルタークラス [edge_filter.h]
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
class CEdgeFilter : public CShaderSquare
{

public:
    CEdgeFilter(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters);
    CEdgeFilter(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height);
    ~CEdgeFilter();
    void Invalidate();
    void Restore();
    HRESULT Load();
    void SetParameters(D3DXVECTOR2* pTexel, float pLimit);
    void Render(LPDIRECT3DTEXTURE9 pBackBuffer, LPDIRECT3DTEXTURE9 pZBuffer);
    BOOL IsOK();
    inline LPD3DXEFFECT GetEffect()const { return m_pEffect; };

private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pTexel, m_pLimit, m_pWVP, m_pLightDir;
    LPDIRECT3DDEVICE9 m_pd3dDevice;
    D3DPRESENT_PARAMETERS* m_pd3dParameters;

};

#endif