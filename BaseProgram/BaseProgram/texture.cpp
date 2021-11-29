//=============================================================================
//
// �e�N�X�`���̊Ǘ��N���X [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
    memset(m_apTexture, 0, sizeof(m_apTexture));
    memset(m_pVolumeTexture, 0, sizeof(m_pVolumeTexture));
    memset(m_pCubeTexture, 0, sizeof(m_pCubeTexture));
    memset(m_aTexFileName, 0, sizeof(m_aTexFileName));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
    for (int nCount = 0; nCount < TEXTURE_TYPE_NUM_MAX; nCount++)
    {
        // ���O�f�[�^�̃N���A
        m_aTexFileName[nCount].clear();
    }
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTexture * CTexture::Create()
{
    // �������m��
    CTexture *pTexture = new CTexture;

    // nullcheck
    if (pTexture)
    {
        // �����l
        pTexture->SetTextureName();
        return pTexture;
    }

    return nullptr;
}

//=============================================================================
// �e�N�X�`���̖��O��ݒ�
//=============================================================================
HRESULT CTexture::SetTextureName(void)
{
    // �ʏ�e�N�X�`��
    m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL] =
    {
        { "data/Texture/test.jpg" },                // �e�X�g
        { "data/Texture/star.png" },
        { "data/Texture/Gauge.png" },
        { "data/Texture/Gauge_Frame.png" },
        { "data/Texture/E-key.png"},
        { "data/Texture/message_back.jpeg" },
    };

    // �����e�N�X�`��
    m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE] =
    {
        { "data/Texture/test_animation.png" },        // �e�X�g�A�j���[�V����
    };

    // �{�����[���e�N�X�`��
    m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME] =
    {
//        { "data/Texture/NoiseVolume.dds" }
    };

    // �L���[�u�e�N�X�`��
    m_aTexFileName[TEXTURE_TYPE_NUM_CUBE] =
    {
//        { "data/Texture/suimen8.dds" }
    };

    return S_OK;
}

//=============================================================================
// �S�Ẵe�N�X�`�����[�h
//=============================================================================
void CTexture::LoadAll()
{
    // �ʏ�e�N�X�`��
    NormalTexLoad();

    // �����e�N�X�`��
    SeparateTexLoad();

    // �{�����[���e�N�X�`��
//    VolumeTexLoad();

    // �L���[�u�e�N�X�`��
//    CubeTexLoad();
}

//=============================================================================
// �S�Ẵe�N�X�`���A�����[�h
//=============================================================================
void CTexture::UnLoadAll()
{
    // �ʏ�e�N�X�`��
    NormalTexUnLoad();

    // �����e�N�X�`��
    SeparateTexUnLoad();

    // �{�����[���e�N�X�`��
//    VolumeTexUnLoad();

    // �L���[�u�e�N�X�`��
//    CubeTexUnLoad();
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::NormalTexLoad()
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL].size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL][nCount].data(), &m_apTexture[nCount]);
    }

    return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CTexture::NormalTexUnLoad()
{
    for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
    {
        if (m_apTexture[nCount])
        {
            m_apTexture[nCount]->Release();
            m_apTexture[nCount] = nullptr;
        }
    }
}

//=============================================================================
// �����e�N�X�`���̃��[�h
//=============================================================================
HRESULT CTexture::SeparateTexLoad()
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // �����e�N�X�`���̓ǂݍ���
    size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE].size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE][nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
    }
    return S_OK;
}

//=============================================================================
// �����e�N�X�`���̃A�����[�h
//=============================================================================
void CTexture::SeparateTexUnLoad()
{
    // �e�N�X�`���̉��
    for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
    {
        if (m_apSeparateTexture[nCount].pSeparateTexture)
        {
            m_apSeparateTexture[nCount].pSeparateTexture->Release();
            m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
        }
    }
}

//=============================================================================
// �e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(const TEXTURE_TYPE &Tex_Num)
{
    if (Tex_Num < TEXTURE_NUM_MAX)
    {
        if (m_apTexture[Tex_Num])
        {
            return m_apTexture[Tex_Num];
        }
    }

    return nullptr;
}

//=============================================================================
// �����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(const SEPARATE_TEX_TYPE &SepaTex_Type)
{
    // �z���菬����������
    if (SepaTex_Type < SEPARATE_TEX_MAX)
    {
        // NULLcheck
        if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture)
        {
            // �e�N�X�`�����
            return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
        }
    }

    return nullptr;
}

//=============================================================================
// �����e�N�X�`���̏��
//=============================================================================
INT_VERTEX_2D CTexture::GetSparateTexInfo(const SEPARATE_TEX_TYPE &SepaTex_Type)
{
    // �z���菬����������
    if (SepaTex_Type < SEPARATE_TEX_MAX)
    {
        // �e�N�X�`�����
        return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
    }

    return { 0, 0 };
}

//=============================================================================
// �����e�N�X�`���̃��[�v�t���O
//=============================================================================
bool CTexture::GetSparateTexLoop(const SEPARATE_TEX_TYPE &SepaTex_Type)
{
    // �z���菬����������
    if (SepaTex_Type < SEPARATE_TEX_MAX)
    {
        // �e�N�X�`�����
        return m_apSeparateTexture[SepaTex_Type].bLoop;
    }

    return false;
}

//=============================================================================
// �{�����[���e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::VolumeTexLoad()
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    // �e�N�X�`���̓ǂݍ���
    size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME].size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        D3DXCreateVolumeTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME][nCount].data(), &m_pVolumeTexture[nCount]);
    }

    return S_OK;
}

//=============================================================================
// �{�����[���e�N�X�`���A�����[�h
//=============================================================================
void CTexture::VolumeTexUnLoad()
{
    for (int nCount = 0; nCount < VOLUME_TEX_MAX; nCount++)
    {
        if (m_pVolumeTexture[nCount])
        {
            m_pVolumeTexture[nCount]->Release();
            m_pVolumeTexture[nCount] = nullptr;
        }
    }
}

//=============================================================================
// �{�����[���e�N�X�`���̏��
//=============================================================================
LPDIRECT3DVOLUMETEXTURE9 CTexture::GetVolumeTexture(const VOLUME_TEX_TYPE &Tex_Type)
{
    if (Tex_Type < VOLUME_TEX_MAX)
    {
        if (m_pVolumeTexture[Tex_Type])
        {
            return m_pVolumeTexture[Tex_Type];
        }
    }

    return nullptr;
}

//=============================================================================
// �L���[�u�e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::CubeTexLoad()
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    // �e�N�X�`���̓ǂݍ���
    size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_CUBE].size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        D3DXCreateCubeTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_CUBE][nCount].data(), &m_pCubeTexture[nCount]);
    }

    return S_OK;
}

//=============================================================================
// �L���[�u�e�N�X�`���A�����[�h
//=============================================================================
void CTexture::CubeTexUnLoad()
{
    for (int nCount = 0; nCount < CUBE_TEX_MAX; nCount++)
    {
        if (m_pCubeTexture[nCount] != nullptr)
        {
            m_pCubeTexture[nCount]->Release();
            m_pCubeTexture[nCount] = nullptr;
        }
    }
}

//=============================================================================
// �L���[�u�e�N�X�`���̏��
//=============================================================================
LPDIRECT3DCUBETEXTURE9 CTexture::GetCubeTexture(const CUBE_TEX_TYPE &Tex_Type)
{
    if (Tex_Type < CUBE_TEX_MAX)
    {
        if (m_pVolumeTexture[Tex_Type] != nullptr)
        {
            return m_pCubeTexture[Tex_Type];
        }
    }

    return nullptr;
}