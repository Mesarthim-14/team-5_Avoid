//=============================================================================
//
// ���N���X [bridge.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "bridge.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBridge::CBridge(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBridge::~CBridge()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBridge * CBridge::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	// �������m��
	CBridge *pTestModel = new CBridge(PRIORITY_TEST_MODEL);

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
HRESULT CBridge::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	// ����������
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_BRIDGE);
	GetModelInfo()->SetModelStatus(pos, rot, model);

	return S_OK;
}