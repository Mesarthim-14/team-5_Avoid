//=============================================================================
//
// �⓹�N���X [slope.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "slope.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_OBB.h"
#include "collisionModel_Polygon.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS            (D3DXVECTOR3(-10040.0f, 514.8f, -15282.6f))
#define TEST_ROT            (D3DXVECTOR3(D3DXToRadian(-17.0f), 0.0f, 0.0f))
#define COL_SIZE_OBB        (D3DXVECTOR3(8000.0f, 200.0f, 18000.0f))
#define COL_SIZE_POLYGON    (D3DXVECTOR2(7500.0f, 18000.0f))
#define COL_ROT             (D3DXVECTOR3(D3DXToRadian(-17.0f), 0.0f, 0.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSlope::CSlope(PRIORITY Priority) : CMap(Priority)
{
    m_pColModelOBB = nullptr;
    m_pColModelPolygon = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSlope::~CSlope()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CSlope * CSlope::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // �������m��
    CSlope *pTestModel = new CSlope(PRIORITY_MAP);

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
HRESULT CSlope::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // ����������
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_SLOOP);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // �����蔻�胂�f���̐���
    m_pColModelPolygon = CCollisionModelPolygon::Create(D3DXVECTOR3(pos.x, pos.y + 180.0f, pos.z), COL_SIZE_POLYGON, D3DXVECTOR3(COL_ROT.x, rot.y, COL_ROT.z));
    m_pColModelOBB = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y - 150.0f, pos.z), COL_SIZE_OBB, D3DXVECTOR3(COL_ROT.x, rot.y, COL_ROT.z));

    return S_OK;
}

//=============================================================================
// ����������
//=============================================================================
void CSlope::Uninit()
{
    // �����蔻�胂�f���̏I��
    if (m_pColModelPolygon)
    {
        m_pColModelPolygon->Uninit();
        m_pColModelPolygon = nullptr;
    }
    if (m_pColModelOBB)
    {
        m_pColModelOBB->Uninit();
        m_pColModelOBB = nullptr;
    }

    // ���f���̏I������
    CMap::Uninit();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CSlope::Col()
{
    if (m_pColModelPolygon)
    {
        HitColOBBsPlayer(m_pColModelPolygon);
    }
    if (m_pColModelOBB)
    {
        HitColOBBsPlayer(m_pColModelOBB);
        HitColOBBsBossBullet(m_pColModelOBB);
    }
}