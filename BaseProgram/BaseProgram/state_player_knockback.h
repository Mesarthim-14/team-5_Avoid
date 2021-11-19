#ifndef _STATE_PLAYER_KNOCKBACK_H_
#define _STATE_PLAYER_KNOCKBACK_H_
//=====================================================================
//
// ジャンプ状態管理クラス [state_player_knockback.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player.h"

//=====================================================================
// クラス定義
//=====================================================================
class CPlayerStateKnockback : public CPlayerState
{
public:
    CPlayerStateKnockback();    // コンストラクタ
    ~CPlayerStateKnockback();   // デストラクタ

    static CPlayerStateKnockback* Create(); // インスタンス生成
    void Init();                            // 初期化処理
    void Update()override;                  // 更新処理

private:
    int m_nStanCount;
};
#endif