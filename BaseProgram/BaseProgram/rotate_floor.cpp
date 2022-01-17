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
#include "collisionModel_OBB.h"
#include "collisionModel_Polygon.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS    (D3DXVECTOR3(-34328.4f, 0.0f, -6081.8f))
#define TEST_ROT    (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))
#define ROTATE_NUM  (D3DXToRadian(2.0f))                                // ��]�̒l
#define COL_SIZE_OBB        (D3DXVECTOR3(19000.0f, 6000.0f, 9000.0f))       // �����蔻�胂�f��(OBB)�̑傫��
#define COL_SIZE_POLYGON    (D3DXVECTOR2(COL_SIZE_OBB.x, COL_SIZE_OBB.z))   // �����蔻�胂�f��(�|���S��)�̑傫��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRotateFloor::CRotateFloor(PRIORITY Priority) : CMap(Priority)
{
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CRotateFloor * CRotateFloor::Create(const D3DXVECTOR3 &pos)
{
    // �������m��
    CRotateFloor *pTestModel = new CRotateFloor(PRIORITY_MAP);

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
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_SPINSHIP_SHIP);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    // �����蔻�胂�f���̐���
    D3DXVECTOR3 rot = GetRot();
    m_pColModelOBB[0][CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x + 1700.0f, pos.y + (COL_SIZE_OBB.y / 2.0f), pos.z), D3DXVECTOR3(COL_SIZE_OBB.x, 0.0f, COL_SIZE_OBB.z), rot);
    m_pColModelOBB[0][CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x + 1700.0f, pos.y - 150.0f, pos.z), COL_SIZE_OBB, rot);
    m_pColModelOBB[1][CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x - 8500.0f, pos.y + (COL_SIZE_OBB.y / 2.0f), pos.z - 1000.0f), D3DXVECTOR3(6000.0f, 0.0f, 4000.0f), D3DXVECTOR3(rot.x, rot.y + D3DXToRadian(48), rot.z));
    m_pColModelOBB[1][CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x - 8500.0f, pos.y - 150.0f, pos.z - 1000.0f), D3DXVECTOR3(6000.0f, COL_SIZE_OBB.y, 4000.0f), D3DXVECTOR3(rot.x, rot.y + D3DXToRadian(48), rot.z));
    m_pColModelOBB[2][CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x - 8500.0f, pos.y + (COL_SIZE_OBB.y / 2.0f), pos.z + 1000.0f), D3DXVECTOR3(6000.0f, 0.0f, 4000.0f), D3DXVECTOR3(rot.x, rot.y + D3DXToRadian(-48), rot.z));
    m_pColModelOBB[2][CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x - 8500.0f, pos.y - 150.0f, pos.z + 1000.0f), D3DXVECTOR3(6000.0f, COL_SIZE_OBB.y, 4000.0f), D3DXVECTOR3(rot.x, rot.y + D3DXToRadian(-48), rot.z));

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRotateFloor::Uninit()
{
    for (int nCount = 0; nCount < COL_NUM; nCount++)
    {
        for (int nCnt = 0; nCnt < CCollisionModelOBB::SURFACE_MAX; nCnt++)
        {
            // �����蔻�胂�f���̏I������
            if (m_pColModelOBB[nCount][nCnt])
            {
                m_pColModelOBB[nCount][nCnt]->Uninit();
                m_pColModelOBB[nCount][nCnt] = nullptr;
            }
        }
    }

    CMap::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRotateFloor::Update()
{
    // �X�V����
    CMap::Update();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CRotateFloor::Col()
{
    for (int nCount = 0; nCount < COL_NUM; nCount++)
    {
        if (m_pColModelOBB[nCount])
        {
            HitColOBBsPlayer(m_pColModelOBB[nCount]);
            HitColOBBsBossBullet(m_pColModelOBB[nCount][CCollisionModelOBB::SURFACE_SIDE]);
        }
    }
}