//=============================================================================CSharkModel
//
// サメモデルクラス [shark_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "shark_model.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS        (ZeroVector3)
#define TEST_ROT        (ZeroVector3)

//=============================================================================
// コンストラクタ
//=============================================================================
CSharkModel::CSharkModel(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSharkModel::~CSharkModel()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CSharkModel * CSharkModel::Create(const D3DXVECTOR3 pos)
{
    // メモリ確保
    CSharkModel *pTestModel = new CSharkModel(PRIORITY_GIMMICK);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init(pos);
        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSharkModel::Init(const D3DXVECTOR3 &pos)
{
    // 初期化処理
    CModel::Init(CModelInfo::MODEL_TYPE_CHARACTER);

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ENEMY_SHARK);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CSharkModel::Update()
{
    CModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CSharkModel::Draw()
{
    CModel::Draw();
}