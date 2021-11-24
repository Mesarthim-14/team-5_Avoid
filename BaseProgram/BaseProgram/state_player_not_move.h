#ifndef _STATE_PLAYER_STUN_H_
#define _STATE_PLAYER_STUN_H_
//=====================================================================
//
// ジャンプ状態管理クラス [state_player_stun.h]
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
class CPlayerStateNotMove : public CPlayerState
{
public:
    CPlayerStateNotMove();     // コンストラクタ
    ~CPlayerStateNotMove();    // デストラクタ

    static CPlayerStateNotMove* Create();  // インスタンス生成
    void Init();                           // 初期化処理
    void Update()override;                 // 更新処理

private:
    int m_nLimit;
};
#endif