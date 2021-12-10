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
#include "model.h"

//=========================================================================
// クラス定義
//=========================================================================
class CMapCheckFloor2 : public CModel
{
public:
    CMapCheckFloor2(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CMapCheckFloor2();                              // デストラクタ

    static CMapCheckFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // 初期化処理
    void Uninit()override;                                                          // 初期化処理
    void Update()override;                                                          // 更新処理
    void Draw()override;                                                            // 描画

private:
};

#endif