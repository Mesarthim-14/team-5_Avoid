//=======================================================================================
//
// ���o�N���X [production.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "production.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "resource_manager.h"

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CProduction::CProduction()
{
    m_nCounter = 0;
    m_bEnd = false;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CProduction::~CProduction()
{
}

//=======================================================================================
// ����������
//=======================================================================================
void CProduction::Init()
{
}

//=======================================================================================
// �I������
//=======================================================================================
void CProduction::Uninit()
{
    delete this;
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CProduction::Update()
{

}

//=======================================================================================
// ��Ԃ̐���
//=======================================================================================
void CProduction::CreateState(CStateObject* pObj, CState* pState)
{
    if (pObj && pState)
    {
        pObj->ChangeState(pState);
    }
}