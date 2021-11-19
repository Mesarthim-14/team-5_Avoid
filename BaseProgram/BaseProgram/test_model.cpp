//=============================================================================
//
// テストモデルクラス [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "test_model.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel.h"
#include "collision.h"

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
	m_pCollisionModel = nullptr;
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
CTestModel * CTestModel::Create()
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
HRESULT CTestModel::Init()
{
	// 初期化処理
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP);
	GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);

	//当たり判定モデルの生成
	if (m_pCollisionModel == nullptr)
	{
		m_pCollisionModel = CCollisionModel::Create(GetModelInfo()->GetPos(), D3DXVECTOR3(5000.0f, 100.0f, 4200.0f), TEST_ROT, CCollisionModel::TYPE_BOX);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTestModel::Uninit()
{
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTestModel::Update()
{
	CModel::Update();

	// 衝突判定
	Hit();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTestModel::Draw()
{
	CModel::Draw();
}

//=============================================================================
// 衝突判定
//=============================================================================
void CTestModel::Hit()
{
	CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();

	if (pPlayer)
	{
		if (m_pCollisionModel && pPlayer->GetCollisionPtr())
		{
			if (CCollision::ColOBBs(m_pCollisionModel->GetOBB(), pPlayer->GetCollisionPtr()->GetOBB()))
			{
				// 着地の処理
				pPlayer->Landing(pPlayer->GetPos().y);
			}
			else
			{
                // 着地処理
				pPlayer->SetLanding(false);
			}
		}
	}
}