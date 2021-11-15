//=============================================================================CCheckFlag
//
// �`�F�b�N�|�C���g�N���X [check_flag.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "check_flag.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_ROT		(ZeroVector3)
#define CHECK_DISTANCE	(2000.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCheckFlag::CCheckFlag(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCheckFlag::~CCheckFlag()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCheckFlag * CCheckFlag::Create(const D3DXVECTOR3 &pos)
{
	// �������m��
	CCheckFlag *pTestModel = new CCheckFlag(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pTestModel)
	{
		// ����������
		pTestModel->Init(pos);

		return pTestModel;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCheckFlag::Init(const D3DXVECTOR3 &pos)
{
	// ����������
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CHECK_FLAG);
	GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

	return S_OK;
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CCheckFlag::Collision()
{
	return PlayerDisCollision(CHECK_DISTANCE);
}

//=============================================================================
// ���W�̎擾
//=============================================================================
D3DXVECTOR3 CCheckFlag::GetPos()
{
	return GetModelInfo()->GetPos(); 
}
