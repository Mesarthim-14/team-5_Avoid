#ifndef _STATE_KRAKEN_DAMAGE_H_
#define _STATE_KRAKEN_DAMAGE_H_
//=====================================================================
//
// ダメージ状態クラス [state_kraken_damage.h]
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
class CKrakenStateDamage : public CKrakenState
{
public:
    CKrakenStateDamage();   // コンストラクタ
    ~CKrakenStateDamage();  // デストラクタ

    static CKrakenStateDamage* Create();    // インスタンス生成
    void Init();                            // 初期化処理
    void Update()override;                  // 更新処理

private:
};
#endif