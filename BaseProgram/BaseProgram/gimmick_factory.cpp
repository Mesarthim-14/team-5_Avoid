//=======================================================================================
//
// �M�~�b�N�����N���X [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "gimmick_factory.h"
#include "manager.h"
#include "resource_manager.h"
#include "check_point.h"
#include "move_scaffold.h"
#include "rubble1.h"
#include "rubble2.h"
#include "rotate_gimmick.h"
#include "barrel.h"
#include "slope.h"
#include "barrel_factory.h"
#include "heel.h"
#include "cannon.h"
#include "bridge.h"
#include "cannon_manager.h"
#include "swirl_scaffold.h"

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGimmickFactory::CGimmickFactory()
{
    m_pCheckPoint = nullptr;
    m_pBarrelFactory = nullptr;
    m_pHeel = nullptr;
    m_pCannonManager = nullptr;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGimmickFactory::~CGimmickFactory()
{
}

//=======================================================================================
// �C���X�^���X����
//=======================================================================================
CGimmickFactory * CGimmickFactory::Create()
{
    CGimmickFactory *pGimmickFactory = new CGimmickFactory;
    if (pGimmickFactory)
    {
        pGimmickFactory->Init();
        return pGimmickFactory;
    }
    return nullptr;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGimmickFactory::Init()
{
    CreateCheckPoint();
    CreateGimmick();

    return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGimmickFactory::Uninit()
{
    // �`�F�b�N�|�C���g
    if (m_pCheckPoint)
    {
        m_pCheckPoint->Uninit();
        delete m_pCheckPoint;
        m_pCheckPoint = nullptr;
    }
    if (m_pBarrelFactory)
    {
        delete m_pBarrelFactory;
        m_pBarrelFactory = nullptr;

    }
    if (m_pHeel)
    {
        m_pHeel->Uninit();
        delete m_pHeel;
        m_pHeel = nullptr;
    }
    if (m_pCannonManager)
    {
        m_pCannonManager->Uninit();
        delete m_pCannonManager;
        m_pCannonManager = nullptr;
    }
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGimmickFactory::Update()
{
    // �`�F�b�N�|�C���g
    if (m_pCheckPoint)
    {
        m_pCheckPoint->Update();
    }
    if (m_pBarrelFactory)
    {
        m_pBarrelFactory->Update();
    }
    if (m_pHeel)
    {
        m_pHeel->Update();
    }
    if (m_pCannonManager)
    {
        m_pCannonManager->Update();
    }
}

//=======================================================================================
// ���\��
//=======================================================================================
void CGimmickFactory::CreateCheckPoint()
{
    if (!m_pCheckPoint)
    {
        m_pCheckPoint = CCheckPoint::Create();
    }
}

//=======================================================================================
// �}�b�v�̐���
//=======================================================================================
void CGimmickFactory::CreateGimmick()
{
    // ������
    CreateMoveScaffold();
    CreateRotateGimmick();
    CreateSlope();
    CreateCannon();
    CreateBridge();
    CreateSwirl();

    if (!m_pBarrelFactory)
    {
        m_pBarrelFactory = CBarrelFactory::Create();
    }
    if (!m_pHeel)
    {
        m_pHeel = CHeel::Create();
    }
}

//=======================================================================================
// �������M�~�b�N
//=======================================================================================
void CGimmickFactory::CreateMoveScaffold()
{
    CMoveScaffold::Create();
    CRubble1::Create();
    CRubble2::Create();
}

//=======================================================================================
// ��]�M�~�b�N
//=======================================================================================
void CGimmickFactory::CreateRotateGimmick()
{
    CRotateGimmick::Create(D3DXVECTOR3(-12126.1f, 810.0f, -16003.8f));
    CRotateGimmick::Create(D3DXVECTOR3(-31838.1f, 800.0f, -17180.4f));

}

//=======================================================================================
// �⓹�̐���
//=======================================================================================
void CGimmickFactory::CreateSlope()
{
    CSlope::Create(D3DXVECTOR3(-6562.7f, -200.0f, -13120.3f), D3DXVECTOR3(0.0f, D3DXToRadian(-75.0f), 0.0f));
    CSlope::Create(D3DXVECTOR3(-9662.7f, -200.0f, -23596.1f), D3DXVECTOR3(0.0f, D3DXToRadian(-15.0f), 0.0f));
}

//=======================================================================================
// ��C�̐���
//=======================================================================================
void CGimmickFactory::CreateCannon()
{
    if (!m_pCannonManager)
    {
        m_pCannonManager = CCannonManager::Create();
    }
}

//=======================================================================================
// ���̐���
//=======================================================================================
void CGimmickFactory::CreateBridge()
{
    CBridge::Create(D3DXVECTOR3(-25423.0f, 1000.0f, -18907.5f), D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f));
}

//=======================================================================================
// �Q
//=======================================================================================
void CGimmickFactory::CreateSwirl()
{
    CSwirlScaffold::Create(D3DXVECTOR3(-5788.6f, 0.0f, -22500.4f));
}