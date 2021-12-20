#ifndef _STATE_KRAKEN_ANGRY_H_
#define _STATE_KRAKEN_ANGRY_H_
//=====================================================================
//
// 怒り状態クラス [state_kraken_angry.h]
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
class CKrakenStateAngry : public CKrakenState
{
public:
    CKrakenStateAngry();   // コンストラクタ
    ~CKrakenStateAngry();  // デストラクタ

    static CKrakenStateAngry* Create();    // インスタンス生成
    void Init();                            // 初期化処理
    void Update()override;                  // 更新処理

private:
};
#endif