//=============================================================================CRubble
//
// ���I�N���X [rubble1.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "rubble1.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_Polygon.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define COLLISION_SIZE  (D3DXVECTOR3(2000.0f, 1000.0f, 6000.0f))    // �����蔻�胂�f��(OBB)�̑傫��
#define COL_POLYGON_SIZE1  (D3DXVECTOR2(6000.0f, 1000.0f))          // �����蔻�胂�f��1(�|���S��)�̑傫��
#define COL_POLYGON_SIZE2  (D3DXVECTOR2(2000.0f, 1000.0f))          // �����蔻�胂�f��2(�|���S��)�̑傫��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRubble1::CRubble1(PRIORITY Priority) : CMap(Priority)
{
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
    memset(m_pColModelPolygon, 0, sizeof(m_pColModelPolygon));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRubble1::~CRubble1()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CRubble1 * CRubble1::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CRubble1 *pTestModel = new CRubble1(PRIORITY_MAP);

    // !nullcheck
    if (pTestModel)
    {
        // ����������
        pTestModel->Init(pos, rot);
        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRubble1::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_PARTY_RUBBLE1);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // �����蔻�胂�f���̐���
    float radian90 = (float)D3DXToRadian(90);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2.0f), pos.z), D3DXVECTOR3(COLLISION_SIZE.x, 1.0f, COLLISION_SIZE.z), rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, D3DXVECTOR3(1.0f, 1.0f, 1.0f), rot);
    m_pColModelPolygon[0] = CCollisionModelPolygon::Create(D3DXVECTOR3(pos.x + (sinf(rot.y + radian90) * (COLLISION_SIZE.x / 2.0f)), pos.y, pos.z + (cosf(rot.y + radian90) * (COLLISION_SIZE.x / 2.0f))), COL_POLYGON_SIZE1, D3DXVECTOR3(rot.x + radian90, rot.y + radian90, rot.z));
    m_pColModelPolygon[1] = CCollisionModelPolygon::Create(D3DXVECTOR3(pos.x + (sinf(rot.y + radian90) * -(COLLISION_SIZE.x / 2.0f)), pos.y, pos.z + (cosf(rot.y + radian90) * -(COLLISION_SIZE.x / 2.0f))), COL_POLYGON_SIZE1, D3DXVECTOR3(rot.x + radian90, rot.y + radian90, rot.z));
    m_pColModelPolygon[2] = CCollisionModelPolygon::Create(D3DXVECTOR3(pos.x + (sinf(rot.y) * (COLLISION_SIZE.z / 2.0f)), pos.y, pos.z + (cosf(rot.y) * (COLLISION_SIZE.z / 2.0f))), COL_POLYGON_SIZE2, D3DXVECTOR3(rot.x + radian90, rot.y, rot.z));
    m_pColModelPolygon[3] = CCollisionModelPolygon::Create(D3DXVECTOR3(pos.x + (sinf(rot.y) * -(COLLISION_SIZE.z / 2.0f)), pos.y, pos.z + (cosf(rot.y) * -(COLLISION_SIZE.z / 2.0f))), COL_POLYGON_SIZE2, D3DXVECTOR3(rot.x - radian90, rot.y, rot.z));

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRubble1::Uninit()
{
    for (int nCount = 0; nCount < CCollisionModelOBB::SURFACE_MAX; nCount++)
    {
        if (m_pColModelOBB[nCount])
        {
            // �����蔻�胂�f���̏I������
            m_pColModelOBB[nCount]->Uninit();
            m_pColModelOBB[nCount] = nullptr;
        }
    }

    for (int nCount = 0; nCount < COL_POLYGON_NUM; nCount++)
    {
        if (m_pColModelPolygon[nCount])
        {
            // �����蔻�胂�f���̏I������
            m_pColModelPolygon[nCount]->Uninit();
            m_pColModelPolygon[nCount] = nullptr;
        }
    }

    CMap::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRubble1::Update()
{
    CMap::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRubble1::Draw()
{
    CMap::Draw();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CRubble1::Col()
{
    if (m_pColModelOBB)
    {
        HitColOBBsPlayer(m_pColModelOBB);
        HitColOBBsBossBullet(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
    }

    for (int nCount = 0; nCount < COL_POLYGON_NUM; nCount++)
    {
        if (m_pColModelPolygon[nCount])
        {
            HitColPolygonPlayer(m_pColModelPolygon[nCount]);
        }
    }
}