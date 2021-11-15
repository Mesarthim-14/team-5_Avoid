#ifndef _MOVE_SCAFFOLD_H_
#define _MOVE_SCAFFOLD_H_
//=============================================================================
//
// 動く足場クラス [move_scaffold.h]
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
class CMoveScaffold : public CModel
{
public:
	CMoveScaffold(PRIORITY = PRIORITY_TEST_MODEL);	// コンストラクタ
	~CMoveScaffold();								// デストラクタ

	static CMoveScaffold *Create(void);	// インスタンス生成
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 初期化処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画

private:
	// private関数
	void Move();	// 移動量

	int m_nTime;
	float m_fSpeed;	
};

#endif