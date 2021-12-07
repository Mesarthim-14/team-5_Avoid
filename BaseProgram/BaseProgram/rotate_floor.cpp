//=============================================================================
//
// ��]���N���X [rotate_floor.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "rotate_floor.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "collision.h"
#include "collisionModel_Cylinder.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS    (D3DXVECTOR3(-34328.4f, 0.0f, -6081.8f))
#define TEST_ROT    (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))
#define ROTATE_NUM  (D3DXToRadian(2.0f))                                    // ��]�̒l
#define COLLISION_RADIUS    (1500.0f)                                       // �����蔻�胂�f��(�~��)�̔��a�̑傫��
#define COLLISION_LENGTH    (400.0f)                                        // �����蔻�胂�f��(�~��)�̏c�̑傫��
#define COLLISION_ROT       (D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f))  // �����蔻�胂�f��(�~��)�̊p�x

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRotateFloor::CRotateFloor(PRIORITY Priority) : CModel(Priority)
{
    m_pColModelCylinder = nullptr;
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CRotateFloor * CRotateFloor::Create(const D3DXVECTOR3 &pos)
{
    // �������m��
    CRotateFloor *pTestModel = new CRotateFloor(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pTestModel)
    {
        // ����������
        pTestModel->Init(pos);

        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRotateFloor::Init(const D3DXVECTOR3 &pos)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ROTATE_FLOOR);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    // �����蔻�胂�f��(�~��)�̐���
    if (!m_pColModelCylinder)
    {
        m_pColModelCylinder = CCollisionModelCylinder::Create(pos, COLLISION_RADIUS, COLLISION_LENGTH, COLLISION_ROT);
    }

    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CRotateFloor::Update()
{
    // �X�V����
    CModel::Update();

    if (m_pColModelCylinder)
    {
        // �����蔻�胂�f��(�~��)�̏��擾
        CCollisionModel::INFO ColModelCylinderInfo = m_pColModelCylinder->GetInfo();

        // �����蔻�胂�f��(�~��)�̐ݒ�
        m_pColModelCylinder->SetInfo(GetPos(),
            ColModelCylinderInfo.size,
            D3DXVECTOR3(ColModelCylinderInfo.rot.x, GetRot().y, ColModelCylinderInfo.rot.z));
    }

    // �~���Ƌ��̂̓����蔻��
    HitCylinderAndSphere();
}

//=============================================================================
// �~���Ƌ��̂̓����蔻��
//=============================================================================
void CRotateFloor::HitCylinderAndSphere()
{
    // �v���C���[�|�C���^�̎擾
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // �v���C���[�̓����蔻�胂�f���|�C���^�̎擾
    CCollisionModelCapsule* pPlayerColModelCapsule = pPlayer->GetColCapsulePtr();

    // �v���C���[�̓����蔻�胂�f��(�J�v�Z��)�̏��擾
    CCollisionModelCapsule::INFO PlayerColModelCapsuleInfo = pPlayerColModelCapsule->GetInfo();

    if (m_pColModelCylinder && pPlayerColModelCapsule)
    {
        CCollisionModel::INFO PlayerColModelSphereInfo =
        {
            PlayerColModelCapsuleInfo.P1,
            D3DXVECTOR3(PlayerColModelCapsuleInfo.radius * 2, PlayerColModelCapsuleInfo.radius * 2, PlayerColModelCapsuleInfo.radius * 2),
            PlayerColModelCapsuleInfo.rot
        };

        // �����蔻�胂�f��(�~��)�̏��擾
        CCollisionModel::INFO ColModelCylinderInfo = m_pColModelCylinder->GetInfo();

        // �����蔻��p�ϐ�
        bool bHit = false;                                      // �Փ˔���
        CCollision::SURFACE surface = CCollision::SURFACE_NONE; // �Փ˖�

        // �~���Ƌ��̂̓����蔻��
        CCollision::ColSphereAndCylinder(bHit, surface, PlayerColModelSphereInfo, ColModelCylinderInfo);

        if (bHit)
        { // �������Ă���Ƃ�

            if (surface == CCollision::SURFACE_UP)
            {
                // ���n�̏���
                pPlayer->Landing(ColModelCylinderInfo.pos.y + (ColModelCylinderInfo.size.z / 2) + (PlayerColModelCapsuleInfo.length / 2));
            }
            else
            {
                D3DXVECTOR3 playerOldPos = pPlayer->GetOldPos();
                pPlayer->SetPos(D3DXVECTOR3(playerOldPos.x, pPlayer->GetPos().y, playerOldPos.z));
            }
        }
    }
}