//=====================================================================
//
//    �ʏ��ԊǗ��N���X [state_player_normal.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player_normal.h"
#include "player.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "mouse.h"
#include "state_player_avoid.h"
#include "state_player_jump.h"

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateNormal::CPlayerStateNormal()
{

}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPlayerStateNormal::~CPlayerStateNormal()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CPlayerStateNormal * CPlayerStateNormal::Create()
{
    // �������m��
    CPlayerStateNormal *pStateNormal = new CPlayerStateNormal;
    if (pStateNormal)
    {
        // ����������
        pStateNormal->Init();
        return pStateNormal;
    }
    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CPlayerStateNormal::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
}

//=====================================================================
// �X�V����
//=====================================================================
void CPlayerStateNormal::Update()
{
    // �������m��
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    // �L�[�{�[�h�ړ�����
    MoveByKeyboard(pPlayer);
    Jump(pPlayer);
    Avoidance(pPlayer);
}

//=====================================================================
// �W�����v����
//=====================================================================
void CPlayerStateNormal::Jump(CPlayer* &pPlayer)
{
    // ���߃W�����v
    if (CLibrary::KeyboardTrigger(DIK_SPACE))
    {
        // ��Ԃ̐ݒ�
        pPlayer->ChangeState(CPlayerStateJump::Create());
    }
}

//=====================================================================
// �������
//=====================================================================
void CPlayerStateNormal::Avoidance(CPlayer* &pPlayer)
{
    CMouse *pMouse = CManager::GetInstance()->GetMouse();   // �}�E�X
    if (pPlayer->GetLanding() == true && pMouse->GetButtonTrigger(CMouse::MOUSE_LEFT))//���
    {
        if (pPlayer->GetSlimeState() != CPlayer::SLIME_LITTLESIZE)
        {
            pPlayer->ChangeState(CPlayerStateAvoid::Create());
        }
    }
}