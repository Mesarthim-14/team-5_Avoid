#ifndef _MAP_SQUARE_FLOOR_H_
#define _MAP_SQUARE_FLOOR_H_
//=============================================================================
//
// 立方体の床クラス [map_square_floor.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"

//=========================================================================
// クラス定義
//=========================================================================
class CMapSquareFloor : public CModel
{
public:
    CMapSquareFloor(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CMapSquareFloor();                              // デストラクタ

    static CMapSquareFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // 初期化処理
    void Uninit()override;                                                          // 初期化処理
    void Update()override;                                                          // 更新処理
    void Draw()override;                                                            // 描画

private:
};

#endif