//=============================================================================CCheckFlag
//
// チェックポイントクラス [check_flag.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "check_flag.h"
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
// マクロ定義
//=============================================================================
#define TEST_ROT		(ZeroVector3)
#define CHECK_DISTANCE	(2000.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CCheckFlag::CCheckFlag(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CCheckFlag::~CCheckFlag()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CCheckFlag * CCheckFlag::Create(const D3DXVECTOR3 &pos)
{
	// メモリ確保
	CCheckFlag *pTestModel = new CCheckFlag(PRIORITY_GIMMICK);

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
HRESULT CCheckFlag::Init(const D3DXVECTOR3 &pos)
{
	// 初期化処理
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CHECK_FLAG);
	GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

	return S_OK;
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CCheckFlag::Collision()
{
	return PlayerDisCollision(CHECK_DISTANCE);
}

//=============================================================================
// 座標の取得
//=============================================================================
D3DXVECTOR3 CCheckFlag::GetPos()
{
	return GetModelInfo()->GetPos(); 
}
