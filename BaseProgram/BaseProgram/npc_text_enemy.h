#ifndef _NPC_TEXT_ENEMY_H_
#define _NPC_TEXT_ENEMY_H_
//=============================================================================
//
// NPCのエネミーテキスト [npc_text_enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "npc_text.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CBillboard;

//=============================================================================
// クラス定義
//=============================================================================
class CNpcTextEnemy : public CNpcText
{
public:
    CNpcTextEnemy();    // コンストラクタ
    ~CNpcTextEnemy();   // デストラクタ

    static CNpcTextEnemy* Create(); // インスタンス生成
    HRESULT Init();                 // 初期化処理
    void Uninit();                  // 終了処理
    void Update();                  // 更新処理

    inline bool GetEnd() { return m_bEnd; }

private:
    void CreateSentence1();     // 文章の生成
    void CreateSentence2();     // 文章の生成

    typedef void(CNpcTextEnemy::*SENTENCE_FUNC)();
    vector<SENTENCE_FUNC> m_CreateSentence =
    { &CNpcTextEnemy::CreateSentence1 ,
        &CNpcTextEnemy::CreateSentence2 };

    int m_nCounter;         // カウンター
    bool m_bEnd;
    CBillboard* m_pSentence;
};
#endif
