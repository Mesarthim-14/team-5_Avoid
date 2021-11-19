#ifndef _WIMP_ENEMY_H_
#define _WIMP_ENEMY_H_
//=============================================================================
//
// サメ [wimp_enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"

//=============================================================================
// クラス定義
//=============================================================================
class CWimpEnemy : public CEnemy
{
public:
    CWimpEnemy(PRIORITY Priority = PRIORITY_CHARACTER); // コンストラクタ
    ~CWimpEnemy();                                      // デストラクタ

    virtual HRESULT Init();     // 初期化処理
    virtual void Update();      // 更新処理

protected:
    void Rush();    // 突進
    bool Follow();  // 追従

private:
    void GravitySwitch();   // 重力の切り替え
    int m_nRushCount;       // 飛んだカウント
    bool isRush;            // 飛んだらtrue
};
#endif