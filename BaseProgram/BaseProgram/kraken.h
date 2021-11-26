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

//=============================================================================
// 前方宣言
//=============================================================================
class CSkinmeshModel;
class CCollisionModelOBB;

//=============================================================================
// クラス定義
//=============================================================================
class CKraken : public CEnemy
{
public:
    CKraken(PRIORITY Priority = PRIORITY_CHARACTER);    // コンストラクタ
    ~CKraken();                                         // デストラクタ

    static CKraken *Create();   // インスタンス生成
    HRESULT Init();             // 初期化処理
    void Uninit();              // 終了処理
    void Update();              // 更新処理

    inline void SubLife()           { m_nLife--; }
    CCollisionModelOBB* GetCollosion() { return m_pCollision; }
    inline bool GetDead()const      { return m_bDead; }

private:
    // private関数
    void Attack();      // 攻撃
    void ShotBullet();  // 弾発射
    void CreateModel(); // モデルの生成

    CSkinmeshModel *m_pSkinmeshModel;   // スキンメッシュモデルポインタ
    int m_nBulletCount;                 // 発射カウント
    CCollisionModelOBB* m_pCollision;   // 当たり判定
    int m_nLife;                        // ライフ
    bool m_bDead;                       // 死んだフラグ
};
#endif