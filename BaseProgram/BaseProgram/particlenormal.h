#ifndef _PARTICLENORMAL_H_
#define _PARTICLENORMAL_H_
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
class CParticleNormal : public CParticleInfo
{
public:
    //==================
    // メンバ関数
    //==================
    CParticleNormal();
    ~CParticleNormal();

    static CParticleNormal * Create(void);
    HRESULT Init(void);
    void Update(void);
    void Uninit(void);
    void Draw(void);

private:
    void SetParticle(void);     // パーティクルを出す処理
    //==================
    // メンバ変数
    //==================
    float m_fAngle;             // 角度
    float m_fSpeed;             // 速度
    int m_nLife;                // 体力
};

#endif