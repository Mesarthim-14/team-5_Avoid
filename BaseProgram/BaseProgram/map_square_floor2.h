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
#include "model.h"
#include "collisionModel_OBB.h"

//=========================================================================
// クラス定義
//=========================================================================
class CMapSquareFloor2 : public CModel
{
public:
    CMapSquareFloor2(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CMapSquareFloor2();                              // デストラクタ

    static CMapSquareFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // 初期化処理
    void Uninit()override;                                                          // 初期化処理
    void Update()override;                                                          // 更新処理
    void Draw()override;                                                            // 描画

    void HitCol();  // 当たり判定

private:
    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // 当たり判定ポインタ配列
};

#endif