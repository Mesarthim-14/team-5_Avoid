//=====================================================================
//
// �N���[�P���ʏ��ԊǗ��N���X [state_kraken_normal.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_kraken_normal.h"
#include "player.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "kraken.h"
#include "boss_bullet.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define BULLET_INTERVAL (500)   // ���ܔ��ˊԊu

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CKrakenStateNormal::CKrakenStateNormal()
{
    m_nBulletCount = 0;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CKrakenStateNormal::~CKrakenStateNormal()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CKrakenStateNormal * CKrakenStateNormal::Create()
{
    // �������m��
    CKrakenStateNormal *pStateNormal = new CKrakenStateNormal;
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
void CKrakenStateNormal::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
}

//=====================================================================
// �X�V����
//=====================================================================
void CKrakenStateNormal::Update()
{
    CKraken* pKraken = GetKrakenPtr();
    if (!pKraken)
    {
        return;
    }

    // �e����
    ShotBullet(pKraken);
}

//=====================================================================
// �e����
//=====================================================================
void CKrakenStateNormal::ShotBullet(CKraken* &pKraken)
{
    // �o���b�g�J�E���g
    m_nBulletCount++;
    if (m_nBulletCount == BULLET_INTERVAL)
    {
        CBossBullet::Create(pKraken->GetPos(), ZeroVector3);
        m_nBulletCount = 0;
    }
}
