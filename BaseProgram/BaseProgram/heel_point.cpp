//=============================================================================
//
// 回復ポイントクラス [check_flag.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "heel_point.h"
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
#define CHECK_DISTANCE	(1000.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CHeelPoint::CHeelPoint(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CHeelPoint::~CHeelPoint()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CHeelPoint * CHeelPoint::Create(const D3DXVECTOR3 &pos)
{
	// メモリ確保
	CHeelPoint *pTestModel = new CHeelPoint(PRIORITY_TEST_MODEL);

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
HRESULT CHeelPoint::Init(const D3DXVECTOR3 &pos)
{
	// 初期化処理
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_RECOVER);
	GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

	return S_OK;
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CHeelPoint::Collision()
{
	return PlayerDisCollision(CHECK_DISTANCE);
}

//=============================================================================
// 座標の取得
//=============================================================================
D3DXVECTOR3 CHeelPoint::GetPos()
{
	return GetModelInfo()->GetPos();
}
