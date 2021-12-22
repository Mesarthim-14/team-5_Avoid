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
#define COLLISION_LENGTH (12100.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapCheckFloor2::CMapCheckFloor2(PRIORITY Priority) : CMap(Priority)
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
    CMapCheckFloor2 *pModel = new CMapCheckFloor2(PRIORITY_MAP);

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
    CMap::Init();

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
    // �����蔻�胂�f���̏I������
    if (m_pColModelCylinder)
    {
        m_pColModelCylinder->Uninit();
        m_pColModelCylinder = nullptr;
    }

    // �I������
    CMap::Uninit();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CMapCheckFloor2::Col()
{
    // �����蔻��
    if (m_pColModelCylinder)
    {
        HitColPlayer(m_pColModelCylinder);
        HitColBossBullet(m_pColModelCylinder);
    }
}