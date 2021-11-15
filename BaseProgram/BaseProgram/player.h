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
#include "skinmesh_model.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPlayerState;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CCharacter
{
public:
	typedef enum
	{
		ACTION_NONE = -1,
		ACTION_IDOL,
		ACTION_JUMP,
		ACTION_LANDING,
		ACTION_WALK,
	//	ACTION_AVOID,
		ACTION_MAX
	}ACTION_STATE;//行動状態

	enum STATE_PLAYER
	{
		STATE_PLAYER_NONE = -1,		// 初期値
		STATE_PLAYER_IDOL,			// 通常状態
		STATE_PLAYER_JUMP,			// ジャンプ状態
		STATE_PLAYER_AVOID,			// 回避状態
		STATE_PLAYER_STUN,			// 気絶
		STATE_PLAYER_KNOCK_BACK,	// ノックバック
		STATE_PLAYER_MAX,			// 最大値
	};

	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);	// コンストラクタ
	~CPlayer();											// デストラクタ

	static CPlayer*Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// クリエイト

	HRESULT Init(void);								// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理
	void ShowInfo(void);							// 情報
	HRESULT LoadInfo(void);							// データロード
	void SaveInfo(void);							// データセーブ
	void SubLife(int nDamage);						// ダメージ
	CSkinmeshModel* GetCurrentSkinMeshPtr();		// 現在のスキンメッシュポインタ
	void ChangeState(CPlayerState* pPlayerState);	// 状態チェンジ

	// Set関数
	void SetAction(int nCount, int nMaxAction)			{ m_nMaxAction[nCount] = nMaxAction; }
	inline void SetMove(const D3DXVECTOR3 &move)		{ CCharacter::SetMove(move); }	// 移動量設定
	inline void SetRotDest(const D3DXVECTOR3& rotDest)	{ m_rotDest = rotDest; }		// 目的の角度
	inline void SetAngle(const float& fAngle)			{ m_fAngle = fAngle; }			// アングル

	// Get関数
	inline int GetLife()const				{ return m_nHP; }			// HPの情報
	inline float GetAngle()const			{ return m_fAngle; }		// アングル
	inline D3DXVECTOR3 GetRotDest()const	{ return m_rotDest; }		// 目的
	inline D3DXVECTOR3 GetInertia()const	{ return m_Inertia; }		// 慣性の情報
	inline float GetInertiaNum()const		{ return m_fInertiaNum; }	// 慣性の値

private:
	// private関数
	void UpdateState(void);			// プレイヤーの状態
	void PlayerControl(void);		// プレイヤーの制御
	void UpdateRot(void);			// 角度の更新処理
	void ChangeModel(void);			// モデルチェンジ
	void Action(void);				// アクション
	void Jump(void);				// ジャンプ
	void Avoidance(void);			// 回避アクション
	void ReSporn();					// リスポーン
	void CreateModel();				// モデル生成

	typedef enum
	{
		SLIME_LITTLESIZE = 0,
		SLIME_MIDDLESIZE,
		SLIME_LARGESIZE,
		SLIME_STATE_MAX
	}SLIME_STATE;//スライムの状態（大きさ）

	// メンバ変数
	D3DXVECTOR3 m_rotDest;								// 回転(目標値)
	D3DXVECTOR3 m_Inertia;								// 慣性
	float m_fInertiaNum;								// 慣性の値
	float m_fRotationSpeed;								// 回転の速度
	bool m_bMove;										// 移動のフラグ
	int m_nHP;											// スライムHP ~100まで（パーセント）
	SLIME_STATE	m_SlimeState;							// スライムの状態
	float m_fAngle;										// カメラ向きアングル
	float m_fAngleSpeed;								// 目標向きまで向かうスピード
	ACTION_STATE m_ActionState;							// 行動状態
	CSkinmeshModel *m_pSkinmeshModel[SLIME_STATE_MAX];	// スキンメッシュモデルポインタ
	int m_nMaxAction[SLIME_STATE_MAX];					// アクションの最大数

	CPlayerState* m_pCurrentState;						// 現在の状態ポインタ
	CPlayerState* m_pNextState;							// 次の状態ポインタ
};
#endif