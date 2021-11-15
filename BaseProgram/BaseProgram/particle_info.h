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

	virtual HRESULT Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Draw(void) = 0;

	// get関数
	D3DXVECTOR3 GetMove(void) { return m_move; }
	int GetLife(void) { return m_nLife; }
	// set関数
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetLife(int life) { m_nLife = life; }
	void SetGravity(bool set) { m_bGravitySet = set; }

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