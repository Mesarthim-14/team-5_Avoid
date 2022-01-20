#ifndef _STATE_PLAYER_H_
#define _STATE_PLAYER_H_
//=====================================================================
//
//    状態管理クラス [state_player.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state.h"

//=====================================================================
// 前方宣言
//=====================================================================
class CPlayer;

//=====================================================================
// クラス定義
//=====================================================================
class CPlayerState : public CState
{
public:
    CPlayerState();     // コンストラクタ
    ~CPlayerState();    // デストラクタ

protected:
    virtual void SetAnimation(const UINT &animID, const FLOAT &time);               // アニメーション設定
    virtual void SetAnimation(const UINT &animID, const FLOAT &time, bool bLoop);   // アニメーション設定
    void MoveByKeyboard(CPlayer* &pPlayer);                                         // 入力処理

    // フラグを返す式
    function<bool(const int&, CPlayerState*)> CounterFunc = [](const int &nLimit, CPlayerState* pState)
    {
        if (nLimit <= pState->m_nCounter++)
        {
            return true;
        }
        return false;
    };

private:
    void SoundUpdate();     // 音の更新

    float m_fAngleSpeed;    // 目標向きまで向かうスピード 
    int m_nCounter;         // カウンタ
    bool m_bMove[2];        // 移動のフラグ
    bool m_Effect;
};
#endif