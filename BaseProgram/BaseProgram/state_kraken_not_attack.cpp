//=====================================================================
//
// 攻撃しない状態 [state_player_not_move.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_kraken_not_attack.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "kraken.h"

//=====================================================================
// コンストラクタ
//=====================================================================
CKrakenStateNotAttack::CKrakenStateNotAttack()
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CKrakenStateNotAttack::~CKrakenStateNotAttack()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CKrakenStateNotAttack * CKrakenStateNotAttack::Create()
{
    // メモリ確保
    CKrakenStateNotAttack *pState = new CKrakenStateNotAttack;
    if (pState)
    {
        // 初期化処理
        pState->Init();
        return pState;
    }

    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CKrakenStateNotAttack::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CKraken::MOTION_MAX - 1) - CKraken::MOTION_IDOL), 60);
}

//=====================================================================
// 更新処理
//=====================================================================
void CKrakenStateNotAttack::Update()
{

}