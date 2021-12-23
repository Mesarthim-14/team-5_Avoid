#ifndef _SWIRL_SCAFFOLD_OBJECT_H_
#define _SWIRL_SCAFFOLD_OBJECT_H_
//=============================================================================
//
// 渦の足場クラス [swirl_scaffold.h]
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
class CSwirlScaffoldObject : public CMap
{
public:
    CSwirlScaffoldObject(PRIORITY Priority); // コンストラクタ
    ~CSwirlScaffoldObject();                 // デストラクタ

    static CSwirlScaffoldObject *Create(const D3DXVECTOR3 &pos);    // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos);                           // 初期化処理
    void Uninit();                                                  // 終了処理
    void Update();                                                  // 更新処理

private:
    void Col(); // 当たり判定

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // 当たり判定ポインタ配列
};

#endif