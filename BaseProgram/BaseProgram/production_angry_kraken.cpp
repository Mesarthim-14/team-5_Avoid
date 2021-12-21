//=======================================================================================
//
// �N���[�P�����{�鉉�o [production_angry_kraken.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "production_angry_kraken.h"
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
#include "kraken.h"
#include "state_kraken_normal.h"
#include "state_kraken_angry.h"

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CProductionAngryKraken::CProductionAngryKraken()
{
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CProductionAngryKraken::~CProductionAngryKraken()
{
}

//=======================================================================================
// �C���X�^���X����
//=======================================================================================
CProductionAngryKraken * CProductionAngryKraken::Create()
{
    // �������m��
    CProductionAngryKraken *pProductionCannon = new CProductionAngryKraken;
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
void CProductionAngryKraken::Init()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
    CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();

    CreateState(pPlayer, CPlayerStateNotMove::Create());
    CreateState(pCamera, CCameraStateAngryKraken::Create());
    CreateState(pKraken, CKrakenStateAngry::Create());
    CLibrary::SetSound(CSound::SOUND_SE_SCREAM);
    CManager::GetInstance()->GetRenderer()->SetShockBlur(true);
}

//=======================================================================================
// �I������
//=======================================================================================
void CProductionAngryKraken::Uninit()
{
    CProduction::Uninit();
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CProductionAngryKraken::Update()
{
    TimeCounter(100);

    if (GetEnd())
    {
        CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
        CreateState(pPlayer, CPlayerStateNormal::Create());

        CCameraGame *pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
        CreateState(pCamera, CCameraStateNormal::Create());

        CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
        CreateState(pKraken, CKrakenStateNormal::Create());

            CManager::GetInstance()->GetRenderer()->SetShockBlur(false);

    }
}