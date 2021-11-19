//=====================================================================
//
//    �C���ԊǗ��N���X [state_player_stun.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player_stun.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "state_player_normal.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define MAX_STAN_COUNT (120)    // ���A�܂ł̃J�E���g

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateStun::CPlayerStateStun()
{
    m_nStunCount = 0;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPlayerStateStun::~CPlayerStateStun()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CPlayerStateStun * CPlayerStateStun::Create()
{
    // �������m��
    CPlayerStateStun *pStateJump = new CPlayerStateStun;
    if (pStateJump)
    {
        // ����������
        pStateJump->Init();
        return pStateJump;
    }
    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CPlayerStateStun::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
}

//=====================================================================
// �X�V����
//=====================================================================
void CPlayerStateStun::Update()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    m_nStunCount++;
    // ����
    D3DXVECTOR3 move = pPlayer->GetMove();
    if (abs(move.x) > 0.0f)//���点��
    {
        if (move.x > 0.0f)
        {
            move.x -= 2.0f;
        }
        if (move.x < 0.0f)
        {
            move.x += 2.0f;
        }
    }
    if (abs(move.z) > 0.0f)
    {
        if (move.z > 0.0f)
        {
            move.z -= 2.0f;
        }
        if (move.z < 0.0f)
        {
            move.z += 2.0f;
        }
    }

    // �ړ��ʐݒ�
    move += (pPlayer->GetInertia() - move) * pPlayer->GetInertiaNum();
    pPlayer->SetMove(move);

    // ��莞�ԂŃX�^������
    if (m_nStunCount >= MAX_STAN_COUNT)
    {
        m_nStunCount = 0;
        pPlayer->ChangeState(CPlayerStateNormal::Create());// �X�^����ԉ����i�N���オ��j
    }

}