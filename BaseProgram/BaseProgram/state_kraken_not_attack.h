#ifndef _STATE_KRAKEN_NOT_ATTACK_H_
#define _STATE_KRAKEN_NOT_ATTACK_H_
//=====================================================================
//
// 攻撃しない状態管理クラス [state_kraken_not_attack.h]
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
class CKrakenStateNotAttack : public CKrakenState
{
public:
    CKrakenStateNotAttack();    // コンストラクタ
    ~CKrakenStateNotAttack();   // デストラクタ

    static CKrakenStateNotAttack* Create(); // インスタンス生成
    void Init();                            // 初期化処理
    void Update()override;                  // 更新処理

private:
};
#endif