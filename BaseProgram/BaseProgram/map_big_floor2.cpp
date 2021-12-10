//=============================================================================
//
// �傫���I�u�W�F�N�g [map_big_floor2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "map_big_floor2.h"
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
CMapBigFloor2::CMapBigFloor2(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapBigFloor2::~CMapBigFloor2()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMapBigFloor2 * CMapBigFloor2::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CMapBigFloor2 *pModel = new CMapBigFloor2(PRIORITY_TEST_MODEL);

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
HRESULT CMapBigFloor2::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_FIRST_FLOOR2);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMapBigFloor2::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMapBigFloor2::Update()
{
    CModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMapBigFloor2::Draw()
{
    CModel::Draw();
}