//=======================================================================================
//
// ��C���̉��o [production_cannon.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "production_cannon.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "gimmick_factory.h"
#include "player.h"
#include "camera_game.h"
#include "state_player_cannon.h"
#include "state_player_normal.h"
#include "state_camera_cannon.h"
#include "state_camera_normal.h"
#include "cannon_bullet.h"
#include "cannon.h"
#include "cannon_manager.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define SHOT_BULLET_TIME    (60)    // �e��ł���
#define END_TIME            (240)    // �I������

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CProductionCannon::CProductionCannon()
{
    m_pPlayerState = nullptr;
    m_pCameraState = nullptr;
    m_nCounter = 0;
    m_bEnd = false;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CProductionCannon::~CProductionCannon()
{
}

//=======================================================================================
// �C���X�^���X����
//=======================================================================================
CProductionCannon * CProductionCannon::Create()
{
    // �������m��
    CProductionCannon *pProductionCannon = new CProductionCannon;
    if (pProductionCannon)
    {
        // �C���X�^���X����
        pProductionCannon->Init();
        return pProductionCannon;
    }

    return nullptr;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CProductionCannon::Init()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();

    if (!m_pPlayerState)
    {
        // �v���C���[�̏�Ԑ���
        m_pPlayerState = CPlayerStateCannon::Create();
        pPlayer->ChangeState(m_pPlayerState);
    }
    if (!m_pCameraState)
    {
        // �J�����̏�Ԑ���
        m_pCameraState = CCameraStateCannon::Create();
        pCamera->ChangeState(m_pCameraState);
    }

    return S_OK;
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CProductionCannon::Update()
{
    m_nCounter++;

    // �e�̔���
    if (m_nCounter == SHOT_BULLET_TIME)
    {
        CCannon* pCannon = CManager::GetInstance()->GetGame()->GetGimmickFactory()->GetCannonManager()->GetCurrentCannon();
        CCannonBullet::Create(pCannon->GetPos(), pCannon->GetRot());
    }

    // �I���t���O
    if (m_nCounter >= END_TIME)
    {
        m_pPlayerState = nullptr;
        m_pCameraState = nullptr;
        CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
        CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
        pPlayer->ChangeState(CPlayerStateNormal::Create());
        pCamera->ChangeState(CCameraStateNormal::Create());
        m_bEnd = true;
    }
}