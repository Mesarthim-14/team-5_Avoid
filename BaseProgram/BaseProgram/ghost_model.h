#ifndef _GHOST_MODEL_H_
#define _GHOST_MODEL_H_
//=============================================================================
//
// 幽霊モデルクラス [ghost_model.h]
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
class CGhostModel : public CModel
{
public:
	CGhostModel(PRIORITY = PRIORITY_TEST_MODEL);	// コンストラクタ
	~CGhostModel();									// デストラクタ

	static CGhostModel *Create(const D3DXVECTOR3 pos);	// インスタンス生成
	HRESULT Init(const D3DXVECTOR3 &pos);				// 初期化処理
	void Draw(void);									// 描画

	void SetPos(const D3DXVECTOR3 &pos);
private:
};

#endif