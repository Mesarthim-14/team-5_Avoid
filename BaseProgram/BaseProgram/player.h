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
#include "skinmesh_model.h"

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
	void SubLife(int nDamage);	// ダメージ

private:
	// private関数
	void UpdateState(void);		// プレイヤーの状態
	void PlayerControl(void);	// プレイヤーの制御
	void Move(void);			// 移動処理
	void KeyBoardMove(void);	// 移動関数
	void UpdateRot(void);		// 角度の更新処理
	void ChangeModel(void);		// モデルチェンジ
	void Action(void);			// アクション
	void Jump(void);			// ジャンプ
	void Avoidance(void);		// 回避アクション
	void JumpProcess(void);		// ジャンプ中の処理
	void AnimationProcess(void); // アニメーション制御
	typedef enum
	{
		SLIME_LITTLESIZE = 0,
		SLIME_MIDDLESIZE,
		SLIME_LARGESIZE,
		SLIME_STATE_MAX
	}SLIME_STATE;//スライムの状態（大きさ）

	typedef enum
	{
		ACTION_NONE = 0,
		ACTION_JUMP,
		ACTION_AVOID,
		ACTION_STAN
	}ACTION_STATE;//行動状態

	// メンバ変数
	D3DXVECTOR3 m_rotDest;		// 回転(目標値)
	D3DXVECTOR3 m_Inertia;		// 慣性
	float m_fInertiaNum;		// 慣性の値
	float m_fRotationSpeed;		// 回転の速度
	bool m_bMove;				// 移動のフラグ
	int m_nHP;				    // スライムHP ~100まで（パーセント）
	SLIME_STATE	m_SlimeState;	// スライムの状態
	float m_fAngle;				// カメラ向きアングル
	float m_fAngleSpeed;		// 目標向きまで向かうスピード
	ACTION_STATE m_ActionState; // 行動状態
	float m_fJumpValue;			// ジャンプ量
	float m_fDushJumpValue;		// 移動ジャンプ時の横移動加算量
	float m_fAvoidValueY;		// 回避移動量（上方向）
	float m_fAvoidValueXZ;		// 回避移動量（横方向）
	int   m_nChargeJumpCount;   // ためジャンプカウント
	bool m_bIsReadyChargeJump;	// ためジャンプ準備完了か
	CSkinmeshModel * m_pSkinmeshModel[SLIME_STATE_MAX]; //スキンメッシュモデルポインタ
	float m_fJumpTimeCount;		// ジャンプ時間カウント
	bool m_fJumpCheck;			// ジャンプし始めたか
};
#endif