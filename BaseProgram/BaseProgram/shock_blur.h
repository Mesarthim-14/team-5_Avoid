#ifndef _SHOCK_BLUR_H_
#define _SHOCK_BLUR_H_
//=============================================================================
//
// �����p�u���[�N���X [shock_filter.h]
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
class CShockBlur : public CShaderSquare
{
public:
    CShockBlur(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height);  // �R���X�g���N�^
    ~CShockBlur();                                                      // �f�X�g���N�^

    void Uninit();                                  // �I������
    void Invalidate();                              // �f�o�C�X�̍폜
    void Restore();                                 // ���X�g��
    HRESULT Load();                                 // ���[�h
    void TextureLoad();                             // �e�N�X�`�����[�h
    void SetCenterTexel(float TU, float TV);        // �e�N�Z���̒��S���W�𑗂�
    void SetBlurPower(const float &fBlurPoswer);    // �u���[�̋���
    void BlurRender();                              // �`�揈��
    void Begin();                                   // �J�n
    void Draw();                                    // �`�揈��
    void EndSurface();                              // �T�[�t�F�X�I��

    inline LPD3DXEFFECT GetEffect()const { return m_pEffect; };

private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pCenterTexel, m_pTU, m_pTV, m_pBlurPower;
    LPDIRECT3DDEVICE9 m_pd3dDevice;
    //�����_�[�^�[�Q�b�g�T�[�t�F�C�X
    LPDIRECT3DTEXTURE9 m_pFullScreenTexture;
    LPDIRECT3DSURFACE9 m_pFullScreenSurface;
    D3DVIEWPORT9 m_OldViewport;
    LPDIRECT3DSURFACE9 m_OldSurface;
};

#endif