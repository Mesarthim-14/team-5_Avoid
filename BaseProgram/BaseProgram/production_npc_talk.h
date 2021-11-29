#ifndef _PRODUCTION_NPC_TALK_H_
#define _PRODUCTION_NPC_TALK_H_
//=======================================================================================
//
// 会話の演出クラス [production_npc_talk.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "production.h"

//=======================================================================================
// クラス定義
//=======================================================================================
class CProductionNpcTalk : public CProduction
{
public:
    CProductionNpcTalk();    // コンストラクタ
    ~CProductionNpcTalk();   // デストラクタ

    static CProductionNpcTalk* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // インスタンス生成
    void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                          // 初期化処理
    void Uninit()override;                                                              // 終了処理
    void Update()override;                                                              // 更新処理

private:
};
#endif