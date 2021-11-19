//=============================================================================
//
// ��]���N���X [rotate_floor.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "rotate_floor.h"
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
#define TEST_POS		(D3DXVECTOR3(-34328.4f, 0.0f, -6081.8f))
#define TEST_ROT		(D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))
#define ROTATE_NUM		(D3DXToRadian(2.0f))							// ��]�̒l

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRotateFloor::CRotateFloor(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CRotateFloor * CRotateFloor::Create(const D3DXVECTOR3 &pos)
{
	// �������m��
	CRotateFloor *pTestModel = new CRotateFloor(PRIORITY_TEST_MODEL);

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
HRESULT CRotateFloor::Init(const D3DXVECTOR3 &pos)
{
	// ����������
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ROTATE_FLOOR);
	GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

	return S_OK;
}