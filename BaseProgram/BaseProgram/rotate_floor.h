#ifndef _ROTATE_FLOOR_H_
#define _ROTATE_FLOOR_H_
//=============================================================================
//
// 回転床クラス [rotate_floor.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"

//=========================================================================
// クラス定義
//=========================================================================
class CRotateFloor : public CModel
{
public:
	CRotateFloor(PRIORITY = PRIORITY_TEST_MODEL);	// コンストラクタ
	~CRotateFloor() {}								// デストラクタ

	static CRotateFloor *Create(const D3DXVECTOR3 &pos);	// インスタンス生成
	HRESULT Init(const D3DXVECTOR3 &pos);					// 初期化処理

private:
};

#endif
