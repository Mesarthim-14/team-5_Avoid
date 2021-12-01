#ifndef _PARTICLESHRINK_HEEL_H_
#define _PARTICLESHRINK_HEEL_H_
//=====================================================================
//
//	パーティクル処理[particlenormal.h]
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
class CParticleHeel : public CParticleInfo
{
public:
    //==================
    // メンバ関数
    //==================
    CParticleHeel();
    ~CParticleHeel();

    static CParticleHeel * Create(const D3DXVECTOR3 &pos);
    HRESULT Init(void);
    void Update(void);
    void Uninit(void);
    void Draw(void);

private:
    void SetParticle(void);		// パーティクルを出す処理
    //==================
    // メンバ変数
    //==================
    static float m_fAngleX;     // 角度
    static float m_fAngleZ;     // 角度
    static float m_fSize;       // 大きさ
    float m_fSpeed;             // 速度
    int m_nLife;                // 体力

    D3DXVECTOR3 ShrinkPos;
};

#endif