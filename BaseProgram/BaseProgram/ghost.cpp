//=============================================================================
//
// �H��N���X [ghost.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "ghost.h"
#include "ghost_model.h"
#include "library.h"
#include "manager.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ATTACK_INTER        (150)                                   // �U���Ԋu
#define ATTACK_STR          (20)                                    // �U����
#define ATTACK_POWER        (2.0f)                                  // ������΂���
#define SPEED               (30.0f)                                 // �X�s�[�h
#define RISE_SPEED          (15.0f)                                 // �㏸���x
#define POS                 (D3DXVECTOR3(-3500.0f, -200.0f, 0.0f))  // ���W
#define FOLLOW_END_DISTANCE (800.0f)                                // �Ǐ]��؂�
#define RISE_TIME           (120)                                   // �I���܂ł̎���
#define END_TIME            (250)                                   // �I���܂ł̎���
#define COLLISION_SIZE  (D3DXVECTOR3(m_fCollisionSize, m_fCollisionSize, m_fCollisionSize))

const float CGhost::m_fCollisionSize = 500.0f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGhost::CGhost(PRIORITY Priority) : CWimpEnemy(Priority)
{
    m_pGhostModel = nullptr;
    m_bFollow = false;
    m_bEnd = false;
    m_nEndCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGhost::~CGhost()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CGhost * CGhost::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // �������m��
    CGhost *pGhost = new CGhost;
    if (pGhost)
    {
        pGhost->Init(pos, rot);
        return pGhost;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGhost::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
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
void CGhost::Uninit()
{
    // ���f���X�V����
    if (m_pGhostModel)
    {
        m_pGhostModel->Uninit();
    }
    CWimpEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGhost::Update()
{
    CWimpEnemy::Update();

    // ���f���X�V����
    if (m_pGhostModel)
    {
        m_pGhostModel->SetPos(GetPos());
    }

    // �ړ�����
    Move();

    // �����蔻��
    Collision();

}

//=============================================================================
// ���f���̐���
//=============================================================================
void CGhost::CreateModel()
{
    // ���f������
    if (!m_pGhostModel)
    {
        m_pGhostModel = CGhostModel::Create(GetPos());
    }
}

//=============================================================================
// �U��
//=============================================================================
void CGhost::Attack()
{
    if (!m_bFollow && !m_bEnd)
    {
        m_bFollow = true;
    }
}

//=============================================================================
// �ړ�
//=============================================================================
void CGhost::Move()
{
    // �Ǐ]�t���O
    if (m_bFollow)
    {
        // �Ǐ]
        if (Follow())
        {

            // ���̋����ɋ߂Â�����
            if (CLibrary::CalDistance(
                CManager::GetInstance()->GetPlayer()->GetPos(), GetPos()) <= FOLLOW_END_DISTANCE)
            {
                m_bFollow = false;
                m_bEnd = true;
            }
        }
    }

    if (m_bEnd)
    {
        m_nEndCount++;
        if (m_nEndCount >= RISE_TIME)
        {
            // �㏸
            Rise();
            if (m_nEndCount >= END_TIME)
            {
                // ������
                Uninit();
                return;
            }
        }
    }
}

//=============================================================================
// �㏸
//=============================================================================
void CGhost::Rise()
{
    D3DXVECTOR3 move = ZeroVector3;
    move.y = RISE_SPEED;
    SetMove(move);
}