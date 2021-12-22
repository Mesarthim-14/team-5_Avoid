//=============================================================================
//
// �Q�M�~�b�N�̏��N���X [swirl_scaffold.object.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "swirl_scaffold_object.h"
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

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_ROT    (D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f))   // �p�x
#define COL_SIZE    (D3DXVECTOR3(3850.0f, 500.0f, 2050.0f))   // �����蔻��T�C�Y

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSwirlScaffoldObject::CSwirlScaffoldObject(PRIORITY Priority) : CMap(Priority)
{
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSwirlScaffoldObject::~CSwirlScaffoldObject()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CSwirlScaffoldObject * CSwirlScaffoldObject::Create(const D3DXVECTOR3 &pos)
{
    // �������m��
    CSwirlScaffoldObject *pRotatebody = new CSwirlScaffoldObject(PRIORITY_MAP);

    // !nullcheck
    if (pRotatebody)
    {
        // ����������
        pRotatebody->Init(pos);
        return pRotatebody;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSwirlScaffoldObject::Init(const D3DXVECTOR3 &pos)
{
    // ����������
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_SPINFLOOR);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    // �����蔻�胂�f���̐���(OBB)
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, COL_SIZE, TEST_ROT);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COL_SIZE.y / 2) + 100.0f, pos.z), D3DXVECTOR3(COL_SIZE.x, 1.0f, COL_SIZE.z), TEST_ROT);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSwirlScaffoldObject::Uninit()
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
}

//=============================================================================
// �X�V����
//=============================================================================
void CSwirlScaffoldObject::Update()
{
    CMap::Update();

    // �����蔻�胂�f���̍X�V
    for (int nCount = 0; nCount < CCollisionModelOBB::SURFACE_MAX; nCount++)
    {
        if (m_pColModelOBB[nCount])
        {
            m_pColModelOBB[nCount]->SetInfo(GetPos(), m_pColModelOBB[nCount]->GetOBB().info.size, GetRot());
        }
    }
}

//=============================================================================
// �����蔻��
//=============================================================================
void CSwirlScaffoldObject::Col()
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
            pPlayer->SetPos(pPlayer->GetPos() + (GetPos() - GetPosOld()));
            SetHitMap(true);
            return;
        }
        else
        {
            if (!GetHitMap())
            {
                // ���n����̐ݒ�
                pPlayer->SetLanding(false);
            }
        }
    }

    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        // ���ʂ̓����蔻��|�C���^�̎擾
        CCollisionModelOBB::OBB surfaceSideObb = m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]->GetOBB();

        if (CCollision::ColOBBs(surfaceSideObb, playerObb))
        {
            // �����̏���
            pPlayer->Fall();
            return;
        }
    }
}