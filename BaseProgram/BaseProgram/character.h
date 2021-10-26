#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// キャラクタークラスヘッダ  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CMotion;

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CCharacter : public CScene
{
public:

	//=============================================================================
	// キャラクターの状態
	//=============================================================================
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_DEAD,
		STATE_JUMP,
		STATE_MAX
	};

	//=============================================================================
	// キャラクターの種類
	//=============================================================================
	enum CHARACTER_TYPE
	{
		CHARACTER_TYPE_NONE = -1,	// 初期値
		CHARACTER_TYPE_PLAYER,		// プレイヤー
		CHARACTER_TYPE_MAX			// 最大値
	};

	CCharacter(PRIORITY Priority = PRIORITY_CHARACTER);				// コンストラクタ
	virtual ~CCharacter();											// デストラクタ

	virtual HRESULT Init(void);										// 初期化処理
	virtual void Uninit(void);										// 終了処理
	virtual void Update(void);										// 更新処理
	virtual void Draw(void);										// 描画処理

	// Get関数
	D3DXVECTOR3 GetPos(void)const					{ return m_pos; }						// 現在の座標情報
	D3DXVECTOR3 GetOldPos(void)const				{ return m_posOld; }					// 古い座標情報
	D3DXVECTOR3 GetRot(void)const					{ return m_rot; }						// 角度情報
	D3DXVECTOR3 GetMove(void)const					{ return m_move; }						// 移動量の情報
	D3DXVECTOR3 GetSize(void)const					{ return m_size; }						// サイズ取得
	CModelAnime *GetModelAnime(const int nCount)	{ return m_apModelAnime.at(nCount); }	// モーションのカウント情報
	CMotion *GetMotion(void)						{ return m_pMotion; }					// モーションのポインタ情報
	int GetStateCounter(void)						{ return m_nStateCounter; }				// 状態カウンターの情報
	int GetPartsNum(void)							{ return m_apModelAnime.size(); }		// パーツ数取得
	float &GetSpeed(void)							{ return m_fSpeed; }					// スピードの情報
	STATE GetState(void)							{ return m_State; }						// 状態取得
	CHARACTER_TYPE GetType(void)					{ return m_type; }						// 種類

protected:
	void SetCharacterInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// キャラクターの基本情報
	void ModelCreate(const CXfile::HIERARCHY_XFILE_NUM &FileNum);			// モデルの生成
	void SetShadowRotCalculation(void);										// 影を回す

	// Set関数
	void SetPos(const D3DXVECTOR3 &pos)			{ m_pos = pos; }			// 座標の設定
	void SetPosOld(const D3DXVECTOR3 &posOld)	{ m_posOld = posOld; }		// 座標の設定
	void SetMove(const D3DXVECTOR3 &move)		{ m_move = move; }			// 移動量の設定
	void SetRot(const D3DXVECTOR3 &rot)			{ m_rot = rot; }			// 角度の設定
	void SetSize(const D3DXVECTOR3 &size)		{ m_size = size; }			// サイズ設定
	void SetSpeed(const float &fSpeed)			{ m_fSpeed = fSpeed; }		// 速度の設定
	void SetState(const STATE &state)			{ m_State = state; }		// 状態設定
	void SetLanding(const bool bLanding)		{ m_bLanding = bLanding; }	// 着地
	void SetGravityFlag(const bool bFlag)		{ m_bGravity = bFlag; }		// 重力のフラグ
	void SetType(const CHARACTER_TYPE &type)	{ m_type = type; }			// 種類
	void SetUseShadow(void)						{ m_bUseShadow = true; }	// 影の使用判定
	bool GetLanding(void)					    { return m_bLanding; }      // 着地判定取得
private:
	// private関数
	void ModelAnimeUpdate(void);				// モデルアニメーション
	void Gravity(void);							// 重力
	void Landing(const float fHeight);			// 着地
	void SetMotion(const int nMotionState);		// モーションの設定

	// 純粋仮想関数
	virtual void UpdateState(void) = 0;			// キャラクター状態
	virtual void Move(void) = 0;				// 移動関数

	// メンバ変数
	vector<CModelAnime*> m_apModelAnime;	// モデルパーツ用ポインタ
	CMotion *m_pMotion;						// モーションクラスのポインタ
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_posOld;					// 古い座標
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_rot;						// 現在の回転
	D3DXVECTOR3 m_size;						// サイズ
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	STATE m_State;							// 状態
	CHARACTER_TYPE m_type;					// 種類
	int m_nStateCounter;					// 状態のカウンター
	int m_nParts;							// パーツ数
	float m_fSpeed;							// 移動量
	bool m_bLanding;						// 着地フラグ
	bool m_bUseShadow;						// 影をつけるフラグ
	bool m_bGravity;						// 重力をかけるフラグ
};
#endif
