//=============================================================================
//
// �傫���I�u�W�F�N�g [map_big_floor2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "map.h"
#include "manager.h"
#include "player.h"
#include "collision.h"
#include "game.h"
#include "kraken.h"
#include "state_kraken_normal.h"
#include "boss_bullet.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
bool CMap::m_bHitMap = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMap::CMap(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMap::~CMap()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMap::Init()
{
    // ���f���̏���������
    CModel::Init();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMap::Uninit()
{
    // ���f���̏I������
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMap::Update()
{
    // ���f���̍X�V����
    CModel::Update();

    // �����蔻�菈��
    Col();

    // ���̃I�u�W�F�N�g(�v���C�I���e�B�F�}�b�v)���Ȃ��Ƃ�
    if (!GetNext())
    {
        // �P�ȏ�}�b�v�ɓ������Ă��邩�̔����������
        m_bHitMap = false;
    }
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMap::Draw()
{
    // ���f���̕`�揈��
    CModel::Draw();
}

//=============================================================================
// �v���C���[�Ƃ̓����蔻��(�����̓��m)
//=============================================================================
void CMap::HitColOBBsPlayer(const CCollisionModelOBB* const* pMapColOBB)
{
    // �v���C���[�|�C���^�̎擾
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // �v���C���[�̓����蔻�胂�f���|�C���^�̎擾
    CCollisionModelOBB* pPlayerColModelOBB = pPlayer->GetColOBBPtr();

    // �v���C���[�̓����蔻��|�C���^�̎擾
    CCollisionModelOBB::OBB playerObb;
    if (pPlayerColModelOBB)
    {
        playerObb = pPlayerColModelOBB->GetOBB();
    }
    else
        return;

    if (pMapColOBB[CCollisionModelOBB::SURFACE_UP])
    {
        // ��ʂ̓����蔻��|�C���^�̎擾
        CCollisionModelOBB::OBB surfaceUpObb = pMapColOBB[CCollisionModelOBB::SURFACE_UP]->GetOBB();

        if (CCollision::ColOBBs(surfaceUpObb, playerObb))
        {
            // ���n�̏���
            pPlayer->Landing(surfaceUpObb.info.pos.y + (surfaceUpObb.info.size.y / 2) + (playerObb.info.size.y / 2));
            m_bHitMap = true;
            return;
        }
        else
        {
            if (!m_bHitMap)
            {
                // ���n����̐ݒ�
                pPlayer->SetLanding(false);
            }
        }
    }

    if (pMapColOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        // ���ʂ̓����蔻��|�C���^�̎擾
        CCollisionModelOBB::OBB surfaceSideObb = pMapColOBB[CCollisionModelOBB::SURFACE_SIDE]->GetOBB();

        if (CCollision::ColOBBs(surfaceSideObb, playerObb))
        {
            // �����̏���
            pPlayer->Fall();
            return;
        }
    }
}

//=============================================================================
// �{�X�o���b�g�Ƃ̓����蔻��(�����̓��m)
//=============================================================================
void CMap::HitColOBBsBossBullet(const CCollisionModelOBB* const* pMapColOBB)
{
    // �e�̃|�C���^�̎擾
    CBossBullet* pBossBullet = (CBossBullet*)GetTop(PRIORITY_BULLET);
    if (!pBossBullet)
        return;

    if (pMapColOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        // ���ʂ̓����蔻��|�C���^�̎擾
        CCollisionModelOBB::OBB surfaceSideObb = pMapColOBB[CCollisionModelOBB::SURFACE_SIDE]->GetOBB();

        while (pBossBullet)
        {
            // �����蔻��(���̂�OBB)��true ���� �e�̔j�����肪false�̂Ƃ�
            if (CCollision::ColOBBs(pBossBullet->GetColOBBPtr()->GetOBB(), surfaceSideObb) && !pBossBullet->GetDeath())
            {
                // �e�̔j�������true�ɂ���
                pBossBullet->SetDeath();
                return;
            }

            pBossBullet = (CBossBullet*)pBossBullet->GetNext();
        }
    }
}

//=============================================================================
// �v���C���[�Ƃ̓����蔻��֐�(���̂Ɖ~��)
//=============================================================================
void CMap::HitColPlayer(const CCollisionModelCylinder* const pMapColCylinder)
{
    // �����蔻�胂�f��(�~��)���̎擾
    CCollisionModelCylinder::CYLINDER colCylinderInfo;
    if (pMapColCylinder)
    {
        colCylinderInfo = pMapColCylinder->GetCylinder();
    }
    else
        return;

    // �v���C���[�|�C���^�̎擾
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // �v���C���[�̓����蔻�胂�f���|�C���^�̎擾
    CCollisionModelCapsule* pPlayerColModelCapsule = pPlayer->GetColCapsulePtr();
    if (!pPlayerColModelCapsule)
        return;

    // �v���C���[�̓����蔻�胂�f��(�J�v�Z��)�̏��擾
    CCollisionModelCapsule::INFO PlayerColModelCapsuleInfo = pPlayerColModelCapsule->GetInfo();

    // �v���C���[�̓����蔻�胂�f��(�J�v�Z��)��񂩂狅�̂̏���ݒ�
    CCollisionModelSphere::SPHERE PlayerColModelSphereInfo =
    {
        {
            PlayerColModelCapsuleInfo.detail.sphere2.pos,
            D3DXVECTOR3(PlayerColModelCapsuleInfo.detail.sphere2.radius * 2, PlayerColModelCapsuleInfo.detail.sphere2.radius * 2, PlayerColModelCapsuleInfo.detail.sphere2.radius * 2),
            PlayerColModelCapsuleInfo.detail.sphere2.rot
        },
        PlayerColModelCapsuleInfo.radius
    };

    bool bHit = false;                                      // �����������̔���
    CCollision::SURFACE surface = CCollision::SURFACE_NONE; // ����������

    // �����蔻��(���̂Ɖ~��)
    CCollision::ColSphereAndCylinder(bHit, surface, PlayerColModelSphereInfo, colCylinderInfo);

    if (bHit)
    {
        if (surface == CCollision::SURFACE_UP)
        {
            // ���n�̏���
            pPlayer->Landing(colCylinderInfo.info.pos.y + (colCylinderInfo.length / 2) + (PlayerColModelCapsuleInfo.length / 2));
            m_bHitMap = true;
            return;
        }
        else if (surface == CCollision::SURFACE_SIDE)
        {
            // �����̏���
            pPlayer->Fall();
            m_bHitMap = true;
            return;
        }
    }
    else
    {
        if (!m_bHitMap)
        {
            // ���n����̐ݒ�
            pPlayer->SetLanding(false);
        }
    }
}

//=============================================================================
// �{�X�o���b�g�Ƃ̓����蔻��֐�(���̂Ɖ~��)
//=============================================================================
void CMap::HitColBossBullet(const CCollisionModelCylinder* const pMapColCylinder)
{
    // �����蔻�胂�f��(�~��)���̎擾
    CCollisionModelCylinder::CYLINDER colCylinderInfo;
    if (pMapColCylinder)
    {
        colCylinderInfo = pMapColCylinder->GetCylinder();
    }
    else
        return;

    // �e�̃|�C���^�̎擾
    CBossBullet* pBossBullet = (CBossBullet*)GetTop(PRIORITY_BULLET);
    if (!pBossBullet)
        return;

    bool bHit = false;                                      // �����������̔���
    CCollision::SURFACE surface = CCollision::SURFACE_NONE; // ����������

    while (pBossBullet)
    {
        // �����蔻��p�ϐ��̏�����
        bHit = false;
        surface = CCollision::SURFACE_NONE;

        // �����蔻��(���̂Ɖ~��)
        CCollision::ColSphereAndCylinder(bHit, surface, pBossBullet->GetColSpherePtr()->GetSphere(), colCylinderInfo);

        if (bHit && !pBossBullet->GetDeath())
        {
            // �e�̔j�������true�ɂ���
            pBossBullet->SetDeath();
            return;
        }

        pBossBullet = (CBossBullet*)pBossBullet->GetNext();
    }
}