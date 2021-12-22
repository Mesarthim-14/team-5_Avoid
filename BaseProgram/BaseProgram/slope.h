#ifndef _SLOPE_H_
#define _SLOPE_H_
//=============================================================================
//
// 坂道クラス [slope.h]
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
class CSlope : public CModel
{
public:
    CSlope(PRIORITY = PRIORITY_MAP); // コンストラクタ
    ~CSlope();                              // デストラクタ

    static CSlope *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // 初期化処理

private:
};

#endif