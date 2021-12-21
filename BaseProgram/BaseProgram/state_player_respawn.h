#ifndef _STATE_PLAYER_RESPAWN_H_
#define _STATE_PLAYER_RESPAWN_H_
//=====================================================================
//
// リスポーン状態クラス [state_player_respawn.h]
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
class CPlayerStateRespawn : public CPlayerState
{
public:
    CPlayerStateRespawn();  // コンストラクタ
    ~CPlayerStateRespawn(); // デストラクタ

    static CPlayerStateRespawn* Create();  // インスタンス生成
    void Init();                           // 初期化処理
    void Update()override;                 // 更新処理

private:
};
#endif