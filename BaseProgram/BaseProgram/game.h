#ifndef _GAME_H_
#define _GAME_H_
//=======================================================================================
//
// ゲームクラス [game.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// 前方宣言
//=======================================================================================
class CPlayer;
class CGimmickFactory;
class CKraken;
class CNpcFactory;
class CGaussFilter;
class CPause;
class CGauge;

//=======================================================================================
// ゲームクラス
//=======================================================================================
class CGame : public CModeBase
{
public:
    CGame();        // コンストラクタ
    ~CGame();       // デストラクタ

    HRESULT Init();     // 初期化処理
    void Uninit();      // 終了処理
    void Update();      // 更新処理
    void Draw();        // 描画処理
    void CreateUi();    // Uiの生成
    static void BeginGauss();                                                           // ガウスフィルタの開始
    static void EndGauss();                                                             // ガウスフィルタの終了
    inline static float GetGravity()                    { return m_fGravity; };         // 重力
    inline CGimmickFactory* GetGimmickFactory()const    { return m_pGimmickFactory; }   // ギミックの情報
    inline CKraken* GetKraken()const                    { return m_pKraken; }           // クラーケン
    inline void GameEnd()                               { m_bGameEnd = true; }          // ゲーム終了フラグ
    inline CNpcFactory* GetNpcFactory()const            { return m_pNpcFactory; }       // NPCファクトリー
    inline void SetGaussFilter(const bool& bUse)        { m_bGaussFilter = bUse; }      // ガウスフィルタ―を設定
    inline CGauge * GetGauge()const                     { return m_pGauge; }            // ゲージ情報取得
    inline CPause * GetPause()const                     { return m_pPause; }            // ポーズ情報取得

private:
    // private関数
    void CreatePlayer();    // プレイヤーの生成関数
    void CreateEnemy();     // 敵の生成
    void CreateNPC();       // NPC
    void CreateMap();       // マップの生成
    void ShowInfo();        // 情報表示
    void CreateObject();    // オブジェクト生成
    void CreateFilter();    // フィルタの生成

    // メンバ変数
    CPlayer *m_pPlayer;                     // プレイヤーのポインタ
    CKraken *m_pKraken;                     // クラーケンのポインタ
    bool m_bGameEnd;                        // ゲームのエンドフラグ
    LPD3DXFONT m_pFont;                     // デバック用フォント
    static float m_fGravity;                // 重力
    CGimmickFactory *m_pGimmickFactory;     // ギミック生成
    CNpcFactory* m_pNpcFactory;             // NPC生成クラスポインタ
    static bool m_bGaussFilter;             // フィルターのフラグ
    static CGaussFilter* m_pGaussFilter;    // ガウスフィルター
    CGauge * m_pGauge;                      // ゲージポインタ
    CPause *m_pPause;                       // ポーズポインタ
};
#endif