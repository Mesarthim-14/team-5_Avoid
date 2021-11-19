//=============================================================================
//
// �N���[�P���N���X [kraken.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "kraken.h"
#include "animation_skinmesh.h"
#include "skinmesh_model.h"
#include "boss_bullet.h"

#define POS             (D3DXVECTOR3(-16686.5f, 0.0f, -2596.4f))
#define BULLET_INTERVAL (120)                                    // ���ܔ��ˊԊu

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKraken::CKraken(PRIORITY Priority) : CEnemy(Priority)
{
    m_pSkinmeshModel = nullptr;
    m_nBulletCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKraken::~CKraken()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CKraken * CKraken::Create()
{
    CKraken *pKraken = new CKraken;
    if (pKraken)
    {
        pKraken->Init();
        return pKraken;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CKraken::Init()
{
    // ���f�����ݒ�
    SetCharacterInfo(POS, ZeroVector3);

    CEnemy::Init();

    // ���f���̐���
    CreateModel();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CKraken::Uninit()
{
    if (m_pSkinmeshModel)
    {
        m_pSkinmeshModel->Uninit();
        m_pSkinmeshModel = nullptr;
    }

    CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CKraken::Update()
{
    CEnemy::Update();
    Attack();
}

//=============================================================================
// �U������
//=============================================================================
void CKraken::Attack()
{
    ShotBullet();
}

//=============================================================================
// �e����
// Author : hayashikawa sarina
//=============================================================================
void CKraken::ShotBullet()
{
    m_nBulletCount++;
    if (m_nBulletCount == BULLET_INTERVAL)
    {
        CBossBullet::Create(POS, ZeroVector3, D3DXVECTOR3(50.0f, 0.0f, 0.0f));
        m_nBulletCount = 0;
    }
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CKraken::CreateModel()
{
    m_pSkinmeshModel = CSkinmeshModel::Create(GetPos(), GetRot(), CSkinmeshModel::MODEL_ENEMY_KRAKEN_HEAD);

    m_pSkinmeshModel->IsDraw(true);
    //SetAction(m_pSkinmeshModel->MaxAction());

    // ���f���̏��c������Ȃ�
    m_pSkinmeshModel->GetHLcontroller()->ChangeAnimation(0);
    m_pSkinmeshModel->GetHLcontroller()->SetLoopTime(0, 60);
    m_pSkinmeshModel->GetHLcontroller()->SetShiftTime(0, 60);

}