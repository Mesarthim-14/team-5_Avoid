#ifndef _CANNON_H_
#define _CANNON_H_
//=============================================================================
//
// 大砲クラス [cannon.h]
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
class CCannon : public CModel
{
public:
    CCannon(PRIORITY = PRIORITY_TEST_MODEL);    // コンストラクタ
    ~CCannon();                                 // デストラクタ

    static CCannon *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // 初期化処理
    void Update();                                                          // 更新処理
    bool Collision();                                                       // 当たり判定

    inline void SetUseFlag() { m_bUse = true; } // 使用している状態にする

private:
    bool m_bUse;    // 使用したかどうか
};

#endif