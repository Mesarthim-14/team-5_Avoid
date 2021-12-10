//=============================================================================
//
// �����`�̏��N���X [map_thin_floor2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "map_thin_floor2.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_OBB.h"
#include "collision.h"
#include "blur_filter.h"
#include "gauss_filter.h"
#include "library.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapThinFloor2::CMapThinFloor2(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapThinFloor2::~CMapThinFloor2()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMapThinFloor2 * CMapThinFloor2::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CMapThinFloor2 *pModel = new CMapThinFloor2(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pModel)
    {
        // ����������
        pModel->Init(pos, rot);

        return pModel;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMapThinFloor2::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_THIN_FLOOR2);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMapThinFloor2::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMapThinFloor2::Update()
{
    CModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMapThinFloor2::Draw()
{
    CModel::Draw();
}