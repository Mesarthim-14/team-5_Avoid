#ifndef _NPC_SENTENCE_ENEMY1_H_
#define _NPC_SENTENCE_ENEMY1_H_
//=============================================================================
//
// NPCの文章(エネミー1) [npc_sentence_enemy1.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "billboard.h"

class CPolygon;
//=============================================================================
// クラス定義
//=============================================================================
class CNpcSentenceEnemy1 : public CBillboard
{
public:
    CNpcSentenceEnemy1();    // コンストラクタ
    ~CNpcSentenceEnemy1();   // デストラクタ

    static CNpcSentenceEnemy1* Create();    // インスタンス生成
    HRESULT Init();                         // 初期化処理
    void Uninit();                          // 終了処理
    void Update();                          // 更新処理
    void Draw();                            // 描画

private:
    //法線マップ
    LPDIRECT3DTEXTURE9 m_pTexture;
    LPDIRECT3DSURFACE9 m_pSurface;
    vector<CPolygon*> m_pPolygon;
};
#endif
