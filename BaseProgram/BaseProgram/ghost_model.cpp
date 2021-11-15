//=============================================================================CGhostModel
//
// 幽霊モデルクラス [ghost_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define TEST_POS		(ZeroVector3)
#define TEST_ROT		(ZeroVector3)

//=============================================================================
// コンストラクタ
//=============================================================================
CGhostModel::CGhostModel(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGhostModel::~CGhostModel()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CGhostModel * CGhostModel::Create(const D3DXVECTOR3 pos)
{
	// メモリ確保
	CGhostModel *pTestModel = new CGhostModel(PRIORITY_TEST_MODEL);

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
HRESULT CGhostModel::Init(const D3DXVECTOR3 &pos)
{
	// 初期化処理
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ENEMY_BOX);
	GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

	return S_OK;
}

//=============================================================================
// 描画処理
//=============================================================================
void CGhostModel::Draw(void)
{
	CModel::Draw();
}

//=============================================================================
// 座標設定
//=============================================================================
void CGhostModel::SetPos(const D3DXVECTOR3 &pos)
{
	GetModelInfo()->SetPos(pos);
}