//=====================================================================
//
//    �����ԊǗ��N���X [state_player_avoid.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player_avoid.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "mouse.h"
#include "state_player_normal.h"
#include "state_player_stun.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define AVOID_CONSUME (1)   // ����������̃��C�t������

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateAvoid::CPlayerStateAvoid()
{
    m_fAvoidValueY = 20.0f;
    m_fAvoidValueXZ = 25.0f;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPlayerStateAvoid::~CPlayerStateAvoid()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CPlayerStateAvoid * CPlayerStateAvoid::Create()
{
    // �������m��
    CPlayerStateAvoid *pStateAvoid = new CPlayerStateAvoid;
    if (pStateAvoid)
    {
        // ����������
        pStateAvoid->Init();
        return pStateAvoid;
    }

    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CPlayerStateAvoid::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_JUMP), 60);
    SetMove();
    Update();
}

//=====================================================================
// �X�V����
//=====================================================================
void CPlayerStateAvoid::Update()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    if (pPlayer->GetLanding())
    {
        pPlayer->ChangeState(CPlayerStateStun::Create());
    }
}

//=====================================================================
// �ړ��ʐݒ�
//=====================================================================
void CPlayerStateAvoid::SetMove()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    D3DXVECTOR3 move = pPlayer->GetMove();

    float fRot = pPlayer->GetRot().y;
    move.y += m_fAvoidValueY;
    move.x += sinf(fRot) * -m_fAvoidValueXZ;
    move.z += cosf(fRot) * -m_fAvoidValueXZ;
    pPlayer->SetMove(move);
    pPlayer->SetLanding(false);

    pPlayer->SubLife(AVOID_CONSUME);
}