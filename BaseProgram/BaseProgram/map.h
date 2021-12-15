#ifndef _MAP_H_
#define _MAP_H_
//=============================================================================
//
// マップ親クラス [map.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"
#include "collisionModel_OBB.h"
#include "collisionModel_Sphere.h"
#include "collisionModel_Cylinder.h"

//=========================================================================
// クラス定義
//=========================================================================
class CMap : public CModel
{
public:
    CMap(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CMap();                              // デストラクタ

    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);   // 初期化処理
    void Uninit()override;                                          // 初期化処理
    void Update()override;                                          // 更新処理
    void Draw()override;                                            // 描画

    // 当たり判定
    void HitColOBBs(CCollisionModelOBB** pMapColOBB);                         // マップの当たり判定関数(直方体同士)
    void HitColSphereAndCylinder(CCollisionModelCylinder* pMapColCylinder);   // マップの当たり判定関数(球体と円柱)

private:
    bool m_bHitOld; // １つ以上マップに当たっているかの判定
};

#endif