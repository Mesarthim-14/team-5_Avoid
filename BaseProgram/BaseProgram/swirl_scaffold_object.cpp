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
#include "state_player_jump.h"

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
    m_bMove = false;
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
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COL_SIZE.y / 2) + 50.0f, pos.z), D3DXVECTOR3(COL_SIZE.x, 1.0f, COL_SIZE.z), TEST_ROT);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, COL_SIZE, TEST_ROT);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSwirlScaffoldObject::Uninit()
{
    for (int nCount = 0; nCount < CCollisionModelOBB::SURFACE_MAX; nCount++)
    {
        // �����蔻�胂�f���̏I������
        if (m_pColModelOBB[nCount])
        {
            m_pColModelOBB[nCount]->Uninit();
            m_pColModelOBB[nCount] = nullptr;
        }
    }

    CMap::Uninit();
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
            m_pColModelOBB[nCount]->SetPos(D3DXVECTOR3(GetPos().x, m_pColModelOBB[nCount]->GetOBB().info.pos.y, GetPos().z));
        }
    }

    // �v���C���[���^�ԏ���
    CarryPlayer();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CSwirlScaffoldObject::Col()
{
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP])
    {
        // ����Ă��邩�̔���
        OnOBBs();
    }
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        HitColOBBsPlayer(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
        HitColOBBsBossBullet(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
    }
}

//=============================================================================
// ����Ă��邩�̔���
//=============================================================================
void CSwirlScaffoldObject::OnOBBs()
{
    // �v���C���[�|�C���^�̎擾
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    if (pPlayer->GetState() == CPlayer::JUMP)
    { // �W�����v��Ԃ̂Ƃ�
        CPlayerStateJump* pStateJump = (CPlayerStateJump*)pPlayer->GetCurrentState();
        if (pStateJump->GetJumpCheck())
        { // �W�����v���n�߂Ă���Ƃ�
            if (pStateJump->GetJumpTimeCount() < NOT_COLLISION_TIME)
            { // �����蔻����s��Ȃ����Ԃ�菭�Ȃ��Ƃ�
                return;
            }
        }
    }

    // �v���C���[�̓����蔻�胂�f���|�C���^�̎擾
    CCollisionModelOBB* pPlayerColModelOBB = pPlayer->GetColOBBPtr();

    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] && pPlayerColModelOBB)
    {
        // ��ʂ̓����蔻��|�C���^�̎擾
        CCollisionModelOBB::OBB surfaceUpObb = m_pColModelOBB[CCollisionModelOBB::SURFACE_UP]->GetOBB();

        if (CCollision::ColOBBs(surfaceUpObb, pPlayerColModelOBB->GetOBB()))
        {
            // ���n�̏���
            pPlayer->Landing(surfaceUpObb.info.pos.y + (surfaceUpObb.info.size.y / 2.0f) + (pPlayerColModelOBB->GetOBB().info.size.y / 2.0f));
            SetHitMap(true);

            if (!m_bMove)
            {
                m_bMove = true;
            }
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
}

//=============================================================================
// �v���C���[���^��
//=============================================================================
void CSwirlScaffoldObject::CarryPlayer()
{
    if (m_bMove)
    {
        CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
        if (pPlayer)
        {
            if (pPlayer->GetMove().y == 0.0f)
            {
                pPlayer->SetPos(pPlayer->GetPos() + GetMove());
            }
            else
            {
                m_bMove = false;
            }
        }
    }
}