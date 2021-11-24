//=======================================================================================
//
// �N���[�P�������ʉ��o [production_dead_kraken.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "production_dead_kraken.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "gimmick_factory.h"
#include "player.h"
#include "camera_game.h"
#include "state_player_not_move.h"
#include "state_player_normal.h"
#include "state_camera_normal.h"
#include "state_camera_angry_kraken.h"

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CProductionDeadKraken::CProductionDeadKraken()
{
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CProductionDeadKraken::~CProductionDeadKraken()
{
}

//=======================================================================================
// �C���X�^���X����
//=======================================================================================
CProductionDeadKraken * CProductionDeadKraken::Create()
{
    // �������m��
    CProductionDeadKraken *pProductionCannon = new CProductionDeadKraken;
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
void CProductionDeadKraken::Init()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();

    CreateState(pPlayer, CPlayerStateNotMove::Create());
    CreateState(pCamera, CCameraStateAngryKraken::Create());
}

//=======================================================================================
// �I������
//=======================================================================================
void CProductionDeadKraken::Uninit()
{
    CProduction::Uninit();
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CProductionDeadKraken::Update()
{
    TimeCounter(200);

    if (GetEnd())
    {
        CManager::GetInstance()->GetGame()->GameEnd();
    }
}