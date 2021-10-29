//=============================================================================CTestModel
//
// テストモデルクラス [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "test_model.h"
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
CTestModel::CTestModel(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTestModel::~CTestModel()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTestModel * CTestModel::Create(void)
{
	// メモリ確保
	CTestModel *pTestModel = new CTestModel(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pTestModel)
	{
		// 初期化処理
		pTestModel->Init();

		return pTestModel;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTestModel::Init(void)
{
	//SetScale(D3DXVECTOR3(100.0f, 100.0f, 100.0f));
	// 初期化処理
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	//BindModel(pXfile->GetXfile(CXfile::XFILE_NUM_TEST_BLOCK));
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP);
	GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTestModel::Uninit(void)
{
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTestModel::Update(void)
{
	CModel::Update();

	// 衝突判定
	Hit();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTestModel::Draw(void)
{
	CModel::Draw();
}

//=============================================================================
// 衝突判定
//=============================================================================
void CTestModel::Hit(void)
{
	CPlayer* pPlayer = nullptr;
	pPlayer = (CPlayer*)GetTop(PRIORITY_CHARACTER);

	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 RayDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		BOOL bHit = FALSE;
		FLOAT fDistance = 0.0f;

		for (int nCount = 0; nCount < (int)GetModelInfo()->GetMesh()->GetNumFaces(); nCount++)
		{
			//下方向
			D3DXIntersect(
				GetModelInfo()->GetMesh(),
				&pPlayer->GetPos(),
				&RayDir,
				&bHit,
				nullptr,
				nullptr,
				nullptr,
				&fDistance,
				nullptr,
				nullptr);

			if (bHit && fDistance < 80.0f)
			{
				// 着地の処理
				pPlayer->Landing(pPlayer->GetPos().y + fDistance);

				break;
			}
			else if (!bHit)
			{
				pPlayer->SetLanding(false);
			}
		}
	}
}