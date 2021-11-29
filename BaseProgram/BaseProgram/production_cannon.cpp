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
#include "kraken.h"
#include "state_kraken_not_attack.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define SHOT_BULLET_TIME    (60)    // �e��ł���
#define END_TIME            (240)   // �I������

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CProductionCannon::CProductionCannon()
{
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
void CProductionCannon::Init()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CreateState(pPlayer, CPlayerStateCannon::Create());

    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
    CreateState(pCamera, CCameraStateCannon::Create());

    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    CreateState(pKraken, CKrakenStateNotAttack::Create());
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CProductionCannon::Update()
{
    if (TimeCounter(END_TIME) == SHOT_BULLET_TIME)
    {
        CCannon* pCannon = CManager::GetInstance()->GetGame()->GetGimmickFactory()->GetCannonManager()->GetCurrentCannon();
        CCannonBullet::Create(pCannon->GetPos(), pCannon->GetRot());
    }
}