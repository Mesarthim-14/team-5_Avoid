#ifndef _CReflect_H_
#define _CReflect_H_
//=============================================================================
//
// 反射クラス [reflect.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "main.h"

//=========================================================================
// クラス定義
//=========================================================================
class CReflect
{
public:
    CReflect(LPDIRECT3DDEVICE9 pd3dDevice);
    ~CReflect();
    HRESULT Load();
    void Invalidate();
    void Restore();
    void Begin();
    void BeginPass();
    void SetHeight(float Height);
    void SetAmbient(float Ambient);
    void SetAmbient(D3DXVECTOR4* pAmbient);
    void SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir);
    void EndPass();
    void End();
    void CommitChanges();
    BOOL IsOK();
    LPD3DXEFFECT GetEffect() { return m_pEffect; };

private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pW, m_pWVPP, m_pLightDir, m_pAmbient, m_pHeight;
    D3DXMATRIX m_matView, m_matProj;
    LPDIRECT3DDEVICE9 m_pd3dDevice;
};

#endif