#ifndef _MAP_THIN_FLOOR2_H_
#define _MAP_THIN_FLOOR2_H_
//=============================================================================
//
// 長方形の床クラス [map_thin_floor2.h]
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
class CMapThinFloor2 : public CMap
{
public:
    CMapThinFloor2(PRIORITY Priority); // コンストラクタ
    ~CMapThinFloor2();                 // デストラクタ

    static CMapThinFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // 初期化処理
    void Uninit()override;                                                          // 初期化処理

private:
    void Col();

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // 当たり判定ポインタ配列
};

#endif