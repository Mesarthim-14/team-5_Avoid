//=============================================================================
// barrl_factory�N���X [barrel_factory.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "barrel_factory.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "barrel.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CREATE_INTER    (120)   // �����̊Ԋu

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBarrelFactory::CBarrelFactory()
{
    m_nCreateCount = 0;
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBarrelFactory * CBarrelFactory::Create()
{
    // �������m��
    CBarrelFactory *pBarrelFactory = new CBarrelFactory;

    // !nullcheck
    if (pBarrelFactory)
    {
        // ����������
        return pBarrelFactory;
    }

    return nullptr;
}

//=============================================================================
// �X�V����
//=============================================================================
void CBarrelFactory::Update()
{
    // �M����
    CreateBarrel();
}

//=============================================================================
// �M�̐���
//=============================================================================
void CBarrelFactory::CreateBarrel()
{
    m_nCreateCount++;

    if (m_nCreateCount >= CREATE_INTER)
    {
        m_nCreateCount = 0;
    //    CBarrel::Create(D3DXVECTOR3(-10040.0f, 1014.8f, -15282.6f), D3DXVECTOR3(0.0f, D3DXToRadian(-25.0f), 0.0f));
    }
}
