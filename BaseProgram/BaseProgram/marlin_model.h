#ifndef _MARLIN_MODEL_H_
#define _MARLIN_MODEL_H_
//=============================================================================
//
// カジキモデルクラス [marlin_model.h]
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
class CMarlinModel : public CModel
{
public:
	CMarlinModel(PRIORITY = PRIORITY_TEST_MODEL);	// コンストラクタ
	~CMarlinModel();									// デストラクタ

	static CMarlinModel *Create(const D3DXVECTOR3 pos);	// インスタンス生成
	HRESULT Init(const D3DXVECTOR3 &pos);				// 初期化処理
	void Draw();										// 描画

	void SetPos(const D3DXVECTOR3 &pos);
private:
};

#endif