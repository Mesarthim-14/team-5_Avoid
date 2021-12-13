//=============================================================================
//
// �e�X�g���f���N���X [map_first_floor.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "map_first_floor.h"
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
#define COLLISION_SIZE (D3DXVECTOR3(10500.0f,3100.0f,15350.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapFirstFloor::CMapFirstFloor(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapFirstFloor::~CMapFirstFloor()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMapFirstFloor * CMapFirstFloor::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CMapFirstFloor *pModel = new CMapFirstFloor(PRIORITY_TEST_MODEL);

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
HRESULT CMapFirstFloor::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_FIRST_FLOOR);
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
void CMapFirstFloor::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMapFirstFloor::Update()
{
    CModel::Update();

    // �����蔻��
    HitCol();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMapFirstFloor::Draw()
{
    CModel::Draw();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CMapFirstFloor::HitCol()
{
    // �v���C���[�|�C���^�̎擾
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // �v���C���[�̓����蔻�胂�f���|�C���^�̎擾
    CCollisionModelOBB* pPlayerColModelOBB = pPlayer->GetColOBBPtr();

    // �v���C���[�̓����蔻��|�C���^�̎擾
    CCollisionModelOBB::OBB playerObb;
    if (pPlayerColModelOBB)
    {
        playerObb = pPlayerColModelOBB->GetOBB();
    }
    else
        return;

    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP])
    {
        // ��ʂ̓����蔻��|�C���^�̎擾
        CCollisionModelOBB::OBB surfaceUpObb = m_pColModelOBB[CCollisionModelOBB::SURFACE_UP]->GetOBB();

        if (CCollision::ColOBBs(surfaceUpObb, playerObb))
        {
            // ���n�̏���
            pPlayer->Landing(surfaceUpObb.info.pos.y + (surfaceUpObb.info.size.y / 2) + (playerObb.info.size.y / 2));
            return;
        }
        else
        {
            // ���n����̐ݒ�
            pPlayer->SetLanding(false);
        }
    }

    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        // ���ʂ̓����蔻��|�C���^�̎擾
        CCollisionModelOBB::OBB surfaceSizeObb = m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]->GetOBB();

        if (CCollision::ColOBBs(surfaceSizeObb, playerObb))
        {
            // �����̏���
            pPlayer->Fall();
            return;
        }
    }
}