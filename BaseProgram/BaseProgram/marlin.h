#ifndef _MARLIN_H_
#define _MARLIN_H_
//=============================================================================
//
// カジキ [marlin.h]
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
class CMarlinModel;

//=============================================================================
// クラス定義
//=============================================================================
class CMarlin : public CWimpEnemy
{
public:
    CMarlin(PRIORITY Priority = PRIORITY_CHARACTER);    // コンストラクタ
    ~CMarlin();                                         // デストラクタ

    static CMarlin *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // 初期化処理
    void Uninit();                                                          // 終了処理
    void Update();                                                          // 更新処理

private:
    // private関数
    void CreateModel(); // モデル生成
    void Attack();      // 攻撃

    // メンバ変数
    CMarlinModel *m_pMarlinModel;   // モデルのポインタ
    static const float m_fCollisionSize;
};
#endif