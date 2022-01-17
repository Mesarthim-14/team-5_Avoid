#ifndef _BRIDGE_H_
#define _BRIDGE_H_
//=============================================================================
//
// 橋クラス [bridge.h]
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
class CBridge : public CMap
{
public:
    CBridge(PRIORITY Priority);    // コンストラクタ
    ~CBridge();                    // デストラクタ

    static CBridge *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // 初期化処理
    void Uninit();                                                          // 終了処理
    void Update();                                                          // 更新処理

private:
    void Col(); // 当たり判定

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // 当たり判定ポインタ配列
};

#endif