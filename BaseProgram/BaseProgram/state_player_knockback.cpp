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
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "state_player_normal.h"

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateKnockback::CPlayerStateKnockback()
{
    m_nStanCount = 0;
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
CPlayerStateKnockback * CPlayerStateKnockback::Create()
{
    // �������m��
    CPlayerStateKnockback *pStateJump = new CPlayerStateKnockback;
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

    D3DXVECTOR3 move = pPlayer->GetMove();
}