#ifndef _STATE_PLAYER_JUMP_H_
#define _STATE_PLAYER_JUMP_H_
//=====================================================================
//
//    ジャンプ状態管理クラス [state_player_normal.h]
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
class CPlayerStateJump : public CPlayerState
{
public:
    CPlayerStateJump();     // コンストラクタ
    ~CPlayerStateJump();    // デストラクタ

    static CPlayerStateJump* Create();  // インスタンス生成
    void Init();                        // 初期化処理
    void Update()override;              // 更新処理

private:
    // private関数
    void SubLife(CPlayer* &pPlayer);        // ライフの減算
    void JumpProcess(CPlayer* &pPlayer);    // ジャンプ中の処理
    void Avoidance(CPlayer* &pPlayer);
    void JumpEffect();

    float m_fJumpTimeCount;     // ジャンプ時間カウント
    float m_fJumpValue;         // ジャンプ量
    float m_fDushJumpValue;     // 移動ジャンプ時の横移動加算量
    int m_nChargeJumpCount;     // ためジャンプカウント
    bool m_bIsReadyChargeJump;  // ためジャンプ準備完了か
    bool m_bJumpCheck;          // ジャンプし始めたか
    bool m_bJumpEffect;
    int m_nCntEffect;
};
#endif