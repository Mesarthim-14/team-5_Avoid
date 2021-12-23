//=============================================================================
//
// �J�W�L�N���X [marlin.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "marlin.h"
#include "marlin_model.h"
#include "pause.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ATTACK_INTER    (150)                                   // �U���Ԋu
#define ATTACK_STR      (20)                                    // �U����
#define ATTACK_POWER    (2.0f)                                  // ������΂���
#define SPEED           (350.0f)                                // �X�s�[�h
#define POS             (D3DXVECTOR3(-3500.0f, -200.0f, 0.0f))  // ���W
#define COLLISION_SIZE  (D3DXVECTOR3(m_fCollisionSize, m_fCollisionSize, m_fCollisionSize))

const float CMarlin::m_fCollisionSize = 500.0f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMarlin::CMarlin(PRIORITY Priority) : CWimpEnemy(Priority)
{
    m_pMarlinModel = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMarlin::~CMarlin()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMarlin * CMarlin::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    CMarlin *pMarlin = new CMarlin;
    if (pMarlin)
    {
        pMarlin->Init(pos, rot);
        return pMarlin;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMarlin::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    CWimpEnemy::Init(pos, COLLISION_SIZE, rot);
    SetAttackInfo(ATTACK_INTER, ATTACK_STR, ATTACK_POWER);
    SetCharacterInfo(pos, rot);
    SetSpeed(SPEED);

    CreateModel();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMarlin::Uninit()
{
    // ���f���X�V����
    if (m_pMarlinModel)
    {
        m_pMarlinModel->Uninit();
    }

    CWimpEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMarlin::Update()
{
    bool bPause = CManager::GetInstance()->GetActivePause();

    if (!bPause)
    {
        // ���f���X�V����
        if (m_pMarlinModel)
        {
            m_pMarlinModel->SetPos(GetPos());
            m_pMarlinModel->SetRot(GetRot());
        }
        CWimpEnemy::Update();
    }
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CMarlin::CreateModel()
{
    // ���f������
    if (!m_pMarlinModel)
    {
        m_pMarlinModel = CMarlinModel::Create(GetPos());
    }
}

//=============================================================================
// �U���֐�
//=============================================================================
void CMarlin::Attack()
{
    // �Ǐ]�U��
    Rush();
}
