#ifndef _NPC_TEXT_H_
#define _NPC_TEXT_H_
//=============================================================================
//
// NPCのテキスト [npc_text.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// クラス定義
//=============================================================================
class CNpcText : public CScene
{
public:
    CNpcText(PRIORITY priority = PRIORITY_0);   // コンストラクタ
    virtual ~CNpcText();                        // デストラクタ

    virtual HRESULT Init();     // 初期化処理
    virtual void Uninit();      // 終了処理
    virtual void Update();      // 更新処理
    virtual void Draw() {}      // 描画処理
    virtual bool GetEnd()const = 0;

private:
    int m_nCounter;
};

#endif
