#ifndef _STATE_KRAKEN_DEAD_H_
#define _STATE_KRAKEN_DEAD_H_
//=====================================================================
//
// 死亡状態クラス [state_kraken_dead.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_kraken.h"

//=====================================================================
// クラス定義
//=====================================================================
class CKrakenStateDead : public CKrakenState
{
public:
    CKrakenStateDead();   // コンストラクタ
    ~CKrakenStateDead();  // デストラクタ

    static CKrakenStateDead* Create();    // インスタンス生成
    void Init();                            // 初期化処理
    void Update()override;                  // 更新処理

private:
};
#endif