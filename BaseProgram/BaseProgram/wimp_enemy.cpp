//=============================================================================
//
// �T���N���X [wimp_enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "wimp_enemy.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "library.h"
#include "collisionModel_OBB.h"
#include "collision.h"
#include "state_player_knockback.h"
#include "gauge.h"
#include "particlepop.h"
#include "caution_wimp_attack.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PERCEPTION_DISTANCE (23000.0f)  // ���m�ł��鋗��
#define FOLLOW_TIME         (100)       // �d�͂�������Ȃ�����
#define PLAYER_ADD_HEIGHT   (500.0f)    // �v���C���[��K���ɗʑ���
#define HIT_TIME_INTER      (300)       // ����������̊Ԋu
#define CAUTION_TIME        (60)        // �x���̃^�C��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWimpEnemy::CWimpEnemy(PRIORITY Priority) : CEnemy(Priority)
{
    isRush = false;
    m_nRushCount = 0;
    m_pCollision = nullptr;
    m_nHitInter = 0;
    m_bHit = false;
    m_pCaution = nullptr;
    m_nCautionCounter = 0;
    m_bLook = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWimpEnemy::~CWimpEnemy()
{
    if (m_pCollision)
    {
        m_pCollision->Uninit();
        m_pCollision = nullptr;
    }
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWimpEnemy::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot)
{
    CEnemy::Init();
    SetGravityFlag(false);

    if (!m_pCollision)
    {
        m_pCollision = CCollisionModelOBB::Create(pos, size, rot);
    }

    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CWimpEnemy::Update()
{
    CEnemy::Update();

    // �v���C���[��T��
    if (Search())
    {
        if (!m_pCaution)
        {
            m_pCaution = CCautionWimpAttack::Create(GetPos());
            m_nCautionCounter = 0;
            m_bLook = true;
        }
    }

    // �x�����o�Ă�Ƃ�
    if (m_pCaution)
    {
        m_nCautionCounter++;

        if (m_nCautionCounter == CAUTION_TIME)
        {
            m_pCaution->Uninit();
            m_bLook = false;
            Attack();
        }
    }

    if (m_bLook)
    {
        // �v���C���[�����鏈��
        LookAtPlayer();
    }

    if (isRush)
    {
        // �����蔻��
        Collision();

        // �d�͂̐؂�ւ�
        GravitySwitch();
    }
}

//=============================================================================
// �ːi
//=============================================================================
void CWimpEnemy::Rush()
{
    // �ːi
    if (Follow())
    {
        isRush = true;
    }
}

//=============================================================================
// �d�͂�������
//=============================================================================
void CWimpEnemy::GravitySwitch()
{
    m_nRushCount++;
    if (m_nRushCount >= FOLLOW_TIME)
    {
        m_nRushCount = 0;
        SetGravityFlag(true);
    }
}

//=============================================================================
// �v���C���[��T������
//=============================================================================
bool CWimpEnemy::Search()
{
    // �������擾
    D3DXVECTOR3 pos = CManager::GetInstance()->GetPlayer()->GetPos();

    float fDistance = CLibrary::CalDistance(pos, GetPos());
    if (fDistance <= PERCEPTION_DISTANCE)
    {
        return true;
    }

    return false;
}

//=============================================================================
// �Ǐ]
//=============================================================================
bool CWimpEnemy::Follow()
{
    // �������擾
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        D3DXVECTOR3 Ppos = pPlayer->GetPos();
        Ppos.y += PLAYER_ADD_HEIGHT;
         float fSpeed = GetSpeed();
        // 2�_�Ԃ̃x�N�g�������߂�i�I�_[�ڕW�n�_] - �n�_[���g�̈ʒu]�j
        D3DXVECTOR3 Vector = Ppos - GetPos();
        Vector = *D3DXVec3Normalize(&Vector, &Vector);
        Vector *= fSpeed;

        // �ړ��ʂ̐ݒ�
        SetMove(Vector);
        return true;  
    }

    return false;
}

//=============================================================================
// �����蔻��
//=============================================================================
void CWimpEnemy::Collision()
{
    // ���̍X�V
    if (m_pCollision)
    {
        m_pCollision->SetInfo(GetPos(), m_pCollision->GetOBB().info.size, GetRot());
    }

    if (m_bHit)
    {
        m_nHitInter++;

        // ����������Ԃ�߂�
        if (m_nHitInter >= HIT_TIME_INTER)
        {
            m_bHit = false;
            m_nHitInter = 0;
        }
    }
    else
    {
        // �v���C���[�Ƃ̓����蔻��
        CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
        if (pPlayer)
        {
            if (m_pCollision && pPlayer->GetColOBBPtr())
            {
                if (CCollision::ColOBBs(m_pCollision->GetOBB(), pPlayer->GetColOBBPtr()->GetOBB()))
                {
                    // �v���C���[�ւ̉e��
                    AffectPlayer(pPlayer);
                    m_bHit = true;
                }
            }
        }
    }
}

//=============================================================================
// �v���C���[�ɉe����^����
//=============================================================================
void CWimpEnemy::AffectPlayer(CPlayer* &pPlayer)
{
    D3DXVECTOR3 pos = pPlayer->GetPos();
    CGauge * pGauge = CManager::GetInstance()->GetGame()->GetGauge();
    // �v���C���[�Ƀ_���[�W
    pPlayer->SubLife(20);
    pGauge->SetDown((float)20);
    pGauge->SetHitDown(true);
    for (int nCntParticle = 0; nCntParticle <= 10; nCntParticle++)
    {
        CParticlePop::Create(pos);
    }
    D3DXVECTOR3 move = GetMove();
    move.x *= 0.4f;
    move.x *= 0.7f;
    move.z *= 0.4f;
    pPlayer->ChangeState(CPlayerStateKnockback::Create(move));
}