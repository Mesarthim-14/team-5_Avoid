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
class CKrakenTentacles;
class CBossHp;

//=============================================================================
// クラス定義
//=============================================================================
class CKraken : public CEnemy, public CStateObject
{
public:
    enum MOTION
    {
        MOTION_NONE = -1,   // 初期値
        MOTION_IDOL,        // 通常
		MOTION_ATTACK,      // 攻撃
		MOTION_ANGRY,       // 怒ったとき
		MOTION_DAMAGE,      // ダメージ
        MOTION_DEATH,       // 死んだとき
        MOTION_MAX
    };

    CKraken(PRIORITY Priority = PRIORITY_CHARACTER);    // コンストラクタ
    ~CKraken();                                         // デストラクタ

    static CKraken *Create();           // インスタンス生成
    HRESULT Init();                     // 初期化処理
    void Uninit();                      // 終了処理
    void Update();                      // 更新処理
    void ChangeState(CState* pState);   // 状態の変更
    void SubLife();                     // 体力の減算

    inline CCollisionModelOBB* GetCollosion()const  { return m_pCollision; }        // 当たり判定の情報
    inline bool GetDead()const                      { return m_bDead; }             // 死んだ判定
    inline CSkinmeshModel* GetSkinMesh()const       { return m_pSkinmeshModel; }    // スキンメッシュの情報
    inline CBossHp* GetHpUi()const                  { return m_pHpUi; }

private:
    // private関数
    void CreateModel();     // モデルの生成
    void UpdateState();     // プレイヤーの状態
    void Attack();          // 攻撃処理
    void CreateTentacles(); // 触手の生成

    // メンバ変数
    CSkinmeshModel *m_pSkinmeshModel;           // スキンメッシュモデルポインタ
    CCollisionModelOBB* m_pCollision;           // 当たり判定
    CState* m_pCurrentState;                    // 現在の状態ポインタ
    CState* m_pNextState;                       // 次の状態ポインタ
    vector<CKrakenTentacles*> m_apTentacles;    // 触手
    int m_nBulletCount;                         // 発射カウント
    int m_nLife;                                // ライフ
    bool m_bDead;                               // 死んだフラグ
    CBossHp* m_pHpUi;                           // HPのUi
};
#endif