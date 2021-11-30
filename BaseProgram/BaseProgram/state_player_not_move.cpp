//=====================================================================
//
// �v���C���[�����Ȃ���� [state_player_not_move.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player_not_move.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateNotMove::CPlayerStateNotMove()
{
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPlayerStateNotMove::~CPlayerStateNotMove()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CPlayerStateNotMove * CPlayerStateNotMove::Create()
{
    // �������m��
    CPlayerStateNotMove *pState = new CPlayerStateNotMove;
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
void CPlayerStateNotMove::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        pPlayer->SetMove(ZeroVector3);
        pPlayer->SetCollision(false);
    }
}

//=====================================================================
// �X�V����
//=====================================================================
void CPlayerStateNotMove::Update()
{

}