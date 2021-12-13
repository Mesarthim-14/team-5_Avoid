//=============================================================================
//
// �`�F�b�N�|�C���g�̃I�u�W�F [map_check_floor2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "map_check_floor2.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_Cylinder.h"
#include "collision.h"
#include "blur_filter.h"
#include "gauss_filter.h"
#include "library.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define COLLISION_RADIUS (5000.0f)
#define COLLISION_LENGTH (11900.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapCheckFloor2::CMapCheckFloor2(PRIORITY Priority) : CModel(Priority)
{
    m_pColModelCylinder = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapCheckFloor2::~CMapCheckFloor2()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMapCheckFloor2 * CMapCheckFloor2::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CMapCheckFloor2 *pModel = new CMapCheckFloor2(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pModel)
    {
        // ����������
        pModel->Init(pos, rot);
        return pModel;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMapCheckFloor2::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_CHECK_FLOOR2);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // �����蔻�胂�f��(�~��)�̐���
    m_pColModelCylinder = CCollisionModelCylinder::Create(pos, COLLISION_RADIUS, COLLISION_LENGTH, rot);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMapCheckFloor2::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMapCheckFloor2::Update()
{
    CModel::Update();

    // �����蔻��
    HitCol();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMapCheckFloor2::Draw()
{
    CModel::Draw();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CMapCheckFloor2::HitCol()
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
    CCollisionModel::INFO PlayerColModelSphereInfo =
    {
        PlayerColModelCapsuleInfo.P1,
        D3DXVECTOR3(PlayerColModelCapsuleInfo.radius * 2, PlayerColModelCapsuleInfo.radius * 2, PlayerColModelCapsuleInfo.radius * 2),
        PlayerColModelCapsuleInfo.rot
    };

    // �����蔻�胂�f��(�~��)���̎擾
    CCollisionModel::INFO colCylinderInfo;
    if (m_pColModelCylinder)
    {
        colCylinderInfo = m_pColModelCylinder->GetInfo();
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
            pPlayer->Landing(colCylinderInfo.pos.y + (colCylinderInfo.size.z / 2) + (PlayerColModelCapsuleInfo.length / 2));
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