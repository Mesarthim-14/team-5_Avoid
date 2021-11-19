//=============================================================================
//
// �e�X�g���f���N���X [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "test_model.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel.h"
#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS		(ZeroVector3)
#define TEST_ROT		(ZeroVector3)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTestModel::CTestModel(PRIORITY Priority) : CModel(Priority)
{
	m_pCollisionModel = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTestModel::~CTestModel()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTestModel * CTestModel::Create()
{
	// �������m��
	CTestModel *pTestModel = new CTestModel(PRIORITY_TEST_MODEL);

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
HRESULT CTestModel::Init()
{
	// ����������
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP);
	GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);

	//�����蔻�胂�f���̐���
	if (m_pCollisionModel == nullptr)
	{
		m_pCollisionModel = CCollisionModel::Create(GetModelInfo()->GetPos(), D3DXVECTOR3(5000.0f, 100.0f, 4200.0f), TEST_ROT, CCollisionModel::TYPE_BOX);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTestModel::Uninit()
{
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTestModel::Update()
{
	CModel::Update();

	// �Փ˔���
	Hit();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTestModel::Draw()
{
	CModel::Draw();
}

//=============================================================================
// �Փ˔���
//=============================================================================
void CTestModel::Hit()
{
	CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();

	if (pPlayer)
	{
		if (m_pCollisionModel && pPlayer->GetCollisionPtr())
		{
			if (CCollision::ColOBBs(m_pCollisionModel->GetOBB(), pPlayer->GetCollisionPtr()->GetOBB()))
			{
				// ���n�̏���
				pPlayer->Landing(pPlayer->GetPos().y);
			}
			else
			{
                // ���n����
				pPlayer->SetLanding(false);
			}
		}
	}
}