#ifndef _NPC_ENEMY_INFO_H_
#define _NPC_ENEMY_INFO_H_
//=============================================================================
//
// 敵の情報を持ってるNPCヘッダ  [npc_enemy_info.h]
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
class CNpcEnemyInfo : public CNonPlayerCharacter
{
public:
    CNpcEnemyInfo();    // コンストラクタ
    ~CNpcEnemyInfo();   // デストラクタ

    static CNpcEnemyInfo* Create(); // インスタンス生成
    HRESULT Init()override;         // 初期化処理
    void Uninit()override;          // 終了処理
    void Update()override;          // 更新処理
    void Draw()override;            // 描画処理

private:
    void Talk();                    // お話

};
#endif
