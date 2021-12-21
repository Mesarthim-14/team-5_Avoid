//=====================================================================
//
// �N���[�P���{���ԃN���X [state_kraken_angry.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_kraken_angry.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "kraken.h"

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CKrakenStateAngry::CKrakenStateAngry()
{
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CKrakenStateAngry::~CKrakenStateAngry()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CKrakenStateAngry * CKrakenStateAngry::Create()
{
    // �������m��
    CKrakenStateAngry *pState = new CKrakenStateAngry;
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
void CKrakenStateAngry::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CKraken::MOTION_MAX - 1) - CKraken::MOTION_ANGRY), 60);
}

//=====================================================================
// �X�V����
//=====================================================================
void CKrakenStateAngry::Update()
{

}