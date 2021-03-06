//=====================================================================
//
// クラーケン怒り状態クラス [state_kraken_angry.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_kraken_angry.h"
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
CKrakenStateAngry::CKrakenStateAngry()
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CKrakenStateAngry::~CKrakenStateAngry()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CKrakenStateAngry * CKrakenStateAngry::Create()
{
    // メモリ確保
    CKrakenStateAngry *pState = new CKrakenStateAngry;
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
void CKrakenStateAngry::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CKraken::MOTION_MAX - 1) - CKraken::MOTION_ANGRY), 60);
}

//=====================================================================
// 更新処理
//=====================================================================
void CKrakenStateAngry::Update()
{

}