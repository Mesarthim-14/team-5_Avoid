#ifndef _FRESNEL_LAMBERT_H_
#define _FRESNEL_LAMBERT_H_
//=============================================================================
//
// フレネル反射光クラス [fresnel_lambert.h]
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
class CFrenelLambert
{
public:
    CFrenelLambert(LPDIRECT3DDEVICE9 pd3dDevice);
    ~CFrenelLambert();
    void Invalidate();
    void Restore();
    HRESULT Load();
    void Begin();
    void BeginPass(UINT Pass);
    void SetZEnable(bool ZEnable);
    void SetAmbient(float Ambient);
    void SetAmbient(D3DXVECTOR4* pAmbient);
    void SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir, float pZF);
    void CommitChanges();
    void EndPass();
    void End();
    BOOL IsOK();
    LPD3DXEFFECT GetEffect() { return m_pEffect; };

private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pWVPP, m_pLightDir, m_pAmbient, m_pZEnable, m_pZF;
    D3DXMATRIX m_matView, m_matProj;
    LPDIRECT3DDEVICE9 m_pd3dDevice;
};

#endif