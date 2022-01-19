//=============================================================================
//
// ���˒e [bullet.cpp]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "bullet.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_Sphere.h"
#include "collisionModel_OBB.h"
#include "collision.h"
#include "state_player_knockback.h"
#include "gauge.h"
#include "particlepop.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS		(ZeroVector3)
#define TEST_ROT		(ZeroVector3)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(PRIORITY Priority) : CScene(Priority)
{
	m_pos = ZeroVector3;						// ���W
	m_move = ZeroVector3;						// �ړ���
	m_rot = ZeroVector3;						// ���݂̉�]
    m_ColRadius = 0.0f;					        // �����蔻��T�C�Y
    m_colSizeOBB = ZeroVector3;
	m_nLife = 0;							    // ��������
	m_fSpeed = 0.0f;							// �X�s�[�h
	m_nDamage = 0;							    // �_���[�W��
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
    m_pCollisionModelSphere = nullptr;
    m_pColModelOBB = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init()
{
    // �����蔻�胂�f��(����)�̐���
    if (!m_pCollisionModelSphere)
    {
         m_pCollisionModelSphere = CCollisionModelSphere::Create(m_pos, m_ColRadius, m_rot);
    }

    // �����蔻�胂�f��(OBB)�̐���
    if (!m_pColModelOBB)
    {
        m_pColModelOBB = CCollisionModelOBB::Create(m_pos, m_colSizeOBB, m_rot);
    }

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit()
{
    // �����蔻�胂�f��(����)�̏I������
    if (m_pCollisionModelSphere)
    {
        m_pCollisionModelSphere->Uninit();
        m_pCollisionModelSphere = nullptr;
    }

    // �����蔻�胂�f��(OBB)�̏I������
    if (m_pColModelOBB)
    {
        m_pColModelOBB->Uninit();
        m_pColModelOBB = nullptr;
    }

    Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update()
{
	// �ʒu�X�V
	m_pos += m_move;

	m_nLife--;

	if (m_nLife < 0)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw()
{
}

//=============================================================================
// �Փ˔���
//=============================================================================
void CBullet::Hit()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CGauge * pGauge = CManager::GetInstance()->GetGame()->GetGauge();
    D3DXVECTOR3 pos = pPlayer->GetPos();
    if (!pPlayer)
    {
        return;
    }

    if (m_pCollisionModelSphere)
    {
        if (pPlayer->GetCollision())
        {
            if (CCollision::ColSphereAndCapsule(m_pCollisionModelSphere->GetSphere(), pPlayer->GetColCapsulePtr()->GetInfo()))
            {
                // ������Ԓl
                D3DXVECTOR3 move = GetMove();
                move.x *= 0.5f;
                move.z *= 0.5f;
                move.y = 10.0f;
                pPlayer->ChangeState(CPlayerStateKnockback::Create(move));  // �v���C���[���m�b�N�o�b�N
                pPlayer->SubLife(20);                                       // �̗͂����炷
                // ���g�̏I������
                pGauge->SetHitDown(true);
                pGauge->SetDown(20);
                // �p�[�e�B�N���̐���
                for (int nCntParticle = 0; nCntParticle <= 20; nCntParticle++)
                {
                    CParticlePop::Create(pos);
                }
                Uninit();
                return;
            }
        }
    }
}