//=============================================================================
//
// �G�l�~�[�̉�b(�G�l�~�[) [npc_text_enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "npc_text_enemy.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "npc_sentence_enemy1.h"
#include "npc_sentence_enemy2.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNpcTextEnemy::CNpcTextEnemy()
{
    m_nCounter = 0;
    m_bEnd = false;
    m_pSentence = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNpcTextEnemy::~CNpcTextEnemy()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CNpcTextEnemy * CNpcTextEnemy::Create()
{
    CNpcTextEnemy* pNpc = new CNpcTextEnemy;
    if (pNpc)
    {
        // ����������
        pNpc->Init();
        return pNpc;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNpcTextEnemy::Init()
{
    (this->*m_CreateSentence.at(m_nCounter))();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNpcTextEnemy::Uninit()
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CNpcTextEnemy::Update()
{
    if (CLibrary::KeyboardTrigger(DIK_E))
    {
        // ���o�̃X�e�b�v�����o���������Ă�����
        if (m_nCounter >= (int)m_CreateSentence.size())
        {
            // �I��
            if (m_pSentence)
            {
                m_pSentence->Uninit();
                m_pSentence = nullptr;
            }

            m_bEnd = true;
        }
        else
        {// ���̉��o��
            (this->*m_CreateSentence.at(m_nCounter))();
        }
    }
}

//=============================================================================
// ���͂̐���
//=============================================================================
void CNpcTextEnemy::CreateSentence1()
{
    if (!m_pSentence)
    {
        m_pSentence = CNpcSentenceEnemy1::Create();
    }
    m_nCounter++;
}

//=============================================================================
// ���͂̐���
//=============================================================================
void CNpcTextEnemy::CreateSentence2()
{
    if (m_pSentence)
    {
        m_pSentence->Uninit();
        m_pSentence = nullptr;
    }

    m_pSentence = CNpcSentenceEnemy2::Create();
    m_nCounter++;
}