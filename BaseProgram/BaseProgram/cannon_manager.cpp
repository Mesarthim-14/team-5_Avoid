//=============================================================================
//
// ��C�̊Ǘ��N���X [cannon_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "cannon_manager.h"
#include "cannon.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "key_e.h"
#include "keyboard.h"
#include "input.h"
#include "cannon_bullet.h"
#include "player.h"
#include "camera_game.h"
#include "production_cannon_manager.h"
#include "state_camera_cannon.h"
#include "state_player_cannon.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCannonManager::CCannonManager()
{
    m_apCannon.clear();
    m_nAttackNum = 0;
    m_pKeyE = nullptr;
    m_nTargetCannon = 0;
    m_pProduction = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCannonManager::~CCannonManager()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCannonManager * CCannonManager::Create()
{
    // �������m��
    CCannonManager *pCheckPoint = new CCannonManager;

    // !nullcheck
    if (pCheckPoint)
    {
        // ����������
        pCheckPoint->Init();
        return pCheckPoint;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCannonManager::Init()
{
    CreateCannon(); // ���̐���
    CreateUi();     // UI�̐���

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCannonManager::Uninit()
{
    if (m_apCannon.size() > 0)
    {
        for (auto &pCannon : m_apCannon)
        {
            // �I������
            pCannon->Uninit();
        }

        m_apCannon.clear();
    }
    if (m_pKeyE)
    {
        m_pKeyE->Uninit();
        m_pKeyE = nullptr;
    }
}

//=============================================================================
// �X�V����
//=============================================================================
void CCannonManager::Update()
{
    // ��C�̓����蔻��
    CannonCollision();

    if (m_pProduction)
    {
        // �X�V����
        m_pProduction->Update();

        // �I���\��Ȃ�폜
        if (m_pProduction->GetEnd())
        {
            delete m_pProduction;
            m_pProduction = nullptr;
        }
    }
}

//=============================================================================
// ���̐���
//=============================================================================
void CCannonManager::CreateCannon()
{
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(-1129.6f, -154.2f, -9119.3f), D3DXVECTOR3(0.0f, D3DXToRadian(-60.0f), 0.0f)));
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(-17666.1f, 993.9f, -18578.5f), D3DXVECTOR3(0.0f, D3DXToRadian(-0.0f), 0.0f)));
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(-32181.7f, 969.4f, -1487.3f), D3DXVECTOR3(0.0f, D3DXToRadian(100.0f), 0.0f)));
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(-15764.1f, 140.4f, 10833.7f), D3DXVECTOR3(0.0f, D3DXToRadian(190.0f), 0.0f)));
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(-5933.0f, 89.4f, 10833.7f), D3DXVECTOR3(0.0f, D3DXToRadian(220.0f), 0.0f)));
}

//=============================================================================
// Ui�̐���
//=============================================================================
void CCannonManager::CreateUi()
{
    // �C���X�^���X����
    if (!m_pKeyE)
    {
        m_pKeyE = CKeyE::Create();
    }
}

//=============================================================================
// ��C�̓����蔻��
//=============================================================================
void CCannonManager::CannonCollision()
{
    // ��C�̐�
    size_t size = m_apCannon.size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        // ��C�̓����蔻��
        if (m_apCannon.at(nCount)->Collision())
        {
            // �Ώۂ̔ԍ����擾
            m_nTargetCannon = nCount;

            // E�L�[�\��
            m_pKeyE->SetDrawFlag(true);

            // �{�^���̔���
            InputJudge();
            return;
        }
    }

    // E�L�[��\��
    m_pKeyE->SetDrawFlag(false);
}

//=============================================================================
// �{�^���̔���
//=============================================================================
void CCannonManager::InputJudge()
{
    // ���˃{�^���������ꂽ��
    if (CLibrary::KeyboardTrigger(DIK_E))
    {
        CreateBullet();
    }
}

//=============================================================================
// �e�̔���
//=============================================================================
void CCannonManager::CreateBullet()
{
    // ���o�ֈȍ~
    SetProductionMode();

    // �g�p��Ԃɂ���
    m_apCannon.at(m_nTargetCannon)->SetUseFlag();
}

//=============================================================================
// ���o�̐ݒ�
//=============================================================================
void CCannonManager::SetProductionMode()
{
    // ��C�̉��o
    if (!m_pProduction)
    {
        m_pProduction = CProductionCannonManager::Create();
    }
}
