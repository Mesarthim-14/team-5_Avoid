#ifndef _RUBBLE1_H_
#define _RUBBLE1_H_
//=============================================================================
//
// 瓦礫クラス [rubble1.h]
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
class CRubble1 : public CModel
{
public:
    CRubble1(PRIORITY = PRIORITY_MAP);   // コンストラクタ
    ~CRubble1();                                // デストラクタ

    static CRubble1 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);    // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);               // 初期化処理
    void Uninit()override;                                                      // 初期化処理
    void Update()override;                                                      // 更新処理
    void Draw()override;                                                        // 描画

private:
};

#endif