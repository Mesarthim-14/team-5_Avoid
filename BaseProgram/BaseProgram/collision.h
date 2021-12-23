#ifndef _COLLISION_H_
#define _COLLISION_H_
//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "model.h"
#include "collisionModel_OBB.h"
#include "collisionModel_Capsule.h"
#include "collisionModel_Cylinder.h"
#include "collisionModel_Sphere.h"

//=============================================================================
// 当たり判定クラス
//=============================================================================
class CCollision
{
public:
    // 当たった面の列挙型
    enum SURFACE
    {
        SURFACE_NONE = -1,
        SURFACE_UP,         // 上面
        SURFACE_DOWN,       // 下面
        SURFACE_SIDE        // 側面
    };

    // 当たり判定(OBBとOBB)
    static bool ColOBBs(const CCollisionModelOBB::OBB &obb1, const CCollisionModelOBB::OBB &obb2);
    // 当たり判定(球体とOBB)
    static bool ColSphereAndOBB(const CCollisionModelSphere::SPHERE &SphereInfo, const CCollisionModelOBB::OBB &ObbInfo);
    // 当たり判定(球体とカプセル)
    static bool ColSphereAndCapsule(const CCollisionModelSphere::SPHERE &SphereInfo, const CCollisionModelCapsule::INFO &CapsuleInfo);
    // 当たり判定(球体と円柱)
    static void ColSphereAndCylinder(bool &bHit, SURFACE &surface, const CCollisionModelSphere::SPHERE &SphereInfo, const CCollisionModelCylinder::CYLINDER &CylinderInfo);
    // 当たり判定(矩形と矩形)
    static bool ColRectangleAndRectangle(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &size2);
    // 当たり判定(円形と円形)
    static bool ColCircularAndCircular(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2, const float &radius1, const float &radius2);
    // 当たり判定(矩形と円形)
    static bool ColRectangleAndCircular(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &CircularPos, const D3DXVECTOR3 &RectangleSize, const float &CircularRadius, const float &RectangleRadian);
    // プレイヤーの壁ずりベクトル計算
    static D3DXVECTOR3 SlideVect(const D3DXVECTOR3 &playerMove, const D3DXVECTOR3 &norVec);
};

#endif