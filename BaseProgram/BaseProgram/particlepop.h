#ifndef _PARTICLEPOP_H_
#define _PARTICLEPOP_H_
//=====================================================================
//
//	パーティクル処理[particlepop.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "particle_info.h"

//=====================================================================
// クラス定義
//=====================================================================
class CParticlePop : public CParticleInfo
{
public:
	//==================
	// メンバ関数
	//==================
	CParticlePop();
	~CParticlePop();

	static CParticlePop * Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

private:
	void SetParticle(void);		// パーティクルを出す処理
	//==================
	// メンバ変数
	//==================
	float m_fAngle;				// 角度
	float m_fSpeed;				// 速度
	int m_nLife;				// 体力
	static float m_fSize;
};

#endif