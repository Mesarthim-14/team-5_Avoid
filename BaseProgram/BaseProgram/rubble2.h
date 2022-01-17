#ifndef _RUBBLE2_H_
#define _RUBBLE2_H_
//=============================================================================
//
// 瓦礫クラス [rubble2.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "map.h"
#include "collisionModel_OBB.h"

//=========================================================================
// マクロ定義
//=========================================================================
#define COL_POLYGON_NUM (4)

//=========================================================================
// 前方宣言
//=========================================================================
class CCollisionModelPolygon;

//=========================================================================
// クラス定義
//=========================================================================
class CRubble2 : public CMap
{
public:
    CRubble2(PRIORITY Priority);   // コンストラクタ
    ~CRubble2();                                // デストラクタ

    static CRubble2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);    // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);               // 初期化処理
    void Uninit()override;                                                      // 初期化処理
    void Update()override;                                                      // 更新処理
    void Draw()override;                                                        // 描画

private:
    void Col(); // 当たり判定

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // 当たり判定モデルポインタ(OBB)
    CCollisionModelPolygon* m_pColModelPolygon[COL_POLYGON_NUM];            // 当たり判定モデルポインタ(ポリゴン)
};

#endif