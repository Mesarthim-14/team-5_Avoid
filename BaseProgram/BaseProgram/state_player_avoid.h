#ifndef _STATE_PLAYER_AVOID_H_
#define _STATE_PLAYER_AVOID_H_
//=====================================================================
//
//    回避状態管理クラス [state_player_avoid.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player.h"

//=====================================================================
// クラス定義
//=====================================================================
class CPlayerStateAvoid : public CPlayerState
{
public:
    CPlayerStateAvoid();    // コンストラクタ
    ~CPlayerStateAvoid();   // デストラクタ

    static CPlayerStateAvoid* Create(); // インスタンス生成
    void Init();                        // 初期化処理
    void Update()override;              // 更新処理
    void SetMove();                     // 移動量の設定

private:
    float m_fAvoidValueY;   // 回避移動量（上方向）
    float m_fAvoidValueXZ;  // 回避移動量（横方向）

};
#endif