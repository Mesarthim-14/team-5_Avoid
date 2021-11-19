#ifndef _FADE_H_
#define _FADE_H_
//=============================================================================
//
// フェードクラスヘッダー処理 [fade.h]
// Author : konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPolygon;

//=============================================================================
// フェードクラス
//=============================================================================
class CFade
{
public:
    //=========================================================================
    //列挙型定義
    //=========================================================================
    enum FADE_MODE
    {
        FADE_MODE_NONE = 0, //何もない状態
        FADE_MODE_IN,       //フェードイン状態
        FADE_MODE_OUT,      //フェードアウト状態
        FADE_MODE_MAX
    };

    CFade();            // コンストラクタ
    ~CFade();           // デストラクタ

    HRESULT Init();     // 初期化処理
    void Uninit();      // 終了処理
    void Update();      // 更新処理　
    void Draw();        // 描画処理
    void SetFade(CManager::MODE_TYPE mode);        // フェード設定

    // Get関数
    FADE_MODE GetFade();    // フェード情報

private:
    D3DXCOLOR m_colorFade;              //フェード色
    FADE_MODE m_FadeMode;               //フェードモード判定用
    CManager::MODE_TYPE m_modeNext;     //フェード終了後のモード設定用
    CPolygon *m_pPolygon;               // ポリゴンクラスのポインタ
};
#endif