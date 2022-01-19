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
#include "shark.h"
#include "marlin.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define BULLET_INTERVAL (500)   // ���ܔ��ˊԊu
constexpr int MAX_ENEMY = 5;
constexpr float ANGLE = 5;
constexpr float ROT_ANGLE = ANGLE*2;

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
    SetAnimation(UINT((CKraken::MOTION_MAX - 1) - CKraken::MOTION_IDOL), 60);
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

    // �o���b�g�J�E���g
    m_nBulletCount++;
    if (m_nBulletCount == BULLET_INTERVAL)
    {
        int nNum = CLibrary::Random(0, 10);
        if (nNum < 7)
        {
            // �e����
            ShotBullet(pKraken);
        }
        else
        {
            ShotEnemy(pKraken);
        }
    }
}

//=====================================================================
// �e����
//=====================================================================
void CKrakenStateNormal::ShotBullet(CKraken* &pKraken)
{
        CBossBullet::Create(pKraken->GetPos(), ZeroVector3);
        m_nBulletCount = 0;
        CLibrary::SetSound(CSound::SOUND_SE_KRAKEN_BULLET_MITING);
}

//=====================================================================
// �G����
//=====================================================================
void CKrakenStateNormal::ShotEnemy(CKraken *& pKraken)
{
    for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
    {
        CShark::Create(pKraken->GetPos(),
            pKraken->GetRot() + D3DXVECTOR3(0.0f,
                D3DXToRadian(ROT_ANGLE) - D3DXToRadian(nCount*ANGLE),
                0.0f));
    }
    m_nBulletCount = 0;
}
