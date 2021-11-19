#ifndef _PARTICLE_INFO_H_
#define _PARTICLE_INFO_H_
//=====================================================================
//
//	パーティクル基礎処理[particle_info.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "billboard.h"

//=====================================================================
// クラス定義
//=====================================================================
class CParticleInfo : public CBillboard
{
public:
	//==================
	// メンバ関数
	//==================
	CParticleInfo();
	virtual ~CParticleInfo();

	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Uninit() = 0;
	virtual void Draw() = 0;

	// get関数
	D3DXVECTOR3 GetMove()const { return m_move; }
	int GetLife()const { return m_nLife; }
	// set関数
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }
	void SetLife(const int life) { m_nLife = life; }
	void SetGravity(const bool set) { m_bGravitySet = set; }

private:
	void Gravity(void);
	//==================
	// メンバ変数
	//==================
	D3DXVECTOR3 m_move;		// パーティクルの移動量
	int m_nLife;			// パーティクルのライフ
	bool m_bGravitySet;
};

#endif