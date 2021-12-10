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

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS        (D3DXVECTOR3(-30637.0f, 0.0f, 8337.8f))
#define TEST_ROT        (D3DXVECTOR3(0.0f, D3DXToRadian(135.0f), 0.0f))
#define TURN_TIME       (800.0f)    // ���]�܂ł̃J�E���g
#define SPEED           (8.0f)
#define COLLISION_SIZE  (D3DXVECTOR3(2000.0f, 100.0f, 5000.0f)) // �����蔻�胂�f���̑傫��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMoveScaffold::CMoveScaffold(PRIORITY Priority) : CModel(Priority)
{
    m_nTime = 0;
    m_fSpeed = SPEED;
    m_pColModelOBB = nullptr;
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
CMoveScaffold * CMoveScaffold::Create()
{
    // �������m��
    CMoveScaffold *pTestModel = new CMoveScaffold(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pTestModel)
    {
        // ����������
        pTestModel->Init();

        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMoveScaffold::Init()
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MOVE_SCAFFOLD);
    GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);

    // �����蔻�胂�f��(OBB)�̐���
    if (!m_pColModelOBB)
    {
        m_pColModelOBB = CCollisionModelOBB::Create(TEST_POS, COLLISION_SIZE, TEST_ROT);
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
    // �ړ�����
    Move();

    // �X�V����
    CModel::Update();

    // OBB���m�̓����蔻��
    HitOBBs();

    // �����蔻�胂�f�����̐ݒ�
    if (m_pColModelOBB)
    {
        m_pColModelOBB->SetInfo(GetPos(), COLLISION_SIZE, TEST_ROT);
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
        }
    }
}

//=============================================================================
// �ړ�����
//=============================================================================
void CMoveScaffold::Move()
{
    m_nTime++;
    
    float fAngle = GetModelInfo()->GetRot().y;

    // �ړ��ʐݒ�
    D3DXVECTOR3 move = D3DXVECTOR3(
        cosf(D3DXToRadian(fAngle+45.0f))*m_fSpeed, 
        0.0f, sinf(D3DXToRadian(fAngle + 45.0f))*m_fSpeed);

    // �ړ��ʐݒ�
    SetMove(move);

    // ��莞�Ԃ�
    if (m_nTime >= TURN_TIME)
    {
        m_nTime = 0;
        m_fSpeed *= -1;
    }
}