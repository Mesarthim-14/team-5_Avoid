#ifndef _COLLISION_MODEL_CYLINDER_H_
#define _COLLISION_MODEL_CYLINDER_H_
//=============================================================================
//
// 当たり判定モデル(円柱)の処理 [collisionModel_Cylinder.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "collisionModel.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCollisionModelCylinder :public CCollisionModel
{
public:
    //円柱情報の構造体
    struct CYLINDER
    {
        INFO info;      // [位置/大きさ/角度]情報の構造体
        float radius;   // 半径
        float length;   // 長さ
    };

    CCollisionModelCylinder(PRIORITY Priority); // コンストラクタ
    ~CCollisionModelCylinder();                 // デストラクタ

    static CCollisionModelCylinder *Create(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot);    // 生成処理

    HRESULT Init(); // 初期化処理
    void Uninit();  // 終了処理
    void Update();  // 更新処理
    void Draw();    // 描画処理

    inline CYLINDER GetCylinder()const { return{ GetInfo(), m_radius, m_length }; }   // 円柱情報の取得

private:
    float m_radius;   // 半径
    float m_length;   // 長さ
};
#endif