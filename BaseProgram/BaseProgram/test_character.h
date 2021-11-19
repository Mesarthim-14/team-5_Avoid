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

	static CTestCharacter*Create(const D3DXVECTOR3 &pos);	// クリエイト

	HRESULT Init();					// 初期化処理
	void Uninit();					// 終了処理
	void Update();					// 更新処理
	void Draw();					// 描画処理
	void UpdateState();				// プレイヤーの状態
	void Move();					// 移動処理

private:
	HRESULT JsonLoad();	
	void JsonWrite();
	void CreateModel();

	D3DXVECTOR3 m_rotDest;							// 回転(目標値)
	bool m_bMove;									// 移動のフラグ
};
#endif