#ifndef _NPC_ANGRY_INFO_H_
#define _NPC_ANGRY_INFO_H_
//=============================================================================
//
// 怒りNPCヘッダ  [npc_angry_info.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "non_player_character.h"

//=============================================================================
// クラス定義
//=============================================================================
class CNpcAngryInfo : public CNonPlayerCharacter
{
public:
    CNpcAngryInfo();    // コンストラクタ
    ~CNpcAngryInfo();   // デストラクタ

    static CNpcAngryInfo* Create(); // インスタンス生成
    HRESULT Init()override;         // 初期化処理
    void Uninit()override;          // 終了処理
    void Update()override;          // 更新処理
    void Draw()override;            // 描画処理

private:
    void Talk();                    // お話

};
#endif
