#ifndef _STATE_PLAYER_NORMAL_H_
#define _STATE_PLAYER_NORMAL_H_
//=====================================================================
//
//    通常状態管理クラス [state_player_normal.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player.h"

//=====================================================================
// 前方宣言
//=====================================================================
class CPlayer;

//=====================================================================
// クラス定義
//=====================================================================
class CPlayerStateNormal : public CPlayerState
{
public:
    CPlayerStateNormal();                   // コンストラクタ
    ~CPlayerStateNormal();                  // デストラクタ
    static CPlayerStateNormal* Create();    // インスタンス生成

    void Init();            // 初期化処理
    void Update()override;  // 更新処理

private:
    void Jump(CPlayer* &pPlayer);       // ジャンプ処理
    void Avoidance(CPlayer* &pPlayer);  // 回避
    
};
#endif