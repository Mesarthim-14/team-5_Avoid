#ifndef _PARTICLEAURA_H_
#define _PARTICLEAURA_H_
//=====================================================================
//
//    パーティクル処理[particleaura.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "particle_info.h"

//=====================================================================
// クラス定義
//=====================================================================
class CParticleAura : public CParticleInfo
{
public:
    //==================
    // メンバ関数
    //==================
    CParticleAura();
    ~CParticleAura();

    static CParticleAura * Create(const D3DXVECTOR3 &pos);
    HRESULT Init();
    void Update();
    void Uninit();
    void Draw();

private:
    void SetParticle();        // パーティクルを出す処理
    //==================
    // メンバ変数
    //==================
    static D3DXVECTOR3 m_pos;
    float m_fAngle;         // 角度
    float m_fSpeed;         // 速度
    int m_nLife;            // 体力 
};

#endif
