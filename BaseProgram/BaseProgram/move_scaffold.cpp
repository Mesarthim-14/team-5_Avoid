//=============================================================================
//
// ��������N���X [move_scaffold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "move_scaffold.h"
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
#include "library.h"
#include "player.h"
#include "state_player_jump.h"
#include "control_ui.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TURN_TIME       (800.0f)    // ���]�܂ł̃J�E���g
#define SPEED           (100.0f)
#define COLLISION_SIZE  (D3DXVECTOR3(6600.0f, 700.0f, 4100.0f)) // �����蔻�胂�f���̑傫��
#define STOP_DISTANCE   (2000.0f)                               // �~�܂鋗��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMoveScaffold::CMoveScaffold(PRIORITY Priority) : CMap(Priority)
{
    m_nTime = 0;
    m_fSpeed = SPEED;
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
    m_StartPos = D3DXVECTOR3(-53522.5f, 0.0f, -12396.5f);
    m_GoalPos = D3DXVECTOR3(-2309.0f, 0.0f, 60403.7f);
    m_bMove = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMoveScaffold::~CMoveScaffold()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMoveScaffold * CMoveScaffold::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CMoveScaffold *pTestModel = new CMoveScaffold(PRIORITY_MAP);

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
HRESULT CMoveScaffold::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_PARTY_BASE);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // �����蔻�胂�f��(OBB)�̐���
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2.0f), pos.z), D3DXVECTOR3(COLLISION_SIZE.x, 1.0f, COLLISION_SIZE.z), rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, pos.z), COLLISION_SIZE, rot);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMoveScaffold::Uninit()
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
void CMoveScaffold::Update()
{
    // �X�V����
    CMap::Update();

    // �����蔻�胂�f�����̐ݒ�
    for (int nCount = 0; nCount < CCollisionModelOBB::SURFACE_MAX; nCount++)
    {
        if (m_pColModelOBB[nCount])
        {
            m_pColModelOBB[nCount]->SetPos(m_pColModelOBB[nCount]->GetOBB().info.pos + GetMove());
        }
    }

    if (m_bMove)
    {
        // �ړ�����
        Move();
    }
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMoveScaffold::Draw()
{
    CMap::Draw();
}

//=============================================================================
// ���X�|�[��
//=============================================================================
void CMoveScaffold::Respawn()
{
    m_bMove = false;
    SetPos(m_StartPos);
    SetMove(ZeroVector3);

    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        pPlayer->SetBoolJump(true);
        CManager::GetInstance()->GetGame()->GetControlUi()->SwitchTexture(true);
    }

    for (int nCount = 0; nCount < CCollisionModelOBB::SURFACE_MAX; nCount++)
    {
        if (m_pColModelOBB[nCount])
        {
            m_pColModelOBB[nCount]->SetPos(D3DXVECTOR3(m_StartPos.x, m_pColModelOBB[nCount]->GetOBB().info.pos.y, m_StartPos.z));
        }
    }
}

//=============================================================================
// �ړ�����
//=============================================================================
void CMoveScaffold::Move()
{
    D3DXVECTOR3 pos = GetPos();
    SetMove(CLibrary::FollowMoveXZ(pos, m_GoalPos, SPEED));

    if (CLibrary::CalDistance(m_GoalPos, pos) <= STOP_DISTANCE)
    {
        m_bMove = false;
        SetMove(ZeroVector3);

        CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
        if (pPlayer)
        {
            pPlayer->SetBoolJump(true);
            CManager::GetInstance()->GetGame()->GetControlUi()->SwitchTexture(true);
        }
    }

    // �v���C���[���^�ԏ���
    CarryPlayer();
}

//=============================================================================
// �v���C���[���^��
//=============================================================================
void CMoveScaffold::CarryPlayer()
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

//=============================================================================
// ����Ă��邩�̔���
//=============================================================================
void CMoveScaffold::OnOBBs()
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
            m_bMove = true;
            pPlayer->SetBoolJump(false);
            CManager::GetInstance()->GetGame()->GetControlUi()->SwitchTexture(false);
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
// �����蔻��
//=============================================================================
void CMoveScaffold::Col()
{
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP])
    {
        OnOBBs();
    }
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        HitColOBBsPlayer(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
        HitColOBBsBossBullet(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
    }
}