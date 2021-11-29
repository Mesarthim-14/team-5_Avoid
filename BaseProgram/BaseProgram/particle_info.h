#ifndef _PARTICLE_INFO_H_
#define _PARTICLE_INFO_H_
//=====================================================================
//
//    パーティクル基礎処理[particle_info.h]
//    Author : toshiki
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
    inline D3DXVECTOR3 GetMove()const  { return m_move; }
    inline int GetLife()const          { return m_nLife; }
    // set関数
    inline void SetMove(const D3DXVECTOR3 &move)    { m_move = move; }
    inline void SetLife(const int &life)            { m_nLife = life; }
    inline void SetGravity(const bool &set)         { m_bGravitySet = set; }
    inline void SetLife(const bool &set)            { m_LifeSet = set; }

private:
    void Gravity();
    void Erase();
    //==================
    // メンバ変数
    //==================
    D3DXVECTOR3 m_move;         // パーティクルの移動量
    int m_nLife;                // パーティクルのライフ
    bool m_bGravitySet;
    bool m_LifeSet;
};

#endif