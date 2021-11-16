//=============================================================================
//
// �񕜃|�C���g�N���X [check_flag.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "heel_point.h"
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
#define CHECK_DISTANCE	(1000.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHeelPoint::CHeelPoint(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CHeelPoint::~CHeelPoint()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CHeelPoint * CHeelPoint::Create(const D3DXVECTOR3 &pos)
{
	// �������m��
	CHeelPoint *pTestModel = new CHeelPoint(PRIORITY_TEST_MODEL);

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
HRESULT CHeelPoint::Init(const D3DXVECTOR3 &pos)
{
	// ����������
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_RECOVER);
	GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

	return S_OK;
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CHeelPoint::Collision()
{
	return PlayerDisCollision(CHECK_DISTANCE);
}

//=============================================================================
// ���W�̎擾
//=============================================================================
D3DXVECTOR3 CHeelPoint::GetPos()
{
	return GetModelInfo()->GetPos();
}