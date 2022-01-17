//=============================================================================
//
// ���N���X [bridge.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "bridge.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collision.h"
#include "collisionModel_OBB.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define COLLISION_SIZE (D3DXVECTOR3(12000.0f, 500.0f, 800.0f))   // �����蔻��̑傫��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBridge::CBridge(PRIORITY Priority) : CMap(Priority)
{
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBridge::~CBridge()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBridge * CBridge::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // �������m��
    CBridge *pTestModel = new CBridge(PRIORITY_MAP);

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
HRESULT CBridge::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // ����������
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_BRIDGE);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // �����蔻��(OBB)�̐���
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2) + 670.0f, pos.z), D3DXVECTOR3(COLLISION_SIZE.x, 1.0f, COLLISION_SIZE.z), rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f + 670.0f, pos.z), COLLISION_SIZE, rot);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBridge::Uninit()
{
    // �����蔻�胂�f���̏I������
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]->Uninit();
        m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = nullptr;
    }
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP])
    {
        m_pColModelOBB[CCollisionModelOBB::SURFACE_UP]->Uninit();
        m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = nullptr;
    }

    // �I������
    CMap::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBridge::Update()
{
    // �X�V����
    CMap::Update();
}

//=============================================================================
// OBB���m�̓����蔻��
//=============================================================================
void CBridge::Col()
{
    // �����蔻��
    if (m_pColModelOBB)
    {
        HitColOBBsPlayer(m_pColModelOBB);
        HitColOBBsBossBullet(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
    }
}