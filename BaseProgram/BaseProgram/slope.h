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
#include "map.h"

//=========================================================================
// クラス定義
//=========================================================================
class CCollisionModelOBB;
class CCollisionModelPolygon;

//=========================================================================
// クラス定義
//=========================================================================
class CSlope : public CMap
{
public:
    CSlope(PRIORITY Priority); // コンストラクタ
    ~CSlope();                 // デストラクタ

    static CSlope *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // 初期化処理
    void Uninit();                                                          // 終了処理

private:
    void Col(); // 当たり判定

    CCollisionModelOBB* m_pColModelOBB;         // 当たり判定モデル(OBB)
    CCollisionModelPolygon* m_pColModelPolygon; //当たり判定モデル(ポリゴン)
};

#endif