//=============================================================================
//
// �����u���[�t�B���^�\ [shock_blur.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "shock_blur.h"
#include "manager.h"
#include "light.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShockBlur::CShockBlur(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height) : CShaderSquare(pd3dDevice, Width, Height)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
    memset(&m_OldViewport, 0, sizeof(D3DVIEWPORT9));
    m_OldSurface = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShockBlur::~CShockBlur()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }
}

//=============================================================================
// �I������
//=============================================================================
void CShockBlur::Uninit()
{
    if (m_pFullScreenTexture)
    {
        m_pFullScreenTexture->Release();
        m_pFullScreenTexture = nullptr;
    }
    if (m_pFullScreenSurface)
    {
        m_pFullScreenSurface->Release();
        m_pFullScreenSurface = nullptr;
    }

    CShaderSquare::Uninit();

    Invalidate();

    delete this;
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CShockBlur::Load()
{
    D3DCAPS9 caps;
    HRESULT hr;

    m_pd3dDevice->GetDeviceCaps(&caps);
    if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
    {
        hr = CShaderSquare::Load();
        if (FAILED(hr))
            return -1;

        //�V�F�[�_�[�̏�����
        LPD3DXBUFFER pErr = nullptr;
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/ShockBlur.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pCenterTexel = m_pEffect->GetParameterByName(nullptr, "m_CenterTexel");
        m_pTU = m_pEffect->GetParameterByName(nullptr, "m_TU");
        m_pTV = m_pEffect->GetParameterByName(nullptr, "m_TV");
        m_pBlurPower = m_pEffect->GetParameterByName(nullptr, "m_BlurPower");

        //�P�e�N�Z���̑傫�����Z�b�g
        float TU = 1.0f / CShaderSquare::GetWidth();
        float TV = 1.0f / CShaderSquare::GetHeight();

        m_pEffect->SetFloat(m_pTU, TU);
        m_pEffect->SetFloat(m_pTV, TV);

        m_pEffect->SetTechnique(m_pTechnique);
    }
    else
    {
        return -3;
    }

    TextureLoad();

    return S_OK;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
void CShockBlur::TextureLoad()
{
    //�X�N���[���̉𑜓x
    UINT nWidth = SCREEN_WIDTH;
    UINT nHeight = SCREEN_HEIGHT;
    UINT HalfWidth = nWidth / 4;
    UINT HalfHeight = nHeight / 4;

    Restore();
    SetCenterTexel(0.5f, 0.5f);
    D3DXCreateTexture(m_pd3dDevice,
        nWidth,
        nHeight,
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        &m_pFullScreenTexture);
    m_pFullScreenTexture->GetSurfaceLevel(0, &m_pFullScreenSurface);
}

//�����̒��S�ʒu��ݒ肷��
void CShockBlur::SetCenterTexel(float TU, float TV)
{
    if (m_pEffect)
    {
        D3DXVECTOR2 Texel = D3DXVECTOR2(TU, TV);

        m_pEffect->SetValue(m_pCenterTexel, &Texel, sizeof(D3DXVECTOR2));
    }
}

//�u���[���ݒ肷��
void CShockBlur::SetBlurPower(const float &fBlurPoswer)
{
    if (m_pEffect)
    {
        m_pEffect->SetFloat(m_pBlurPower, fBlurPoswer);
    }
}

//=============================================================================
// �V�F�[�_�̕`��
//=============================================================================
void CShockBlur::BlurRender()
{
    if (m_pEffect)
    {
        m_pEffect->Begin(nullptr, 0);
        m_pEffect->BeginPass(0);

        CShaderSquare::Draw();

        m_pEffect->EndPass();
        m_pEffect->End();
    }
}

//=============================================================================
// �V�F�[�_�J�n
//=============================================================================
void CShockBlur::Begin()
{
    D3DVIEWPORT9 NewViewport;
    //****************************************************************
    //STEP1:�I�u�W�F�N�g�̃����_�����O
    //****************************************************************
    //���݂̃r���[�|�[�g���擾����
    m_pd3dDevice->GetViewport(&m_OldViewport);
    CopyMemory(&NewViewport, &m_OldViewport, sizeof(D3DVIEWPORT9));
    NewViewport.Width = SCREEN_WIDTH;
    NewViewport.Height = SCREEN_HEIGHT;
    NewViewport.MinZ = 0.0f;
    NewViewport.MaxZ = 1.0f;
    m_pd3dDevice->SetViewport(&NewViewport);

    // �T�[�t�F�X�擾
    m_pd3dDevice->GetRenderTarget(0, &m_OldSurface);

    // �T�[�t�F�X�ݒ�
    m_pd3dDevice->SetRenderTarget(0, m_pFullScreenSurface);
    // �T�[�t�F�X�N���A
    m_pd3dDevice->Clear(0L,
        nullptr,
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        BlackColor,
        1.0f,
        0L);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CShockBlur::Draw()
{
    EndSurface();
    //****************************************************************
    //STEP2:�u���[����
    //****************************************************************
    //�{�P�̋�����ݒ肷��B0.0f �Ń{�P�Ȃ��B
    SetBlurPower(20.0f);

    //****************************************************************
    //STEP3:�u���[�C���[�W���o�b�N�o�b�t�@�Ƀ����_�����O
    //****************************************************************
    m_pd3dDevice->BeginScene();
    m_pd3dDevice->SetTexture(0, m_pFullScreenTexture);
    BlurRender();
}

//=============================================================================
// �T�[�t�F�X�̏I��
//=============================================================================
void CShockBlur::EndSurface()
{    
    // �T�[�t�F�X���o�b�N�o�b�t�@�ɖ߂�
    m_pd3dDevice->SetRenderTarget(0, m_OldSurface);
    if (m_OldSurface)
    {
        m_OldSurface->Release();
        m_OldSurface = nullptr;
    }
}

void CShockBlur::Invalidate()
{
    if (m_pEffect)
        m_pEffect->OnLostDevice();
}

void CShockBlur::Restore()
{
    if (m_pEffect)
        m_pEffect->OnResetDevice();
}