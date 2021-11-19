//=============================================================================CMarlinModel
//
// �J�W�L���f���N���X [marlin_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "marlin_model.h"
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
CMarlinModel::CMarlinModel(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMarlinModel::~CMarlinModel()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMarlinModel * CMarlinModel::Create(const D3DXVECTOR3 pos)
{
    // �������m��
    CMarlinModel *pMarlinModel = new CMarlinModel(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pMarlinModel)
    {
        // ����������
        pMarlinModel->Init(pos);
        return pMarlinModel;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMarlinModel::Init(const D3DXVECTOR3 &pos)
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
void CMarlinModel::Draw()
{
    CModel::Draw();
}

//=============================================================================
// ���W�ݒ�
//=============================================================================
void CMarlinModel::SetPos(const D3DXVECTOR3 &pos)
{
    GetModelInfo()->SetPos(pos);
}