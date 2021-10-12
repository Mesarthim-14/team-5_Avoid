#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "json.h"

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CCharacter
{
public:
	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);	// コンストラクタ
	~CPlayer();											// デストラクタ

	static CPlayer*Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// クリエイト

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理
	void ShowInfo(void);		// 情報
	HRESULT LoadInfo(void);		// データロード
	void SaveInfo(void);		// データセーブ

private:
	// private関数
	void UpdateState(void);		// プレイヤーの状態
	void PlayerControl(void);	// プレイヤーの制御
	void Move(void);			// 移動処理
	void KeyBoardMove(void);	// 移動関数
	void UpdateRot(void);		// 角度の更新処理

	// メンバ変数
	D3DXVECTOR3 m_rotDest;		// 回転(目標値)
	D3DXVECTOR3 m_Inertia;		// 慣性
	float m_fInertiaNum;		// 慣性の値
	float m_fRotationSpeed;		// 回転の速度
	bool m_bMove;				// 移動のフラグ
};
#endif