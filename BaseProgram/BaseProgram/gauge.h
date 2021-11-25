#ifndef _GAUGE_H_
#define _GAUGE_H_
//=====================================================================
//
//    ゲージ処理[gauge.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "scene2d.h"

//=====================================================================
// クラス定義
//=====================================================================
class CGauge : public CScene2D
{
public:
    CGauge();
    ~CGauge();
    //========================
    // メンバ関数
    //========================
    static CGauge * Create();
    HRESULT Init();
    void Uninit();
    void Update();
    void Draw();

    static void SetDown(const float &down)    { m_fSave = down; }       //どれだけ上下するかを設定
    static void SetHitDown(const bool &hit)   { m_bHitDown = hit; }     //下げる情報を持ってくる
    static void SetHitUp(const bool &hit)     { m_bHitUp = hit; }       //上げる情報を持ってくる
    float GetHP()                             { return m_fSave; }       //どれだけ上下するかの情報を持ってくる

private:
    void SetVertexGauge();  // ゲージ減算処理
    void SetDownUp();       // テスト減る処理

    //========================
    // メンバ変数
    //========================
    float m_fDown;              // 減る
    float m_fUp;                // 増える
    static float m_fSave;       // 減る量を確保
    static float m_fHP;         // HP
    static bool m_bHitDown;     // ヒット時下がる
    static bool m_bHitUp;       // ヒット時上がる
};


#endif // !_GAUGE_H_