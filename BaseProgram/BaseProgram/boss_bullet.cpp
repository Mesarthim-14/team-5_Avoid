//=============================================================================
//
// �{�X�̔��˒e [boss_bullet.cpp]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "boss_bullet.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collision.h"
#include "collisionModel_Sphere.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS		(ZeroVector3)
#define TEST_ROT		(ZeroVector3)
#define COLLISION_SIZE  (D3DXVECTOR3(90.0f, 90.0f, 90.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBossBullet::CBossBullet(PRIORITY Priority) : CBullet(Priority)
{
	m_pModel = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBossBullet::~CBossBullet()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBossBullet * CBossBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	// �������m��
	CBossBullet *pTestModel = new CBossBullet(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pTestModel)
	{
		pTestModel->m_pos = pos;
		pTestModel->m_rot = rot;
		pTestModel->m_move = move;
		// ����������
		pTestModel->Init();

		return pTestModel;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossBullet::Init(void)
{
    // �T�C�Y�̐ݒ�
    m_size = COLLISION_SIZE;

	// ����������
	CBullet::Init();

	m_pModel = CModel::Create(m_pos, m_rot);
	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CANNON_BULLET);
	m_pModel->GetModelInfo()->SetModelStatus(m_pos, m_rot, model);

	m_nLife = 200;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBossBullet::Uninit(void)
{
	if (m_pModel != nullptr)
	{
		m_pModel->Uninit();
		m_pModel = nullptr;
	}
	CBullet::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossBullet::Update(void)
{
	// �Փ˔���
	Hit();

	if (m_pModel != nullptr)
	{
		m_pModel->GetModelInfo()->SetPos(m_pos);
	}
 	
	CBullet::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossBullet::Draw(void)
{
	CBullet::Draw();
}

//=============================================================================
// �Փ˔���
//=============================================================================
void CBossBullet::Hit(void)
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();

    if (pPlayer)
    {
        if (GetColSpherePtr() && pPlayer->GetColCapsulePtr())
        {
            if (CCollision::ColSphereAndCapsule(GetColSpherePtr()->GetInfo(), pPlayer->GetColCapsulePtr()->GetInfo()))
            {
                Uninit();
            }
        }
    }
}

//=============================================================================
// ���̃|�C���^����
//=============================================================================
void CBossBullet::Move()
{
}