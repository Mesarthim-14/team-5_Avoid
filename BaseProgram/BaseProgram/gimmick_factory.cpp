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
    CRotateGimmick::Create(D3DXVECTOR3(-10676.8f, 2000.0f, -47242.9f));
 //   CRotateGimmick::Create(D3DXVECTOR3(-31838.1f, 800.0f, -17180.4f));
}

//=======================================================================================
// �⓹�̐���
//=======================================================================================
void CGimmickFactory::CreateSlope()
{
    CSlope::Create(D3DXVECTOR3(-12503.1f, 2700.0f, -74892.9f), D3DXVECTOR3(0.0f, D3DXToRadian(278.0f), 0.0f));
    CSlope::Create(D3DXVECTOR3(53587.5f, 2200.0f, -35282.7f), D3DXVECTOR3(0.0f, D3DXToRadian(243.0f), 0.0f));
    CSlope::Create(D3DXVECTOR3(2961.4f, 2700.0f, -62761.8f), D3DXVECTOR3(0.0f, D3DXToRadian(6.0f), 0.0f));
    CSlope::Create(D3DXVECTOR3(11661.5f, 2700.0f, 58025.7f), D3DXVECTOR3(0.0f, D3DXToRadian(118.0f), 0.0f));
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
    CBridge::Create(D3DXVECTOR3(13890.0f, 5512.5f, -49270.0f), D3DXVECTOR3(0.0f, D3DXToRadian(7.0f), 0.0f));
}

//=======================================================================================
// �Q
//=======================================================================================
void CGimmickFactory::CreateSwirl()
{
    CSwirlScaffold::Create(D3DXVECTOR3(50244.2f, 0.0f, -18862.9f));
    CSwirlScaffold::Create(D3DXVECTOR3(57719.1f, 0.0f, -23549.7f));
}