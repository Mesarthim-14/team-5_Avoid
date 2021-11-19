//=============================================================================
//
// �u���[�N���X [blur_filter.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "blur_filter.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBlurFilter::CBlurFilter(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters) : CShaderSquare(pd3dDevice, pd3dParameters)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBlurFilter::CBlurFilter(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height) : CShaderSquare(pd3dDevice, Width, Height)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBlurFilter::~CBlurFilter()
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
void CBlurFilter::Uninit()
{
    if (m_pEffect)
        m_pEffect->OnLostDevice();
}

//=============================================================================
// �f�o�C�X�ݒ�
//=============================================================================
void CBlurFilter::Restore()
{
    if (m_pEffect)
    {
        m_pEffect->OnResetDevice();
    }
}

//=============================================================================
// �V�F�[�_���[�h
//=============================================================================
HRESULT CBlurFilter::Load()
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
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/BlurFilter.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pTU = m_pEffect->GetParameterByName(nullptr, "m_TU");
        m_pTV = m_pEffect->GetParameterByName(nullptr, "m_TV");

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

    return S_OK;
}

//=============================================================================
// �e�N�Z���̐ݒ�
//=============================================================================
void CBlurFilter::SetTexel(float TU, float TV)
{
    if (m_pEffect)
    {
        m_pEffect->SetFloat(m_pTU, TU);
        m_pEffect->SetFloat(m_pTV, TV);
    }
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBlurFilter::Render(UINT Pass)
{
    if (m_pEffect)
    {
        m_pEffect->Begin(nullptr, 0);
        m_pEffect->BeginPass(Pass);

        CShaderSquare::Draw();   //2D�X�v���C�g�̃����_�����O

        m_pEffect->EndPass();
        m_pEffect->End();
    }
}

//=============================================================================
// nullcheck
//=============================================================================
BOOL CBlurFilter::IsOK()
{
    if (m_pEffect == nullptr)
        return FALSE;

    return TRUE;
}