//=============================================================================
//
// �����̂̏��N���X [map_square_floor.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "map_square_floor.h"
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
#define COLLISION_SIZE (D3DXVECTOR3(9700.0f,2450.0f,9500.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapSquareFloor::CMapSquareFloor(PRIORITY Priority) : CMap(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapSquareFloor::~CMapSquareFloor()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMapSquareFloor * CMapSquareFloor::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CMapSquareFloor *pModel = new CMapSquareFloor(PRIORITY_MAP);

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
HRESULT CMapSquareFloor::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_SQUARE_FLOOR);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //�����蔻�胂�f��(OBB)�̐���
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, COLLISION_SIZE, rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2 + 100.0f), pos.z), D3DXVECTOR3(COLLISION_SIZE.x - 100.0f, 100.0f, COLLISION_SIZE.z - 100.0f), rot);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMapSquareFloor::Uninit()
{
    // �I������
    CMap::Uninit();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CMapSquareFloor::Col()
{
    // �����蔻��
    if (m_pColModelOBB)
    {
        HitColOBBsPlayer(m_pColModelOBB);
        HitColOBBsBossBullet(m_pColModelOBB);
    }
}