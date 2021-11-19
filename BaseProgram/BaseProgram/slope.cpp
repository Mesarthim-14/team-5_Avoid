//=============================================================================
//
// �⓹�N���X [slope.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "slope.h"
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
#define TEST_POS        (D3DXVECTOR3(-10040.0f, 514.8f, -15282.6f))
#define TEST_ROT        (D3DXVECTOR3(0.0f, D3DXToRadian(-75.0f), 0.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSlope::CSlope(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSlope::~CSlope()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CSlope * CSlope::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // �������m��
    CSlope *pTestModel = new CSlope(PRIORITY_TEST_MODEL);

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
HRESULT CSlope::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_SLOPE);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    return S_OK;
}