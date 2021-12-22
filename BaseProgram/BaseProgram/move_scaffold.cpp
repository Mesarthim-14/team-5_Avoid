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

//=============================================================================
// �}�N����`
//=============================================================================
#define TURN_TIME       (800.0f)    // ���]�܂ł̃J�E���g
#define SPEED           (20.0f)
#define COLLISION_SIZE  (D3DXVECTOR3(2000.0f, 100.0f, 5000.0f)) // �����蔻�胂�f���̑傫��
#define STOP_DISTANCE   (2000.0f)                               // �~�܂鋗��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMoveScaffold::CMoveScaffold(PRIORITY Priority) : CModel(Priority)
{
    m_nTime = 0;
    m_fSpeed = SPEED;
    m_pColModelOBB = nullptr;
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
    CMoveScaffold *pTestModel = new CMoveScaffold(PRIORITY_TEST_MODEL);

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
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_PARTY_BASE);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // �����蔻�胂�f��(OBB)�̐���
    if (!m_pColModelOBB)
    {
        m_pColModelOBB = CCollisionModelOBB::Create(pos, COLLISION_SIZE, rot);
    }

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMoveScaffold::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMoveScaffold::Update()
{
    if (m_bMove)
    {
        // �ړ�����
        Move();
    }

    // �X�V����
    CModel::Update();

    // OBB���m�̓����蔻��
    HitOBBs();

    // �����蔻�胂�f�����̐ݒ�
    if (m_pColModelOBB)
    {
        m_pColModelOBB->SetInfo(GetPos(), COLLISION_SIZE, GetRot());
    }
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMoveScaffold::Draw()
{
    CModel::Draw();
}

//=============================================================================
// OBB���m�̓����蔻��
//=============================================================================
void CMoveScaffold::HitOBBs()
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
            pPlayer->Landing(m_pColModelOBB->GetOBB().info.pos.y + (m_pColModelOBB->GetOBB().info.size.y / 2) + (pPlayerColModelOBB->GetOBB().info.size.y / 2));
            if (!m_bMove)
            {
                m_bMove = true;
            }
        }
    }
}

//=============================================================================
// ���X�|�[��
//=============================================================================
void CMoveScaffold::Respawn()
{
    if (m_bMove)
    {
        m_bMove = false;
        SetPos(m_StartPos);
        SetMove(ZeroVector3);
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
        D3DXVECTOR3 move = pPlayer->GetPos() + GetMove();
        pPlayer->SetPos(move);
    }
}
