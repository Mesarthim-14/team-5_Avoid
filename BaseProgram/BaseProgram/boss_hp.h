#ifndef _BOSS_HP_H_
#define _BOSS_HP_H_
//=============================================================================
//
// ボスのHPクラス [boss_hp.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CBossHpBack;
class CBossHpBar;

//=========================================================================
// クラス定義
//=========================================================================
class CBossHp : CScene
{
public:
    CBossHp(PRIORITY);      // コンストラクタ
    ~CBossHp();             // デストラクタ

    static CBossHp *Create(const int& nLife);   // インスタンス生成
    HRESULT Init() { return S_OK; }             // 初期化処理
    HRESULT Init(const int& nLife);             // 初期化処理

    void Uninit();                              // 初期化処理
    void Update();                              // 更新処理
    void Draw();                                // 描画
    void SubHp();                               // HPの減算

    inline void SetDraw(const bool& bDraw) { m_bDraw = bDraw; }

private:
    CBossHpBack* m_pBack;   // 背景
    CBossHpBar* m_pBar;     // バー
    bool m_bDraw;
};

#endif