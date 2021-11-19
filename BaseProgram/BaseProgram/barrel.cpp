//=============================================================================
//
// �M�N���X [barrel.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "barrel.h"
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
#define TEST_POS    (D3DXVECTOR3(-10040.0f, 1014.8f, -15282.6f))
#define TEST_ROT    (D3DXVECTOR3(0.0f, D3DXToRadian(-25.0f), 0.0f))
#define ROTATE_NUM  (D3DXToRadian(-2.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBarrel::CBarrel(PRIORITY Priority) : CModel(Priority)
{
    m_fRotateNum = ROTATE_NUM;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBarrel::~CBarrel()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBarrel * CBarrel::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // �������m��
    CBarrel *pTestModel = new CBarrel(PRIORITY_TEST_MODEL);

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
HRESULT CBarrel::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CYLINDER);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CBarrel::Update()
{
    // ��]
    Rotate();

    CModel::Update();
}

//=============================================================================
// ��]
//=============================================================================
void CBarrel::Rotate()
{
    D3DXVECTOR3 rot = GetModelInfo()->GetRot();
    rot.z += m_fRotateNum;
    CLibrary::RotFix(rot.z);
    GetModelInfo()->SetRot(rot);
}