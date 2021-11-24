//=====================================================================
//
//    �C���ԊǗ��N���X [state_player_knockback.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player_knockback.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "state_player_normal.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define KNOCK_TIME  (150)   // �m�b�N�̎���

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateKnockback::CPlayerStateKnockback()
{
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPlayerStateKnockback::~CPlayerStateKnockback()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CPlayerStateKnockback * CPlayerStateKnockback::Create(const D3DXVECTOR3& move)
{
    // �������m��
    CPlayerStateKnockback *pState = new CPlayerStateKnockback;
    if (pState)
    {
        // ����������
        pState->SetMove(move);
        pState->Init();
        return pState;
    }
    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CPlayerStateKnockback::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
}

//=====================================================================
// �X�V����
//=====================================================================
void CPlayerStateKnockback::Update()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    if (pPlayer->GetLanding())
    {
        pPlayer->ChangeState(CPlayerStateNormal::Create());
    }
}

//=====================================================================
// �ړ��ʐݒ�
//=====================================================================
void CPlayerStateKnockback::SetMove(const D3DXVECTOR3 &move)
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    pPlayer->SetMove(move);
    pPlayer->SetLanding(false);

}