//=====================================================================
//
// �N���[�P�����S��ԃN���X [state_kraken_dead.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_kraken_dead.h"
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
CKrakenStateDead::CKrakenStateDead()
{
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CKrakenStateDead::~CKrakenStateDead()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CKrakenStateDead * CKrakenStateDead::Create()
{
    // �������m��
    CKrakenStateDead *pState = new CKrakenStateDead;
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
void CKrakenStateDead::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CKraken::MOTION_MAX - 1) - CKraken::MOTION_DEATH), 60);
}

//=====================================================================
// �X�V����
//=====================================================================
void CKrakenStateDead::Update()
{
    CKraken* pKraken = GetKrakenPtr();
    if (pKraken)
    {
        D3DXVECTOR3 pos = pKraken->GetPos();
        pos.y -= 50.0f;
        pKraken->SetPos(pos);
    }
}