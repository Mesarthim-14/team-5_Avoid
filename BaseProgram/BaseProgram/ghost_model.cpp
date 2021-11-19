//=============================================================================CGhostModel
//
// �H�샂�f���N���X [ghost_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "ghost_model.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS        (ZeroVector3)
#define TEST_ROT        (ZeroVector3)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGhostModel::CGhostModel(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGhostModel::~CGhostModel()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CGhostModel * CGhostModel::Create(const D3DXVECTOR3 pos)
{
    // �������m��
    CGhostModel *pTestModel = new CGhostModel(PRIORITY_TEST_MODEL);

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
HRESULT CGhostModel::Init(const D3DXVECTOR3 &pos)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ENEMY_BOX);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    return S_OK;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGhostModel::Draw()
{
    CModel::Draw();
}

//=============================================================================
// ���W�ݒ�
//=============================================================================
void CGhostModel::SetPos(const D3DXVECTOR3 &pos)
{
    GetModelInfo()->SetPos(pos);
}