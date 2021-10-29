//=============================================================================CTestModel
//
// �e�X�g���f���N���X [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "test_model.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"

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
CTestModel * CTestModel::Create(void)
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
HRESULT CTestModel::Init(void)
{
	//SetScale(D3DXVECTOR3(100.0f, 100.0f, 100.0f));
	// ����������
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	//BindModel(pXfile->GetXfile(CXfile::XFILE_NUM_TEST_BLOCK));
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP);
	GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTestModel::Uninit(void)
{
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTestModel::Update(void)
{
	CModel::Update();

	// �Փ˔���
	Hit();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTestModel::Draw(void)
{
	CModel::Draw();
}

//=============================================================================
// �Փ˔���
//=============================================================================
void CTestModel::Hit(void)
{
	CPlayer* pPlayer = nullptr;
	pPlayer = (CPlayer*)GetTop(PRIORITY_CHARACTER);

	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 RayDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		BOOL bHit = FALSE;
		FLOAT fDistance = 0.0f;

		for (int nCount = 0; nCount < (int)GetModelInfo()->GetMesh()->GetNumFaces(); nCount++)
		{
			//������
			D3DXIntersect(
				GetModelInfo()->GetMesh(),
				&pPlayer->GetPos(),
				&RayDir,
				&bHit,
				nullptr,
				nullptr,
				nullptr,
				&fDistance,
				nullptr,
				nullptr);

			if (bHit && fDistance < 80.0f)
			{
				// ���n�̏���
				pPlayer->Landing(pPlayer->GetPos().y + fDistance);

				break;
			}
			else if (!bHit)
			{
				pPlayer->SetLanding(false);
			}
		}
	}
}