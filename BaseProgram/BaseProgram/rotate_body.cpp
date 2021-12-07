//=============================================================================
//
// ��]�{�̃N���X [rotate_body.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "rotate_body.h"
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
#define TEST_POS            (D3DXVECTOR3(-34328.4f, 200.0f, -6081.8f))
#define TEST_ROT            (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))
#define ROTATE_NUM          (D3DXToRadian(2.0f))                            // ��]�̒l

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRotateBody::CRotateBody(PRIORITY Priority) : CModel(Priority)
{
    m_fRotateNum = ROTATE_NUM;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRotateBody::~CRotateBody()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CRotateBody * CRotateBody::Create(const D3DXVECTOR3 &pos)
{
    // �������m��
    CRotateBody *pRotatebody = new CRotateBody(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pRotatebody)
    {
        // ����������
        pRotatebody->Init(pos);
        return pRotatebody;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRotateBody::Init(const D3DXVECTOR3 &pos)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ROTATE_BODY);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CRotateBody::Update()
{
    // ��]������
    Rotate();

    // �X�V����
    CModel::Update();
}

//=============================================================================
// ��]
//=============================================================================
void CRotateBody::Rotate()
{
    D3DXVECTOR3 rot = GetModelInfo()->GetRot();
    rot.y += m_fRotateNum;
    CLibrary::RotFix(rot.y);
    GetModelInfo()->SetRot(rot);
}