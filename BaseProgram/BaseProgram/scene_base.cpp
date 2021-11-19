//=============================================================================
//
// �V�[���x�[�X�N���X [scene_base.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene_base.h"
#include "texture_animation.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSceneBase::CSceneBase(PRIORITY Priority):CScene(Priority)
{
    m_pos = ZeroVector3;
    m_size = ZeroVector3;
    m_col = WhiteColor;
    m_rot = ZeroVector3;
    m_pVtxBuff = nullptr;
    m_pTexture = nullptr;
    m_pTextureAnimation = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneBase::~CSceneBase()
{
    // !nullcheck
    if (m_pVtxBuff)
    {
        //���_�o�b�t�@�̊J��
        m_pVtxBuff->Release();
        m_pVtxBuff = nullptr;
    }

    // �e�N�X�`���A�j���[�V�����̏I������
    if (m_pTextureAnimation)
    {
        delete m_pTextureAnimation;
        m_pTextureAnimation = nullptr;
    }
}

//=============================================================================
// �I������
//=============================================================================
void CSceneBase::Uninit()
{
    Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneBase::Update()
{
    // �e�N�X�`���A�j���[�V�����̍X�V����
    if (m_pTextureAnimation)
    {
        // �A�j���[�V�����X�V
        m_pTextureAnimation->Update();

        // �A�j���[�V�������W�ɍX�V����������
        if (m_pTextureAnimation->GetUpdate())
        {
            // �e�N�X�`�����W�̍X�V
            this->UpdateAnimation();
            m_pTextureAnimation->SetUpdateFlag(false);
        }
    }
}

//=============================================================================
// �V�[�����̐ݒ�
//=============================================================================
void CSceneBase::SetSceneInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
    m_pos = pos;
    m_size = size;
}
