#ifndef _COLLISION_MODEL_SPHERE_H_
#define _COLLISION_MODEL_SPHERE_H_
//=============================================================================
//
// 当たり判定モデル(球体)の処理 [collisionModel_Sphere.h]
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
class CCollisionModelSphere :public CCollisionModel
{
public:
    CCollisionModelSphere(PRIORITY = PRIORITY_COLLISION); // コンストラクタ
    ~CCollisionModelSphere();                             // デストラクタ

    static CCollisionModelSphere *Create(const D3DXVECTOR3 &pos, const float &radius, const D3DXVECTOR3 &rot);    // 生成処理

    HRESULT Init(); // 初期化処理
    void Uninit();  // 終了処理
    void Update();  // 更新処理
    void Draw();    // 描画処理
};
#endif