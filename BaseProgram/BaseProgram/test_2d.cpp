//=============================================================================CTest2d
//
// テスト2Dクラス [test_2d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "test_2d.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS		(HALF_SCREEN_POS)
#define TEST_SIZE		(D3DXVECTOR3(300.0f, 300.0f, 0.0f))
#define SCROLL_SPEED	(1.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CTest2d::CTest2d(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTest2d::~CTest2d()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTest2d * CTest2d::Create(void)
{
	// メモリ確保
	CTest2d *pPolygon = new CTest2d(PRIORITY_UI);

	// !nullcheck
	if (pPolygon)
	{
		// 初期化処理
		pPolygon->Init();

		return pPolygon;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTest2d::Init(void)
{
	// 初期化処理
	SetSceneInfo(TEST_POS, TEST_SIZE);
	CScene2D::Init();

	CTexture *pTexture = GET_TEXTURE_PTR;
	INT_VERTEX_2D TexInfo = pTexture->GetSparateTexInfo(CTexture::SEPARATE_TEX_TEST);
	bool bLoop = pTexture->GetSparateTexLoop(CTexture::SEPARATE_TEX_TEST);
//	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
	BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_TEST));
	InitAnimation(TexInfo.x, TexInfo.y, bLoop);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTest2d::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTest2d::Update(void)
{
	CScene2D::Update();

	// 頂点の更新
//	SetVertex();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTest2d::Draw(void)
{
	CScene2D::Draw();
}
