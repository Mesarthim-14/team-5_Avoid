#ifndef _MAP_THIN_FLOOR_H_
#define _MAP_THIN_FLOOR_H_
//=============================================================================
//
// 長方形の床クラス [map_thin_floor.h]
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
class CMapThinFloor : public CModel
{
public:
    CMapThinFloor(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CMapThinFloor();                              // デストラクタ

    static CMapThinFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // 初期化処理
    void Uninit()override;                                                          // 初期化処理
    void Update()override;                                                          // 更新処理
    void Draw()override;                                                            // 描画

    void HitCol();  // 当たり判定

private:
    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // 当たり判定ポインタ配列
};

#endif