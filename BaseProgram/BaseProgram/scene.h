#ifndef _SCENE_H_
#define _SCENE_H_
//=============================================================================
//
// オブジェクト管理クラス [scene.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// シーンクラス
//=============================================================================
class CScene
{
public:
    //=========================================================================
    //描画の優先順位の列挙型
    //=========================================================================
    enum PRIORITY
    {
        PRIORITY_0 = 0,
        PRIORITY_1,
        PRIORITY_TEST_MODEL,    // テストモデル
        PRIORITY_MODEL,         // モデル
        PRIORITY_CHARACTER,     // キャラクター
        PRIORITY_COLLISION,     //当たり判定
        PRIORITY_EFFECT,        // エフェクト
        PRIORITY_SHADOW,        // 影
        PRIORITY_UI,            // UI
        PRIORITY_FADE,          // FADE
        PRIORITY_MAX            // 優先順位の最大数
    };

    CScene(PRIORITY Priority);      // コンストラクタ
    virtual ~CScene();              // デストラクタ
    static void ReleaseAll();       // 全てのオブジェクトをリリース
    static void UpdateAll();        // 全てのオブジェクトを更新
    static void DrawAll();          // 全てのオブジェクトを描画

    virtual HRESULT Init() = 0;     // 初期化処理
    virtual void Uninit() = 0;      // 終了処理
    virtual void Update() = 0;      // 更新処理
    virtual void Draw() = 0;        // 描画処理

    CScene *GetNext();                          // 次の情報を受け取る
    static CScene *GetTop(const int &nCount);   // シーンの情報受け取り
    static void SetPause(const bool &Pause);    // ポーズの情報

protected:
    void Release(); // オブジェクトを開放

private:
    // private関数
    void DeathRelease();    // 死亡フラグのリリース

    // メンバ変数
    static CScene *m_pTop[PRIORITY_MAX];    // 先頭のオブジェクトへのポインタ
    static CScene *m_pCur[PRIORITY_MAX];    // 現在のオブジェクトへのポインタ
    CScene *m_pPrev;                        // 前のオブジェクトへのポインタ
    CScene *m_pNext;                        // 次のオブジェクトへのポインタ
    PRIORITY m_Priority;                    // 描画の優先順位
    bool m_bDeath;                          // 死亡フラグ
    bool m_bLate;                           // 描画を遅らせる処理
    static bool m_bPause;                   // ポーズの情報
};

#endif