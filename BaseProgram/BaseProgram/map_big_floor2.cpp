//=============================================================================
//
// �傫���I�u�W�F�N�g [map_big_floor2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "map_big_floor2.h"
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
#define COLLISION_SIZE (D3DXVECTOR3(8800.0f, 12200.0f, 31500.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapBigFloor2::CMapBigFloor2(PRIORITY Priority) : CMap(Priority)
{
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapBigFloor2::~CMapBigFloor2()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMapBigFloor2 * CMapBigFloor2::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CMapBigFloor2 *pModel = new CMapBigFloor2(PRIORITY_MAP);

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
HRESULT CMapBigFloor2::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_FIRST_FLOOR2);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //�����蔻�胂�f��(OBB)�̐���
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, COLLISION_SIZE, rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2) + 100.0f, pos.z), D3DXVECTOR3(8500.0f, 100.0f, 31400.0f), rot);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMapBigFloor2::Uninit()
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
// �����蔻��
//=============================================================================
void CMapBigFloor2::Col()
{
    // �����蔻��
    if (m_pColModelOBB)
    {
        HitColOBBsPlayer(m_pColModelOBB);
        HitColOBBsBossBullet(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
    }
}