#ifndef _PLANE_H_
#define _PLANE_H_
//=============================================================================
//
// 3Dポリゴンヘッダー [plane.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene3D.h"

//=========================================================================
// 3Dポリゴンクラス
//=========================================================================
class CPlane :public CScene3D
{
public:
	CPlane(PRIORITY Priority = PRIORITY_0) {}	// コンストラクタ
	virtual ~CPlane() {}						// デストラクタ
	virtual void Draw();					// 描画処理

private:

};
#endif