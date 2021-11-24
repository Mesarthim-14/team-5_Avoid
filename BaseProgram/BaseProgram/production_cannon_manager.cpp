//=======================================================================================
//
// ��C���̉��o [production_cannon_manager.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "production_cannon_manager.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "resource_manager.h"
#include "production_cannon.h"
#include "production_angry_kraken.h"
#include "kraken.h"
#include "game.h"
#include "production_dead_kraken.h"

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CProductionCannonManager::CProductionCannonManager()
{
    m_pProduction = nullptr;
    m_bEnd = false;
    m_nStep = 0;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CProductionCannonManager::~CProductionCannonManager()
{
}

//=======================================================================================
// �C���X�^���X����
//=======================================================================================
CProductionCannonManager* CProductionCannonManager::Create()
{
    // �������m��
    CProductionCannonManager* pProduction = new CProductionCannonManager;
    if (pProduction)
    {
        // �C���X�^���X����
        pProduction->Init();
        return pProduction;
    }

    return nullptr;
}

//=======================================================================================
// ����������
//=======================================================================================
void CProductionCannonManager::Init()
{
    (this->*m_CreateProduction.at(m_nStep))();
}

//=======================================================================================
// ����������
//=======================================================================================
void CProductionCannonManager::Uninit()
{
    if (m_pProduction)
    {
        m_pProduction->Uninit();
        m_pProduction = nullptr;
    }
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CProductionCannonManager::Update()
{
    if (m_pProduction)
    {
        // ���o�̍X�V����
        m_pProduction->Update();
        if (m_pProduction->GetEnd())
        {// ���o���I��������
            // �I������
            m_pProduction->Uninit();
            m_pProduction = nullptr;

            // ���o�̃X�e�b�v�����o���������Ă�����
            if (m_nStep >= (int)m_CreateProduction.size())
            {// �I��
                m_bEnd = true;
            }
            else
            {// ���̉��o��
                (this->*m_CreateProduction.at(m_nStep))();
            }
        }
    }
}

//=======================================================================================
// ��C��łƂ��̉��o����
//=======================================================================================
void CProductionCannonManager::CreateProductionCannonShot()
{
    if (!m_pProduction)
    {
        // ��C�̔��˃N���X
        m_pProduction = CProductionCannon::Create();
    }
    m_nStep++;
}

//=======================================================================================
// �{�����Ƃ��̉��o
//=======================================================================================
void CProductionCannonManager::CreateProductionAngry()
{
    if (!CManager::GetInstance()->GetGame()->GetKraken()->GetDead())
    {
        if (!m_pProduction)
        {
            // ��C�̔��˃N���X
            m_pProduction = CProductionAngryKraken::Create();
        }
    }
    else
    {
        // ��C�̔��˃N���X
        m_pProduction = CProductionDeadKraken::Create();
    }
    m_nStep++;
}