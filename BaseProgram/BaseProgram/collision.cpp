//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "model.h"
#include "collision.h"
#include "library.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBB_INTERVAL (50000.0f)    // OBB同士の当たり判定を行う範囲

//*****************************************************************************
// 当たり判定(OBBとOBB)
//*****************************************************************************
bool CCollision::ColOBBs(const CCollisionModelOBB::OBB &obb1, const CCollisionModelOBB::OBB &obb2)
{
    // 当たり判定モデル同士の距離
    D3DXVECTOR3 Interval = obb1.info.pos - obb2.info.pos;
    if (D3DXVec3Length(&Interval) > (FLOAT)OBB_INTERVAL)
    { // OBB_INTERVALより離れているとき、当たり判定を行わない
        return false;
    }

    // 各方向ベクトルの確保
    D3DXVECTOR3 Ae1 = obb1.DirVect[0];
    D3DXVECTOR3 Ae2 = obb1.DirVect[1];
    D3DXVECTOR3 Ae3 = obb1.DirVect[2];
    D3DXVECTOR3 Be1 = obb2.DirVect[0];
    D3DXVECTOR3 Be2 = obb2.DirVect[1];
    D3DXVECTOR3 Be3 = obb2.DirVect[2];

    // 正規化した各方向ベクトルの確保
    D3DXVECTOR3 NAe1; D3DXVec3Normalize(&NAe1, &Ae1);
    D3DXVECTOR3 NAe2; D3DXVec3Normalize(&NAe2, &Ae2);
    D3DXVECTOR3 NAe3; D3DXVec3Normalize(&NAe3, &Ae3);
    D3DXVECTOR3 NBe1; D3DXVec3Normalize(&NBe1, &Be1);
    D3DXVECTOR3 NBe2; D3DXVec3Normalize(&NBe2, &Be2);
    D3DXVECTOR3 NBe3; D3DXVec3Normalize(&NBe3, &Be3);

    // 分離軸 : Ae1
    FLOAT rA = D3DXVec3Length(&Ae1);
    FLOAT rB = CLibrary::LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    FLOAT L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NAe1));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : Ae2
    rA = D3DXVec3Length(&Ae2);
    rB = CLibrary::LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NAe2));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : Ae3
    rA = D3DXVec3Length(&Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NAe3));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : Be1
    rA = CLibrary::LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB = D3DXVec3Length(&Be1);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NBe1));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : Be2
    rA = CLibrary::LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB = D3DXVec3Length(&Be2);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NBe2));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : Be3
    rA = CLibrary::LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    rB = D3DXVec3Length(&Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NBe3));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : C11
    D3DXVECTOR3 Cross;
    D3DXVec3Cross(&Cross, &NAe1, &NBe1);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : C12
    D3DXVec3Cross(&Cross, &NAe1, &NBe2);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : C13
    D3DXVec3Cross(&Cross, &NAe1, &NBe3);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : C21
    D3DXVec3Cross(&Cross, &NAe2, &NBe1);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : C22
    D3DXVec3Cross(&Cross, &NAe2, &NBe2);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : C23
    D3DXVec3Cross(&Cross, &NAe2, &NBe3);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : C31
    D3DXVec3Cross(&Cross, &NAe3, &NBe1);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : C32
    D3DXVec3Cross(&Cross, &NAe3, &NBe2);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離軸 : C33
    D3DXVec3Cross(&Cross, &NAe3, &NBe3);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // 分離平面が存在しないので「衝突している」
    return true;
}

//=============================================================================
// 当たり判定(球体とカプセル)
//=============================================================================
bool CCollision::ColSphereAndCapsule(const CCollisionModelSphere::SPHERE &SphereInfo, const CCollisionModelCapsule::INFO &CapsuleInfo)
{
    // 当たり判定モデル同士の距離
    D3DXVECTOR3 Interval = SphereInfo.info.pos - CapsuleInfo.pos;
    if (D3DXVec3Length(&Interval) > (FLOAT)OBB_INTERVAL)
    { // OBB_INTERVALより離れているとき、当たり判定を行わない
        return false;
    }

    D3DXVECTOR3 V1 = ZeroVector3;       // カプセル線分のベクトル
    D3DXVECTOR3 V2 = ZeroVector3;       // カプセル線分の始点から球体の中心までのベクトル
    D3DXVECTOR3 norV1 = ZeroVector3;    // V1の単位ベクトル
    FLOAT fDot = 0.0f;                  // 2つのベクトルの内積
    D3DXVECTOR3 ret = ZeroVector3;      // 線分上最近点

    // カプセル線分のベクトルを計算
    V1 = CapsuleInfo.P1 - CapsuleInfo.P0;

    // 単位ベクトルを計算
    D3DXVec3Normalize(&norV1, &V1);

    // カプセル線分の始点から球体の中心までのベクトルの計算
    V2 = SphereInfo.info.pos - CapsuleInfo.P0;

    // 2つのベクトルの内積を計算
    fDot = D3DXVec3Dot(&norV1, &V2);

    // 線分上最近点を計算
    ret = CapsuleInfo.P0 + D3DXVECTOR3(norV1.x * fDot, norV1.y * fDot, norV1.z * fDot);

    // 「線分上最近点と球体の中心との距離」が球体の半径とカプセルの半径を足した値より小さいとき
    if (D3DXVec3Length(&(SphereInfo.info.pos - ret)) <= SphereInfo.radius + CapsuleInfo.radius)
    {
        FLOAT ratio = 0.0f; // 線分を0～1の範囲で表したときの線分上最近点の位置

        // 線分を0～1の範囲で表したときの線分上最近点の位置を計算
        ratio = D3DXVec3Dot(&norV1, &(ret - CapsuleInfo.P0)) / D3DXVec3Dot(&norV1, &V1);

        if (ratio >= 0.0f && ratio <= 1.0f)
        { // ratioが0以上1以下のとき
            // 「線分上最近点と球体の中心との距離」がカプセルと球体の半径を足した値より小さいとき
            if (D3DXVec3Length(&(SphereInfo.info.pos - ret)) <= SphereInfo.radius + CapsuleInfo.radius)
            {
                return true;
            }
        }
        else if (ratio > 1.0f)
        { // ratioが1より大きいとき
            // 「カプセル線分の終点から球体の中心までのベクトルの長さ」が球体の半径より小さいとき
            if (D3DXVec3Length(&(SphereInfo.info.pos - CapsuleInfo.P1)) <= SphereInfo.radius)
            {
                return true;
            }
        }
        else if (ratio < 0.0f)
        { // ratioが0より小さいとき
            // V2の長さがカプセルと球体の半径より小さいとき
            if (D3DXVec3Length(&(ret - CapsuleInfo.P0)) <= SphereInfo.radius)
            {
                return true;
            }
        }
    }

    return false;
}

//=============================================================================
// 当たり判定(球体と円柱)
//=============================================================================
void CCollision::ColSphereAndCylinder(bool &bHit, SURFACE &surface, const CCollisionModelSphere::SPHERE &SphereInfo, const CCollisionModelCylinder::CYLINDER &CylinderInfo)
{
    // 当たり判定モデル同士の距離
    D3DXVECTOR3 Interval = SphereInfo.info.pos - CylinderInfo.info.pos;
    if (D3DXVec3Length(&Interval) > (FLOAT)OBB_INTERVAL)
    { // OBB_INTERVALより離れているとき、当たり判定を行わない
        bHit = false;
        return;
    }

    D3DXVECTOR3 P0 = ZeroVector3;       // 線分の始点
    D3DXVECTOR3 P1 = ZeroVector3;       // 線分の終点
    D3DXVECTOR3 V1 = ZeroVector3;       // 円柱線分のベクトル
    D3DXVECTOR3 V2 = ZeroVector3;       // 円柱線分の始点から球体の中心までのベクトル
    D3DXVECTOR3 norV1 = ZeroVector3;    // V1の単位ベクトル
    FLOAT fDot = 0.0f;                  // 2つのベクトルの内積

    // 円柱線分の始点座標を計算
    P0 = D3DXVECTOR3(CylinderInfo.info.pos.x, CylinderInfo.info.pos.y + (CylinderInfo.length / 2), CylinderInfo.info.pos.z);
    //CLibrary::Rotate3D(P0, CylinderInfo.rot);

    // 円柱線分の終点座標を計算
    P1 = D3DXVECTOR3(CylinderInfo.info.pos.x, CylinderInfo.info.pos.y - (CylinderInfo.length / 2), CylinderInfo.info.pos.z);
    //CLibrary::Rotate3D(P1, CylinderInfo.rot);

    // 円柱線分のベクトルを計算
    V1 = P1 - P0;

    // 単位ベクトルを計算
    D3DXVec3Normalize(&norV1, &V1);

    // 円柱線分の始点から球体の中心までのベクトルの計算
    V2 = SphereInfo.info.pos - P0;

    // 2つのベクトルの内積を計算
    fDot = D3DXVec3Dot(&norV1, &V2);

    D3DXVECTOR3 ret = ZeroVector3;  // 線分上最近点
    FLOAT ratio = 0.0f;             // 線分を0～1の範囲で表したときの線分上最近点の位置

    // 線分上最近点を計算
     ret = P0 + D3DXVECTOR3(norV1.x * fDot, norV1.y * fDot, norV1.z * fDot);

    // 「線分上最近点と球体の中心との距離」が円柱と球体の半径を足した値より小さいとき
    if (D3DXVec3Length(&(SphereInfo.info.pos - ret)) <= SphereInfo.radius + CylinderInfo.radius)
    {
        // 線分を0～1の範囲で表したときの線分上最近点の位置を計算
        ratio = D3DXVec3Dot(&norV1, &(ret - P0)) / D3DXVec3Dot(&norV1, &V1);

        if (ratio >= 0.0f && ratio <= 1.0f)
        { // ratioが0以上1以下のとき
            surface = SURFACE::SURFACE_SIDE;
            bHit = true;
            return;
        }

        // 「円柱線分の中心から線分上最近点までの長さ」が「円柱線分の半分の長さ + 球体の半径」より小さいとき
        if (D3DXVec3Length(&(ret - CylinderInfo.info.pos)) <= (CylinderInfo.length / 2) + SphereInfo.radius)
        {
            if (ratio < 0.0f)
            { // ratioが0より小さいとき
                surface = SURFACE::SURFACE_UP;
                bHit = true;
                return;
            }
            else if (ratio > 1.0f)
            { // ratioが1より大きいとき
                surface = SURFACE::SURFACE_DOWN;
                bHit = true;
                return;
            }
        }
    }
    
    bHit = false;
    return;
}

//=============================================================================
// 当たり判定(矩形と矩形)
//=============================================================================
bool CCollision::ColRectangleAndRectangle(const D3DXVECTOR3 &pos1,
    const D3DXVECTOR3 &pos2, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &size2)
{
    bool bCollision = false;

    if (pos2.x - (size2.x / 2) < pos1.x + (size1.x / 2) &&
        pos2.x + (size2.x / 2) > pos1.x - (size1.x / 2) &&
        pos2.y - (size2.y / 2) < pos1.y + (size1.y / 2) &&
        pos2.y + (size2.y / 2) > pos1.y - (size1.y / 2)    &&
        pos2.z - (size2.z / 2) < pos1.z + (size1.z / 2) &&
        pos2.z + (size2.z / 2) > pos1.z - (size1.z / 2))
    {
        bCollision = true;
    }

    return bCollision;
}

//=============================================================================
// 当たり判定(円形と円形)
//=============================================================================
bool CCollision::ColCircularAndCircular(const D3DXVECTOR3 &pos1,
    const D3DXVECTOR3 &pos2, const float &radius1, const float &radius2)
{
    bool bCollision = false;

    if (pow(pos1.x - pos2.x, 2) +
        pow(pos1.y - pos2.y, 2) +
        pow(pos1.z - pos2.z, 2) <= pow(radius1 + radius2, 2))
    {
        bCollision = true;
    }

    return bCollision;
}

//=============================================================================
// 当たり判定(矩形と円形)
//=============================================================================
bool CCollision::ColRectangleAndCircular(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &CircularPos,
    const D3DXVECTOR3 &RectangleSize, const float &CircularRadius, const float &RectangleRadian)
{
    // 矩形の角度を０にした時の円形の座標を求める
    D3DXVECTOR3 NewCircularPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    NewCircularPos.x = (float)(cos(RectangleRadian) * (CircularPos.x - RectanglePos.x) -
        sin(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.x);
    NewCircularPos.y = (float)(sin(RectangleRadian) * (CircularPos.x - RectanglePos.x) +
        cos(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.y);

    if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2) - CircularRadius) ||
        NewCircularPos.x >(RectanglePos.x + (RectangleSize.x / 2) + CircularRadius) ||
        NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2) - CircularRadius) ||
        NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2) + CircularRadius))
    { // 「矩形の外枠 + 円の半径」の範囲に入っていないとき
        return false;
    }
    if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
        NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
        !(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
            + pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
            < pow(CircularRadius, 2)))
    { // 矩形の左上の判定
        return false;
    }
    if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
        NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
        !(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
            + pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
            < pow(CircularRadius, 2)))
    { // 矩形の右上の判定
        return false;
    }
    if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
        NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2)) &&
        !(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
            + pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
            < pow(CircularRadius, 2)))
    { // 矩形の左下の判定
        return false;
    }
    if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
        NewCircularPos.y > (RectanglePos.y + (RectangleSize.y / 2)) &&
        !(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
            + pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
            < pow(CircularRadius, 2)))
    { // 矩形の右下の判定
        return false;
    }

    return true;
}