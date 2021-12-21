//=============================================================================
//
// �����`�̏��N���X [map_thin_floor.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "map_thin_floor.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_OBB.h"
#include "collision.h"
#include "blur_filter.h"
#include "gauss_filter.h"
#include "library.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define COLLISION_SIZE (D3DXVECTOR3(13000.0f,2200.0f,9500.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapThinFloor::CMapThinFloor(PRIORITY Priority) : CMap(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapThinFloor::~CMapThinFloor()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMapThinFloor * CMapThinFloor::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CMapThinFloor *pModel = new CMapThinFloor(PRIORITY_MAP);

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
HRESULT CMapThinFloor::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_THIN_FLOOR);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //�����蔻�胂�f��(OBB)�̐���
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, COLLISION_SIZE, rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2 + 50.0f), pos.z), D3DXVECTOR3(COLLISION_SIZE.x - 100.0f, 1.0f, COLLISION_SIZE.z - 100.0f), rot);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMapThinFloor::Uninit()
{
    // �I������
    CMap::Uninit();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CMapThinFloor::Col()
{
    // �����蔻��
    if (m_pColModelOBB)
    {
        HitColOBBsPlayer(m_pColModelOBB);
        HitColOBBsBossBullet(m_pColModelOBB);
    }
}