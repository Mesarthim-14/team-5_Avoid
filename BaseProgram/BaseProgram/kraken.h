#ifndef _KRAKEN_H_
#define _KRAKEN_H_
//=============================================================================
//
//クラーケン(敵) [kraken.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"
#include "state_object.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CSkinmeshModel;
class CCollisionModelOBB;
class CState;

//=============================================================================
// クラス定義
//=============================================================================
class CKraken : public CEnemy, public CStateObject
{
public:
    CKraken(PRIORITY Priority = PRIORITY_CHARACTER);    // コンストラクタ
    ~CKraken();                                         // デストラクタ

    static CKraken *Create();           // インスタンス生成
    HRESULT Init();                     // 初期化処理
    void Uninit();                      // 終了処理
    void Update();                      // 更新処理
    void ChangeState(CState* pState);   // 状態の変更

    inline void SubLife()                           { m_nLife--; }                  // 体力の減算
    inline CCollisionModelOBB* GetCollosion()const  { return m_pCollision; }        // 当たり判定の情報
    inline bool GetDead()const                      { return m_bDead; }             // 死んだ判定
    inline CSkinmeshModel* GetSkinMesh()const       { return m_pSkinmeshModel; }    // スキンメッシュの情報

private:
    // private関数
    void CreateModel(); // モデルの生成
    void UpdateState(); // プレイヤーの状態
    void Attack();      // 攻撃処理

    // メンバ変数
    CSkinmeshModel *m_pSkinmeshModel;   // スキンメッシュモデルポインタ
    CCollisionModelOBB* m_pCollision;   // 当たり判定
    int m_nBulletCount;                 // 発射カウント
    int m_nLife;                        // ライフ
    bool m_bDead;                       // 死んだフラグ

    // 状態のポインタ
    CState* m_pCurrentState;  // 現在の状態ポインタ
    CState* m_pNextState;     // 次の状態ポインタ
};
#endif