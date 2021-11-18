#ifndef _RUBBLE2_H_
#define _RUBBLE2_H_
//=============================================================================
//
// 瓦礫クラス [rubble2.h]
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
class CRubble2 : public CModel
{
public:
	CRubble2(PRIORITY = PRIORITY_TEST_MODEL);	// コンストラクタ
	~CRubble2();								// デストラクタ

	static CRubble2 *Create();	// インスタンス生成
	HRESULT Init();				// 初期化処理
	void Uninit();				// 初期化処理
	void Update();				// 更新処理
	void Draw();				// 描画

private:
};

#endif