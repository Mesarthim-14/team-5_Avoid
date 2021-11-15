//=============================================================================
//
// 樽クラス [barrel.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "barrel.h"
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
#define TEST_POS		(D3DXVECTOR3(-10040.0f, 1014.8f, -15282.6f))
#define TEST_ROT		(D3DXVECTOR3(0.0f, D3DXToRadian(-25.0f), 0.0f))
#define ROTATE_NUM		(D3DXToRadian(-2.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CBarrel::CBarrel(PRIORITY Priority) : CModel(Priority)
{
	m_fRotateNum = ROTATE_NUM;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBarrel::~CBarrel()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CBarrel * CBarrel::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	// メモリ確保
	CBarrel *pTestModel = new CBarrel(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pTestModel)
	{
		// 初期化処理
		pTestModel->Init(pos, rot);
		return pTestModel;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBarrel::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	// 初期化処理
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CYLINDER);
	GetModelInfo()->SetModelStatus(pos, rot, model);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CBarrel::Update(void)
{
	// 回転
	Rotate();

	CModel::Update();
}

//=============================================================================
// 回転
//=============================================================================
void CBarrel::Rotate()
{
	D3DXVECTOR3 rot = GetModelInfo()->GetRot();
	rot.z += m_fRotateNum;
	CLibrary::RotFix(rot.z);
	GetModelInfo()->SetRot(rot);
}