#ifndef _MASK_H_
#define _MASK_H_
//=============================================================================
//
// �}�X�N�N���X [mask.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CMask
{
private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pWVP;
    D3DXMATRIX m_matView, m_matProj;
    LPDIRECT3DDEVICE9 m_pd3dDevice;

public:
    CMask(LPDIRECT3DDEVICE9 pd3dDevice);
    ~CMask();
    void Invalidate();
    void Restore();
    HRESULT Load();
    void Begin();
    void BeginPass(UINT Pass);
    void SetMatrix(D3DXMATRIX* pMatWorld);
    void CommitChanges();
    void EndPass();
    void End();
    BOOL IsOK();
    LPD3DXEFFECT GetEffect() { return m_pEffect; };
};

#endif