#ifndef _MAP_SQUARE_FLOOR2_H_
#define _MAP_SQUARE_FLOOR2_H_
//=============================================================================
//
// 立方体の床クラス [map_square_floor2.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "map.h"
#include "collisionModel_OBB.h"

//=========================================================================
// クラス定義
//=========================================================================
class CMapSquareFloor2 : public CMap
{
public:
    CMapSquareFloor2(PRIORITY Priority); // コンストラクタ
    ~CMapSquareFloor2();                 // デストラクタ

    static CMapSquareFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // 初期化処理
    void Uninit()override;                                                          // 初期化処理

private:
    void Col();

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // 当たり判定ポインタ配列
};

#endif