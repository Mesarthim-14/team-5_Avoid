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

    static CParticleNormal * Create(const D3DXVECTOR3 &pos);
    HRESULT Init(void);
    void Update(void);
    void Uninit(void);
    void Draw(void);

private:
    void SetParticle(void);     // パーティクルを出す処理
    void SetParticleColor(void);        // パーティクルを徐々に消す処理
    void SetEffect(void);
    //==================
    // メンバ変数
    //==================
    static D3DXVECTOR3 m_Rot;   // 方向
    float m_fColor;             // 透明度
    float m_fAngle;             // 角度
    float m_fSpeed;             // 速度
    int m_nLife;                // 体力
    int m_nCnt;
};

#endif