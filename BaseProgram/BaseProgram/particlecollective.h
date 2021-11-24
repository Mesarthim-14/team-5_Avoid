#ifndef _PARTICLECOLLECTIVE_H_
#define _PARTICLECOLLECTIVE_H_
//=====================================================================
//
//  集合パーティクル処理[particlefire.h]
//  Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "particle_info.h"

//=====================================================================
// クラス定義
//=====================================================================
class CParticleCollective : public CParticleInfo
{
public:
    //==================
    // メンバ関数
    //==================
    CParticleCollective();
    ~CParticleCollective();

    static CParticleCollective * Create(const D3DXVECTOR3 &pos);
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