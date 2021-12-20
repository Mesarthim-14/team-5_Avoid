#ifndef _PLANE_JUMPRESERVOIR_H_
#define _PLANE_JUMPRESERVOIR_H_
//=====================================================================
//
//    ジャンプエフェクト処理[plane_jump.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "plane.h"

//=====================================================================
// クラス定義
//=====================================================================
class CPlaneJumpReservoir : public CPlane
{
public:
    //==================
    // メンバ関数
    //==================
    CPlaneJumpReservoir();
    ~CPlaneJumpReservoir();

    static CPlaneJumpReservoir * Create(const D3DXVECTOR3 &pos);
    HRESULT Init();
    void Update();
    void Uninit();
    void Draw();

private:
    //==================
    // メンバ変数
    //==================
    D3DXVECTOR3 m_pos;      // 座標
    D3DXVECTOR3 m_move;     // 移動
    float m_fSize;          // 大きさ
    float m_fRot;           // 回転
    float m_fColor;         // カラー
    int m_nCnt;             // カウント
    int m_nLife;            // ライフ
};

#endif