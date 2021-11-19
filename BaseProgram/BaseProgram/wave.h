#ifndef _WAVE_H_
#define _WAVE_H_
//=============================================================================
//
// �g�N���X [wave.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "shader_square.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CWave : public CShaderSquare
{
public:
    CWave(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters); // �R���X�g���N�^
    CWave(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height);               // �R���X�g���N�^
    ~CWave();                                                                   // �f�X�g���N�^
    void Uninit();                                                              // �I������
    void Restore();                                                             // ���X�g�A
    HRESULT Load();                                                             // ���[�h
    void SetWaveSpeed(float SpringPower);                                       // �g�̑��x
    void AddWave(float Pos_X, float Pos_Y, float Height);                       // �g��^���鏈��
    LPDIRECT3DTEXTURE9 Draw();                                                  // �`�揈��
    HRESULT SetVertexDecl(LPDIRECT3DDEVICE9 pd3dDevice,                         // ���_�f�[�^�̍Đ���
        const D3DVERTEXELEMENT9 *pDecl, LPD3DXMESH &meshWater, 
        const LPD3DXMESH &mesh);
    LPD3DXEFFECT GetEffect() { return m_pEffect; };

private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pTexOffset, m_pSpringPower, m_pAddWavePos, m_pAddWaveHeight;
    //�g�}�b�v
    LPDIRECT3DTEXTURE9 m_pWaveMapTexture[2];
    LPDIRECT3DSURFACE9 m_pWaveMapSurface[2];
    //�@���}�b�v
    LPDIRECT3DTEXTURE9 m_pBumpMapTexture;
    LPDIRECT3DSURFACE9 m_pBumpMapSurface;
    LPDIRECT3DDEVICE9 m_pd3dDevice;
    //�g�}�b�v�̃C���f�b�N�X
    int m_RenderTargetIndex;
};

#endif