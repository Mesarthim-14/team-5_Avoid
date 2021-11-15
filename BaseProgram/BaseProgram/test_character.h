#ifndef _TEST_CHARACTER_H_
#define _TEST_CHARACTER_H_
//=============================================================================
//
// テストキャラクタークラスヘッダー [test_character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "modelanime.h"
#include "json.h"

//=============================================================================
// プレイヤークラス
//=============================================================================
class CTestCharacter : public CCharacter
{
public:
	CTestCharacter(PRIORITY Priority = PRIORITY_CHARACTER);	// コンストラクタ
	~CTestCharacter();										// デストラクタ

	static CTestCharacter*Create(D3DXVECTOR3 pos);	// クリエイト

	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理
	void UpdateState(void);				// プレイヤーの状態
	void Move(void);					// 移動処理

private:
	HRESULT JsonLoad(void);	
	void JsonWrite(void);
	void CreateModel();

	D3DXVECTOR3 m_rotDest;							// 回転(目標値)
	bool m_bMove;									// 移動のフラグ
};
#endif