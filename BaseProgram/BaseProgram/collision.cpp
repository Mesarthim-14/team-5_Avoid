//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"
#include "collision.h"
#include "library.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define OBB_INTERVAL (10000.0f)	//OBB同士の当たり判定を行う範囲(半径)

//*****************************************************************************
//OBBとOBBの衝突判定
//*****************************************************************************
bool CCollision::ColOBBs(const CCollisionModel::OBB &obb1, const CCollisionModel::OBB &obb2)
{
	//OBB同士の距離
	D3DXVECTOR3 Interval = obb1.pos - obb2.pos;
	if (D3DXVec3Length(&Interval) > (FLOAT)OBB_INTERVAL)
	{ //OBB_INTERVALより離れているとき、当たり判定を行わない
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
		return false; // 衝突していない
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
//当たり判定(矩形と矩形)
//=============================================================================
bool CCollision::CollisionRectangleAndRectangle(const D3DXVECTOR3 &pos1,
	const D3DXVECTOR3 &pos2, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &size2)
{
	bool bCollision = false;

	if (pos2.x - (size2.x / 2) < pos1.x + (size1.x / 2) &&
		pos2.x + (size2.x / 2) > pos1.x - (size1.x / 2) &&
		pos2.y - (size2.y / 2) < pos1.y + (size1.y / 2) &&
		pos2.y + (size2.y / 2) > pos1.y - (size1.y / 2)	&&
		pos2.z - (size2.z / 2) < pos1.z + (size1.z / 2) &&
		pos2.z + (size2.z / 2) > pos1.z - (size1.z / 2))
	{
		bCollision = true;
	}

	return bCollision;
}

//=============================================================================
//当たり判定(円形と円形)
//=============================================================================
bool CCollision::CollisionCircularAndCircular(const D3DXVECTOR3 &pos1,
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
//当たり判定(矩形と円形)
//=============================================================================
bool CCollision::CollisionRectangleAndCircular(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &CircularPos,
	const D3DXVECTOR3 &RectangleSize, const float &CircularRadius, const float &RectangleRadian)
{
	//矩形の角度を０にした時の円形の座標を求める
	D3DXVECTOR3 NewCircularPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NewCircularPos.x = (float)(cos(RectangleRadian) * (CircularPos.x - RectanglePos.x) -
		sin(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.x);
	NewCircularPos.y = (float)(sin(RectangleRadian) * (CircularPos.x - RectanglePos.x) +
		cos(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.y);

	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2) - CircularRadius) ||
		NewCircularPos.x >(RectanglePos.x + (RectangleSize.x / 2) + CircularRadius) ||
		NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2) - CircularRadius) ||
		NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2) + CircularRadius))
	{ //「矩形の外枠 + 円の半径」の範囲に入っていないとき
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の左上の判定
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の右上の判定
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の左下の判定
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.y > (RectanglePos.y + (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の右下の判定
		return false;
	}

	return true;
}