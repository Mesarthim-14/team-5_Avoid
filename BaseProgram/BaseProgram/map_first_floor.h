#ifndef _MAP_FIRST_FLOOR_H_
#define _MAP_FIRST_FLOOR_H_
//=============================================================================
//
// テストモデルクラス [map_first_floor.h]
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
class CMapFirstFloor : public CModel
{
public:

    CMapFirstFloor(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CMapFirstFloor();                              // デストラクタ

    static CMapFirstFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // 初期化処理
    void Uninit()override;                                                          // 初期化処理
    void Update()override;                                                          // 更新処理
    void Draw()override;                                                            // 描画
    void OBBs();                                                                    // OBB衝突判定

private:
};

#endif