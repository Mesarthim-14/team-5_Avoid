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
#include "map.h"
#include "collisionModel_OBB.h"

//=========================================================================
// マクロ定義
//=========================================================================
#define COL_NUM (3)

//=========================================================================
// クラス定義
//=========================================================================
class CRotateFloor : public CMap
{
public:
    CRotateFloor(PRIORITY Priority);   // コンストラクタ
    ~CRotateFloor() {}                              // デストラクタ

    static CRotateFloor *Create(const D3DXVECTOR3 &pos);    // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos);                   // 初期化処理
    void Uninit();                                          // 終了処理
    void Update();                                          // 更新処理

private:
    void Col(); // 当たり判定

    CCollisionModelOBB* m_pColModelOBB[COL_NUM][CCollisionModelOBB::SURFACE_MAX];    // 当たり判定ポインタ配列
};

#endif
