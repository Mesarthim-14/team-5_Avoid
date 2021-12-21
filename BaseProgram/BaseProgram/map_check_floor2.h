#ifndef _MAP_CHECK_FLOOR2_H_
#define _MAP_CHECK_FLOOR2_H_
//=============================================================================
//
// チェックポイントのオブジェ [map_check_floor2.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "map.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CCollisionModelCylinder;

//=========================================================================
// クラス定義
//=========================================================================
class CMapCheckFloor2 : public CMap
{
public:
    CMapCheckFloor2(PRIORITY Priority); // コンストラクタ
    ~CMapCheckFloor2();                 // デストラクタ

    static CMapCheckFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // 初期化処理
    void Uninit()override;                                                          // 初期化処理

private:
    void Col();

    CCollisionModelCylinder* m_pColModelCylinder;   // 当たり判定ポインタ
};

#endif