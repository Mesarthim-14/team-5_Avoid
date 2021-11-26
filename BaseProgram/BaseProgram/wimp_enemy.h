#ifndef _WIMP_ENEMY_H_
#define _WIMP_ENEMY_H_
//=============================================================================
//
// サメ [wimp_enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CCollisionModelOBB;
class CPlayer;

//=============================================================================
// クラス定義
//=============================================================================
class CWimpEnemy : public CEnemy
{
public:
    CWimpEnemy(PRIORITY Priority = PRIORITY_CHARACTER); // コンストラクタ
    ~CWimpEnemy();                                      // デストラクタ

    virtual HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot);     // 初期化処理
    virtual void Update();      // 更新処理

protected:
    void Rush();            // 突進
    bool Follow();          // 追従
    void Collision();       // 当たり判定
    void AffectPlayer(CPlayer* &pPlayer);    // プレイヤーに影響を与える

private:
    void GravitySwitch();               // 重力の切り替え
    int m_nRushCount;                   // 飛んだカウント
    bool isRush;                        // 飛んだらtrue
    CCollisionModelOBB* m_pCollision;   // 当たり判定
    bool m_bHit;                        // 当たったフラグ
    int m_nHitInter;                    // 当たり判定のカウント
};
#endif