//=============================================================================CMoveScaffold
//
// 動く足場クラス [move_scaffold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "move_scaffold.h"
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
#define TEST_POS		(D3DXVECTOR3(-30637.0f, 0.0f, 8337.8f))
#define TEST_ROT		(D3DXVECTOR3(0.0f, D3DXToRadian(135.0f), 0.0f))
#define TURN_TIME		(800.0f)	// 反転までのカウント
#define SPEED			(8.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CMoveScaffold::CMoveScaffold(PRIORITY Priority) : CModel(Priority)
{
	m_nTime = 0;
	m_fSpeed = SPEED;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMoveScaffold::~CMoveScaffold()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CMoveScaffold * CMoveScaffold::Create()
{
	// メモリ確保
	CMoveScaffold *pTestModel = new CMoveScaffold(PRIORITY_TEST_MODEL);

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
HRESULT CMoveScaffold::Init()
{
	// 初期化処理
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MOVE_SCAFFOLD);
	GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMoveScaffold::Uninit()
{
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMoveScaffold::Update()
{
	// 移動処理
	Move();

	CModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMoveScaffold::Draw()
{
	CModel::Draw();
}

//=============================================================================
// 移動処理
//=============================================================================
void CMoveScaffold::Move()
{
	m_nTime++;
	
	float fAngle = GetModelInfo()->GetRot().y;

	// 移動量設定
	D3DXVECTOR3 move = D3DXVECTOR3(
		cosf(D3DXToRadian(fAngle+45.0f))*m_fSpeed, 
		0.0f, sinf(D3DXToRadian(fAngle + 45.0f))*m_fSpeed);

	// 移動量設定
	SetMove(move);

	// 一定時間で
	if (m_nTime >= TURN_TIME)
	{
		m_nTime = 0;
		m_fSpeed *= -1;
	}
}