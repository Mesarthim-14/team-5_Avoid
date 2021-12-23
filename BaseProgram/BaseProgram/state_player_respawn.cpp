//=====================================================================
//
// ���X�|�[����� [state_player_respawn.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player_respawn.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "game.h"
#include "gimmick_factory.h"
#include "check_point.h"
#include "state_player_normal.h"
#include "move_scaffold.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define END_LIMIT   (60)   // �I���̎���

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateRespawn::CPlayerStateRespawn()
{
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPlayerStateRespawn::~CPlayerStateRespawn()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CPlayerStateRespawn * CPlayerStateRespawn::Create()
{
    // �������m��
    CPlayerStateRespawn *pState = new CPlayerStateRespawn;
    if (pState)
    {
        // ����������
        pState->Init();
        return pState;
    }

    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CPlayerStateRespawn::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CGame* pGame = (CGame*)CManager::GetInstance()->GetModePtr();
    if (!pPlayer || !pGame)
    {
        return;
    }
    D3DXVECTOR3 CheckPointPos = pGame->GetGimmickFactory()->GetCheckPoint()->GetPointPos();
    // ���W�̎擾
    pPlayer->SetPos(D3DXVECTOR3(CheckPointPos.x, CheckPointPos.y + (600 / 2), CheckPointPos.z));

    // ���W�̎擾
    pPlayer->SetPos(pGame->GetGimmickFactory()->GetCheckPoint()->GetPointPos());
    pPlayer->SetMove(ZeroVector3);
    pPlayer->SetCollision(false);

    // ��Ԃ̐ݒ�
    pPlayer->SetState(CPlayer::RESPAWN);

    CMoveScaffold* pScaffold = pGame->GetGimmickFactory()->GetMoveScaffold();
    if (pScaffold)
    {
        pScaffold->Respawn();
    }
}

//=====================================================================
// �X�V����
//=====================================================================
void CPlayerStateRespawn::Update()
{
    // �v���C���[���擾
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        // �I���t���O�𗧂Ă�
        if (CounterFunc(END_LIMIT, this))
        {
            pPlayer->ChangeState(CPlayerStateNormal::Create());
        }
    }
}