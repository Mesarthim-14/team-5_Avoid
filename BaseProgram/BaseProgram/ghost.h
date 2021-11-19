#ifndef _GHOST_H_
#define _GHOST_H_
//=============================================================================
//
// 幽霊 [ghost.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "wimp_enemy.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CGhostModel;

//=============================================================================
// クラス定義
//=============================================================================
class CGhost : public CWimpEnemy
{
public:
    CGhost(PRIORITY Priority = PRIORITY_CHARACTER); // コンストラクタ
    ~CGhost();                                      // デストラクタ

    static CGhost *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // 初期化処理
    void Uninit();                                                          // 終了処理
    void Update();                                                          // 更新処理

private:
    // private関数
    void CreateModel();     // モデル生成
    void Attack();          // 攻撃
    void Move()override;    // 移動処理
    void Rise();            // 上昇

    // メンバ変数
    CGhostModel *m_pGhostModel; // モデルの変数
    bool m_bFollow;             // 追従フラグ
    bool m_bEnd;                // 終了フラグ
    int m_nEndCount;            // 終了時のカウント
};
#endif