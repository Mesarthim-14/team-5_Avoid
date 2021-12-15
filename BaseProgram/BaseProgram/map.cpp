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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMap::CMap(PRIORITY Priority) : CModel(Priority)
{
    m_bHitOld = false;
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
HRESULT CMap::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CModel::Init();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMap::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMap::Update()
{
    CModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMap::Draw()
{
    CModel::Draw();
}

//=============================================================================
// �����蔻��(�����̓��m)
//=============================================================================
void CMap::HitColOBBs(CCollisionModelOBB** pMapColOBB)
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
            m_bHitOld = true;
            return;
        }
        else
        {
            if (m_bHitOld)
            {
                // ���n����̐ݒ�
                pPlayer->SetLanding(false);
                m_bHitOld = false;
            }
        }
    }

    if (pMapColOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        // ���ʂ̓����蔻��|�C���^�̎擾
        CCollisionModelOBB::OBB surfaceSizeObb = pMapColOBB[CCollisionModelOBB::SURFACE_SIDE]->GetOBB();

        if (CCollision::ColOBBs(surfaceSizeObb, playerObb))
        {
            // �����̏���
            pPlayer->Fall();
            return;
        }
    }
}

//=============================================================================
// �����蔻��(���̂Ɖ~��)
//=============================================================================
void CMap::HitColSphereAndCylinder(CCollisionModelCylinder * pMapColCylinder)
{
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

    // �����蔻�胂�f��(�~��)���̎擾
    CCollisionModelCylinder::CYLINDER colCylinderInfo;
    if (pMapColCylinder)
    {
        colCylinderInfo = pMapColCylinder->GetCylinder();
    }
    else
        return;

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
            return;
        }
        else if (surface == CCollision::SURFACE_SIDE)
        {
            // �����̏���
            pPlayer->Fall();
            return;
        }
    }
}