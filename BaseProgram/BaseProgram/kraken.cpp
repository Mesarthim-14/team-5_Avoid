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
#include "collisionModel_OBB.h"
#include "state.h"
#include "state_kraken_normal.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POS             (D3DXVECTOR3(-16686.5f, 0.0f, -2596.4f))
#define SIZE            (D3DXVECTOR3(3200.0f, 7500.0f, 3200.0f))
#define BULLET_INTERVAL (500)                                      // ���ܔ��ˊԊu
#define MAX_LIFE        (5)                                        // ���C�t

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKraken::CKraken(PRIORITY Priority) : CEnemy(Priority)
{
    m_pSkinmeshModel = nullptr;
    m_nBulletCount = 0;
    m_pCollision = nullptr;
    m_nLife = MAX_LIFE;
    m_bDead = false;
    m_pCurrentState = nullptr;
    m_pNextState = nullptr;
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
    SetGravityFlag(false);
    CEnemy::Init();

    // ���f���̐���
    CreateModel();

    if (!m_pCollision)
    {
        // �C���X�^���X����
        m_pCollision = CCollisionModelOBB::Create(POS, SIZE, ZeroVector3);
    }

    if (!m_pCurrentState)
    {
        m_pCurrentState = CKrakenStateNormal::Create();
    }
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
    if (m_pCollision)
    {
        m_pCollision->Uninit();
        m_pCollision = nullptr;
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
    if (m_pCollision)
    {
        m_pCollision->SetInfo(GetPos(), m_pCollision->GetInfo().size, GetRot());
    }

    // �̗͂������Ȃ�����
    if (m_nLife <= 0)
    {
        m_bDead = true;
    }
}

//=============================================================================
// ��Ԃ̕ύX
//=============================================================================
void CKraken::ChangeState(CState* pState)
{
    m_pNextState = pState;
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CKraken::CreateModel()
{
    m_pSkinmeshModel = CSkinmeshModel::Create(GetPos(), GetRot(), CSkinmeshModel::MODEL_ENEMY_KRAKEN_HEAD);

    m_pSkinmeshModel->IsDraw(true);

    // ���f���̏�񕪂���Ȃ�
    m_pSkinmeshModel->GetHLcontroller()->ChangeAnimation(0);
    m_pSkinmeshModel->GetHLcontroller()->SetLoopTime(0, 60);
    m_pSkinmeshModel->GetHLcontroller()->SetShiftTime(0, 60);
}

//=============================================================================
// ��Ԃ̍X�V
//=============================================================================
void CKraken::UpdateState()
{
    if (m_pNextState)
    {
        delete m_pCurrentState;
        m_pCurrentState = nullptr;

        m_pCurrentState = m_pNextState;
        m_pNextState = nullptr;
    }

    if (m_pCurrentState)
    {
        // �X�V����
        m_pCurrentState->Update();
    }
}

//=============================================================================
// �U��
//=============================================================================
void CKraken::Attack()
{
    UpdateState();
}
