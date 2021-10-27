#ifndef _TEST_MODEL_H_
#define _TEST_MODEL_H_
//=============================================================================
//
// テストモデルクラス [test_model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"

//=========================================================================
// クラス定義
//=========================================================================
class CTestModel : public CModel
{
public:
	CTestModel(PRIORITY = PRIORITY_TEST_MODEL);	// コンストラクタ
	~CTestModel();								// デストラクタ

	static CTestModel *Create(void);	// インスタンス生成
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 初期化処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画

	CModelInfo* GetModelInfo(void) { return CModel::GetModelInfo(); }	// モデルの情報

private:
};

#endif