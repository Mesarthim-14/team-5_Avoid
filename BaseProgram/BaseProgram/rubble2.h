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
#include "model.h"

//=========================================================================
// クラス定義
//=========================================================================
class CRubble2 : public CModel
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
};

#endif