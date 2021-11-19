//=============================================================================
//
// �g�N���X [wave.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "wave.h"
#include "resource_manager.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWave::CWave(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters) : CShaderSquare(pd3dDevice, pd3dParameters)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
    for (int nCount = 0; nCount < 2; nCount++)
    {
        m_pWaveMapTexture[nCount] = nullptr;
        m_pWaveMapSurface[nCount] = nullptr;
    }
    m_pBumpMapTexture = nullptr;
    m_pBumpMapSurface = nullptr;
    m_RenderTargetIndex = 0;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWave::CWave(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height) : CShaderSquare(pd3dDevice, Width, Height)
{
    m_pd3dDevice = pd3dDevice;

    m_pEffect = nullptr;

    for (int nCount = 0; nCount < 2; nCount++)
    {
        m_pWaveMapTexture[nCount] = nullptr;
        m_pWaveMapSurface[nCount] = nullptr;
    }

    m_pBumpMapTexture = nullptr;
    m_pBumpMapSurface = nullptr;

    m_RenderTargetIndex = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWave::~CWave()
{
    // �G�t�F�N�g���
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }

    // �I������
    Uninit();
}

//=============================================================================
// �I������
//=============================================================================
void CWave::Uninit()
{
    if (m_pEffect)
    {
        m_pEffect->OnLostDevice();
    }

    //�g�}�b�v
    for (int nCount = 0; nCount < 2; nCount++)
    {
        if (m_pWaveMapTexture[nCount])
        {
            m_pWaveMapTexture[nCount]->Release();
            m_pWaveMapTexture[nCount] = nullptr;
        }
        if (m_pWaveMapSurface[nCount])
        {
            m_pWaveMapSurface[nCount]->Release();
            m_pWaveMapSurface[nCount] = nullptr;
        }
    }
    if (m_pBumpMapTexture)
    {
        m_pBumpMapTexture->Release();
        m_pBumpMapTexture = nullptr;
    }
    if (m_pBumpMapSurface)
    {
        m_pBumpMapSurface->Release();
        m_pBumpMapSurface = nullptr;
    }

    m_RenderTargetIndex = 0;
}

//=============================================================================
//�f�o�C�X�����X�g�A�����Ƃ��ɃR�[������֐�
//=============================================================================
void CWave::Restore()
{
    if (m_pEffect)
    {
        m_pEffect->OnResetDevice();

        for (int nCount = 0; nCount < 2; nCount++)
        {
            // �`��Ώۂ̔g�}�b�v�e�N�X�`���𐶐�
            D3DXCreateTexture(m_pd3dDevice,
                (DWORD)CShaderSquare::GetWidth(),    // �e�N�X�`���̑傫��
                (DWORD)CShaderSquare::GetHeight(),    // �e�N�X�`���̑傫��
                1,                                    // �~�j�}�b�v�̃��x��
                D3DUSAGE_RENDERTARGET,
                D3DFMT_G16R16F,
                D3DPOOL_DEFAULT,
                &m_pWaveMapTexture[nCount]);

            // �e�N�X�`������T�[�t�F�X�ւ̃|�C���^���擾
            m_pWaveMapTexture[nCount]->GetSurfaceLevel(0, &m_pWaveMapSurface[nCount]);
        }

        // �g�}�b�v�����ŏ�����
        // ���݂̃����_�[�^�[�Q�b�g���擾
        LPDIRECT3DSURFACE9 OldSurface = nullptr;
        m_pd3dDevice->GetRenderTarget(0, &OldSurface);

        // �o�b�N�o�b�t�@�̐[�x�o�b�t�@���擾
        LPDIRECT3DSURFACE9 OldDepthStencilSurface = nullptr;
        m_pd3dDevice->GetDepthStencilSurface(&OldDepthStencilSurface);

        //�f�v�X�o�b�t�@�͎g�p���Ȃ��̂Ŗ����ɂ���
        m_pd3dDevice->SetDepthStencilSurface(nullptr);

        for (int nCount = 0; nCount < 2; nCount++)
        {
            // �����_�[�^�[�Q�b�g���w��
            m_pd3dDevice->SetRenderTarget(0, m_pWaveMapSurface[nCount]);
            m_pd3dDevice->Clear(
                0,                            // �N���A�����`�̈�̐�
                NULL,                        // ��`�̈�
                D3DCLEAR_TARGET,
                BlackColor,                    // ��
                1.0f,                        // Z�o�b�t�@�̃N���A�l
                0                            // �X�e���V���o�b�t�@�̃N���A�l
            );
        }

        // �����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�
        m_pd3dDevice->SetRenderTarget(0, OldSurface);
        if (OldSurface)
        {
            // �T�[�t�F�X���̊J��
            OldSurface->Release();
        }

        // �o�b�N�o�b�t�@�̐[�x�o�b�t�@��߂�
        m_pd3dDevice->SetDepthStencilSurface(OldDepthStencilSurface);
        if (OldDepthStencilSurface)
        {
            // �[�x�o�b�t�@�̊J��
            OldDepthStencilSurface->Release();
        }

        // �o���v�}�b�v�p�̃^�[�Q�b�g�e�N�X�`������
        D3DXCreateTexture(m_pd3dDevice,
            (DWORD)CShaderSquare::GetWidth(),
            (DWORD)CShaderSquare::GetHeight(),
            1,
            D3DUSAGE_RENDERTARGET,
            D3DFMT_A8R8G8B8,
            D3DPOOL_DEFAULT,
            &m_pBumpMapTexture);
        // �T�[�t�F�X���擾
        m_pBumpMapTexture->GetSurfaceLevel(0, &m_pBumpMapSurface);
    }
}

//=============================================================================
// �V�F�[�_���[�h
//=============================================================================
HRESULT CWave::Load()
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
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/wave.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pTexOffset = m_pEffect->GetParameterByName(nullptr, "TexOffset");
        m_pSpringPower = m_pEffect->GetParameterByName(nullptr, "SpringPower");
        m_pAddWavePos = m_pEffect->GetParameterByName(nullptr, "AddWavePos");
        m_pAddWaveHeight = m_pEffect->GetParameterByName(nullptr, "AddWaveHeight");

        m_pEffect->SetTechnique(m_pTechnique);

        D3DXVECTOR2 Size;
        Size.x = 1.0f / CShaderSquare::GetWidth();
        Size.y = 1.0f / CShaderSquare::GetHeight();
        m_pEffect->SetFloatArray(m_pTexOffset, (float*)&Size, sizeof(D3DXVECTOR2));
    }
    else
    {
        return -3;
    }

    return S_OK;
}

//=============================================================================
// �g�̑��x�ݒ�
//=============================================================================
void CWave::SetWaveSpeed(float SpringPower)
{
    if (m_pEffect)
    {
        m_pEffect->SetFloat(m_pSpringPower, SpringPower);
    }
}

//=============================================================================
// �g�̒ǉ�
//=============================================================================
void CWave::AddWave(float Pos_X, float Pos_Y, float Height)
{
    if (m_pEffect)
    {
        //�g��ǉ�����ʒu��ݒ�
        D3DXVECTOR2 AddWavePos = D3DXVECTOR2(Pos_X, Pos_Y);
        m_pEffect->SetValue(m_pAddWavePos, &AddWavePos, sizeof(D3DXVECTOR2));

        //�ǉ�����g�̍�����ݒ肷��
        m_pEffect->SetFloat(m_pAddWaveHeight, Height);
    }
}

//=============================================================================
// �`�揈��
//=============================================================================
LPDIRECT3DTEXTURE9 CWave::Draw()
{
    if (m_pEffect)
    {
        // �r���[�|�[�g�ϐ�
        D3DVIEWPORT9 OldViewport, NewViewport;

        //�r���[�|�[�g��g�}�b�v�̃T�C�Y�ɍ��킹��
        m_pd3dDevice->GetViewport(&OldViewport);
        CopyMemory(&NewViewport, &OldViewport, sizeof(D3DVIEWPORT9));
        NewViewport.Width = (DWORD)CShaderSquare::GetWidth();
        NewViewport.Height = (DWORD)CShaderSquare::GetHeight();
        // �V�����r���[�|�[�g�ݒ�
        m_pd3dDevice->SetViewport(&NewViewport);
    
        //���݂̃����_�[�^�[�Q�b�g�T�[�t�F�C�X���擾
        LPDIRECT3DSURFACE9 OldSurface = nullptr;
        m_pd3dDevice->GetRenderTarget(0, &OldSurface);

        // ���݂̃T�[�t�F�X�擾
        LPDIRECT3DSURFACE9 OldDepthStencilSurface = nullptr;
        m_pd3dDevice->GetDepthStencilSurface(&OldDepthStencilSurface);
        //�f�v�X�o�b�t�@���g�p���Ȃ��̂Ŗ����ɂ���(���ӂQ)
        m_pd3dDevice->SetDepthStencilSurface(nullptr);

        // �����_�[�^�[�Q�b�g�̔ԍ��ݒ�
        m_RenderTargetIndex = 1 - m_RenderTargetIndex;
        // �����_�[�^�[�Q�b�g���Z�b�g����
        m_pd3dDevice->SetRenderTarget(0, m_pWaveMapSurface[1 - m_RenderTargetIndex]);
        // �g�}�b�v���e�N�X�`���[�X�e�[�W�O�ɃZ�b�g����
        m_pd3dDevice->SetTexture(0, m_pWaveMapTexture[m_RenderTargetIndex]);

        // �g�}�b�v�̍X�V
        m_pEffect->Begin(nullptr, 0);
        m_pEffect->BeginPass(0);
        CShaderSquare::Draw();   //2D�X�v���C�g�̃����_�����O
        m_pEffect->EndPass();    

        // �X�V�����g�}�b�v���Q�Ƃ����ʂ�ʉ��ɂ��ă����_�����O����
        m_pd3dDevice->SetRenderTarget(0, m_pBumpMapSurface);
        m_pd3dDevice->SetTexture(0, m_pWaveMapTexture[1 - m_RenderTargetIndex]);

        // 2D�e�N�X�`���̕`��
        m_pEffect->BeginPass(1);
        CShaderSquare::Draw();   //2D�X�v���C�g�̃����_�����O
        m_pEffect->EndPass();
        m_pEffect->End();

        // �����_�[�^�[�Q�b�g��߂�
        m_pd3dDevice->SetRenderTarget(0, OldSurface);
        if (OldSurface)
        {
            OldSurface->Release();
        }

        // �[�x�o�b�t�@��߂�
        m_pd3dDevice->SetDepthStencilSurface(OldDepthStencilSurface);
        if (OldDepthStencilSurface)
        {
            OldDepthStencilSurface->Release();
        }

        // �r���[�|�[�g��߂�
        m_pd3dDevice->SetViewport(&OldViewport);
    }

    return m_pBumpMapTexture;
}

//=============================================================================
// ���_�f�[�^�̍Đ���
//=============================================================================
HRESULT CWave::SetVertexDecl(LPDIRECT3DDEVICE9 pd3dDevice, const D3DVERTEXELEMENT9 *pDecl, LPD3DXMESH &meshWater, const LPD3DXMESH &mesh)
{
    LPD3DXMESH pTempSysMemMesh = nullptr;

    //���b�V�������R�s�[����
    if (mesh)
    {
        if (FAILED(mesh->CloneMesh(mesh->GetOptions(),
            pDecl,
            pd3dDevice, &pTempSysMemMesh)))
            return E_FAIL; 
    }

    //���_�����Q�Ƃ��A�@���x�N�g���A�ڐ��x�N�g���A�]�@���x�N�g�������邩���ׂ�
    DWORD Normal = D3DX_DEFAULT;
    DWORD Tangent = D3DX_DEFAULT;
    DWORD Binormal = D3DX_DEFAULT;
    if (pTempSysMemMesh)
    {
        for (UINT index = 0; index < D3DXGetDeclLength(pDecl); ++index)
        {
            if (pDecl[index].Usage == D3DDECLUSAGE_NORMAL)
                Normal = D3DDECLUSAGE_NORMAL;
            else if (pDecl[index].Usage == D3DDECLUSAGE_TANGENT)
                Tangent = D3DDECLUSAGE_TANGENT;
            else if (pDecl[index].Usage == D3DDECLUSAGE_BINORMAL)
                Binormal = D3DDECLUSAGE_BINORMAL;
        }
    }

    if (pTempSysMemMesh)
    {
        //���_���Ɋ�Â����_�f�[�^���Đ�������   
        if (Normal != D3DX_DEFAULT || Tangent != D3DX_DEFAULT || Binormal != D3DX_DEFAULT)
        {
            D3DXComputeTangentFrameEx(pTempSysMemMesh,
                D3DDECLUSAGE_TEXCOORD,
                0,
                D3DDECLUSAGE_TANGENT,
                0,
                D3DDECLUSAGE_BINORMAL,
                0,
                D3DDECLUSAGE_NORMAL,
                0,
                0,
                nullptr,
                0.01f,    //�{�P�.�l��������������Ƃڂ��Ȃ��Ȃ�
                0.25f,
                0.01f,
                &meshWater,
                nullptr
            );
        }

        //���_�f�[�^���Đ������Ȃ�
        else
        {
            pTempSysMemMesh->CloneMesh(pTempSysMemMesh->GetOptions(),
                pDecl,
                pd3dDevice,
                &meshWater);

        }
        pTempSysMemMesh->Release();
    }

    return S_OK;

}
