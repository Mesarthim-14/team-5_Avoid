//=============================================================================
//
// �N���X [swirl_scaffold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "swirl_scaffold.h"
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
#define TEST_ROT    (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))   // �p�x
#define ROTATE_NUM  (D3DXToRadian(1.0f))                            // ��]�̒l

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSwirlScaffold::CSwirlScaffold(PRIORITY Priority) : CModel(Priority)
{
    m_fRotateNum = ROTATE_NUM;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSwirlScaffold::~CSwirlScaffold()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CSwirlScaffold * CSwirlScaffold::Create(const D3DXVECTOR3 &pos)
{
    // �������m��
    CSwirlScaffold *pRotatebody = new CSwirlScaffold(PRIORITY_TEST_MODEL);

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
HRESULT CSwirlScaffold::Init(const D3DXVECTOR3 &pos)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_SWIRL_SCAFFOLD);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CSwirlScaffold::Update()
{
    // ��]������
    Rotate();

    CModel::Update();
}

//=============================================================================
// ��]
//=============================================================================
void CSwirlScaffold::Rotate()
{
    D3DXVECTOR3 rot = GetModelInfo()->GetRot();
    rot.y += m_fRotateNum;
    CLibrary::RotFix(rot.y);
    GetModelInfo()->SetRot(rot);
}