#ifndef _CPARALLAX_MAPPING2_H_
#define _CPARALLAX_MAPPING2_H_
//=============================================================================
//
// 視差マッピングクラス [parallax_mapping2.h]
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
class CParallaxMapping2
{
private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pWVPP, m_pWVPPT, m_pLightDir, m_pEyePos, m_pAmbient, m_pSpecular, m_pSpecularPower, m_pHeight, m_pDistortion, m_pRefraction, m_pZF;
    D3DXMATRIX m_matView, m_matProj;
    LPDIRECT3DDEVICE9 m_pd3dDevice;

public:
    CParallaxMapping2(LPDIRECT3DDEVICE9 pd3dDevice);
    ~CParallaxMapping2();
    void Invalidate();
    void Restore();
    HRESULT Load();
    void Begin();
    void BeginPass(UINT Pass);
    void SetAmbient(float Ambient);
    void SetAmbient(D3DXVECTOR4* pAmbient);
    void SetSpecular(float Specular);
    void SetSpecularPower(float SpecularPower);
    //高さに対する係数
    void SetHeight(float Height);
    //屈折率
    void SetRefraction(float Refraction);
    void SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pCameraPos, D3DXVECTOR4* pLightDir, float pZF);
    void EndPass();
    void End();
    void CommitChanges();
    BOOL IsOK();
    LPD3DXEFFECT GetEffect() { return m_pEffect; };
};

#endif