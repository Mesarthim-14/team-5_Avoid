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
#include "model.h"

//=========================================================================
// クラス定義
//=========================================================================
class CMapThinFloor2 : public CModel
{
public:
    CMapThinFloor2(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CMapThinFloor2();                              // デストラクタ

    static CMapThinFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // 初期化処理
    void Uninit()override;                                                          // 初期化処理
    void Update()override;                                                          // 更新処理
    void Draw()override;                                                            // 描画

private:
};

#endif