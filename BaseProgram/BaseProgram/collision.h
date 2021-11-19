#ifndef _COLLISION_H_
#define _COLLISION_H_
//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : Suzuki Mahiro
//
//=============================================================================
//(^_-)-☆
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "model.h"
#include "collisionModel.h"

//=============================================================================
// 当たり判定クラス
//=============================================================================
class CCollision
{
public:
    // 当たった面
    enum SURFACE
    {
        SURFACE_DOWN = 1,
        SURFACE_UP,
        SURFACE_LEFT,
        SURFACE_RIGHT,
        SURFACE_PREVIOUS,
        SURFACE_BACK
    };

    //OBBとOBBの衝突判定
    static bool ColOBBs(const CCollisionModel::OBB &obb1, const CCollisionModel::OBB &obb2);
    //当たり判定(矩形と矩形)
    static bool CollisionRectangleAndRectangle(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &size2);
    //当たり判定(円形と円形)
    static bool CollisionCircularAndCircular(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2, const float &radius1, const float &radius2);
    //当たり判定(矩形と円形)
    static bool CollisionRectangleAndCircular(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &CircularPos, const D3DXVECTOR3 &RectangleSize, const float &CircularRadius, const float &RectangleRadian);
};

#endif