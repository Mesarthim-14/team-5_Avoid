//=============================================================================
//
// �e�N�X�`���A�j���[�V�����N���X [texture_animation.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture_animation.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTextureAnimation::CTextureAnimation()
{
    memset(m_tex, 0, sizeof(m_tex));
    m_nCountAnim = 0;
    m_nCountAnimPattern = 0;
    m_nPatternNum = 0;
    m_nAnimSpeed = 0;
    m_nLoop = -1;
    m_nSpeedTexture = 0;
    m_nScrollCounter = 0;
    m_fDivisionBaseNum = 0.0f;
    m_fDivisionCounter = 0.0f;
    m_bEnd = false;
    m_bUpdate = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTextureAnimation::~CTextureAnimation()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTextureAnimation * CTextureAnimation::Create(const D3DXVECTOR2 m_tex[NUM_VERTEX])
{
    // �I�u�W�F�N�g�𐶐�
    CTextureAnimation* pTextureAnimation = new CTextureAnimation;

    if (pTextureAnimation)
    {
        // �l�̐ݒ�
        memcpy(pTextureAnimation->m_tex, m_tex, NUM_VERTEX);
        return pTextureAnimation;
    }

    return nullptr;
}

//=============================================================================
// �X�V����
//=============================================================================
void CTextureAnimation::Update()
{
    // �e�N�X�`���̃A�j���[�V����
    if (m_nAnimSpeed != 0)
    {
        // �A�j���[�V�������X�V����
        UpdateAnimation();
    }

    // �e�N�X�`���̃X�N���[��
    if (m_nSpeedTexture != 0)
    {
        // �A�j���[�V�������X�V����
        UpdateScroll();
    }
}

//=============================================================================
// �A�j���[�V�������̐ݒ�
//=============================================================================
void CTextureAnimation::InitAnimationInfo(const int &nPatternNum, const int &nSpeed, const int &nLoop)
{
    m_nPatternNum = nPatternNum;
    m_nAnimSpeed = nSpeed;
    m_nLoop = nLoop;
}

//=============================================================================
// �X�N���[�����̐ݒ�
//=============================================================================
void CTextureAnimation::InitScroll(const int &nSpeed, const float &fDivision)
{
    m_nSpeedTexture = nSpeed;
    m_fDivisionBaseNum = fDivision;
}

//=============================================================================
// �A�j���[�V�����̍X�V
//=============================================================================
void CTextureAnimation::UpdateAnimation()
{
    // �����̃A�j���[�V�����J�E���g��i�߂āA�p�^�[����؂�ւ���
    m_nCountAnim++;

    // ���_���(�e�N�X�`�����W)�̍X�V
    if (m_nCountAnim >= m_nAnimSpeed)    // �����̑���
    {
        m_nCountAnim = 0;            // �A�j���[�V�����̃J�E���g��0�ɂ���
        m_nCountAnimPattern++;        // �A�j���[�V�����̃p�^�[�����J�E���g������
    }

    // �A�j���[�V�������I�������
    if (m_nCountAnimPattern >= m_nPatternNum)
    {
        // ���l��߂��Ă���
        m_nCountAnimPattern = 0;

        if (m_nLoop == 0)
        {
            m_bEnd = true;
        }
    }
    else
    {
        // �e�N�X�`�����W�̍X�V
        m_tex[0] = D3DXVECTOR2((float)(1.0f / m_nPatternNum)*(float)m_nCountAnimPattern, 0.0f);
        m_tex[1] = D3DXVECTOR2((float)(1.0f / m_nPatternNum)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternNum), 0.0f);
        m_tex[2] = D3DXVECTOR2((float)(1.0f / m_nPatternNum)*(float)m_nCountAnimPattern, 1.0f);
        m_tex[3] = D3DXVECTOR2((float)(1.0f / m_nPatternNum)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternNum), 1.0f);

        m_bUpdate = true;
    }
}

//=============================================================================
// �X�N���[���̍X�V
//=============================================================================
void CTextureAnimation::UpdateScroll()
{
    // �J�E���^�[��i�߂�
    m_nScrollCounter++;

    // ���_���(�e�N�X�`�����W)�̍X�V
    if (m_nScrollCounter >= m_nSpeedTexture)        // �����̑���
    {
        //�e�N�X�`�����W���X�V
        m_tex[0] = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
        m_tex[1] = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
        m_tex[2] = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
        m_tex[3] = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

        // �A�j���[�V�����̃p�^�[�����J�E���g������
        m_fDivisionCounter += m_fDivisionBaseNum;
        m_nScrollCounter = 0;

        m_bUpdate = true;
    }
}