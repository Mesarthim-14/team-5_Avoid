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
#define COLLISION_SIZE (D3DXVECTOR3(6000.0f, 80.0f, 500.0f))   // �����蔻��̑傫��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBridge::CBridge(PRIORITY Priority) : CModel(Priority)
{
    m_pColModelOBB = nullptr;
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
    CBridge *pTestModel = new CBridge(PRIORITY_TEST_MODEL);

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
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_BRIDGE);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // �����蔻��(OBB)�̐���
    if (!m_pColModelOBB)
    {
        m_pColModelOBB = CCollisionModelOBB::Create(pos, COLLISION_SIZE, rot);
    }

    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CBridge::Update()
{
    // �X�V����
    CModel::Update();

    // OBB���m�̓����蔻��
    HitOBBs();
}

//=============================================================================
// OBB���m�̓����蔻��
//=============================================================================
void CBridge::HitOBBs()
{
    // �v���C���[�|�C���^�̎擾
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // �v���C���[�̓����蔻�胂�f���|�C���^�̎擾
    CCollisionModelOBB* pPlayerColModelOBB = pPlayer->GetColOBBPtr();

    if (m_pColModelOBB && pPlayerColModelOBB)
    {
        if (CCollision::ColOBBs(m_pColModelOBB->GetOBB(), pPlayerColModelOBB->GetOBB()))
        {
            // ���n�̏���
            pPlayer->Landing(m_pColModelOBB->GetOBB().info.pos.y + (m_pColModelOBB->GetOBB().info.size.y / 2) + (pPlayerColModelOBB->GetInfo().size.y / 2));
        }
    }
}