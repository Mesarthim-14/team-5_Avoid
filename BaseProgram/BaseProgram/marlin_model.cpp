//=============================================================================CMarlinModel
//
// カジキモデルクラス [marlin_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define TEST_POS        (ZeroVector3)
#define TEST_ROT        (ZeroVector3)

//=============================================================================
// コンストラクタ
//=============================================================================
CMarlinModel::CMarlinModel(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CMarlinModel::~CMarlinModel()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CMarlinModel * CMarlinModel::Create(const D3DXVECTOR3 pos)
{
    // メモリ確保
    CMarlinModel *pMarlinModel = new CMarlinModel(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pMarlinModel)
    {
        // 初期化処理
        pMarlinModel->Init(pos);
        return pMarlinModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMarlinModel::Init(const D3DXVECTOR3 &pos)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ENEMY_MARLIN);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    return S_OK;
}

//=============================================================================
// 描画処理
//=============================================================================
void CMarlinModel::Draw()
{
    CModel::Draw();
}
