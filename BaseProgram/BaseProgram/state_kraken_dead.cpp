//=====================================================================
//
// クラーケン死亡状態クラス [state_kraken_dead.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_kraken_dead.h"
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
CKrakenStateDead::CKrakenStateDead()
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CKrakenStateDead::~CKrakenStateDead()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CKrakenStateDead * CKrakenStateDead::Create()
{
    // メモリ確保
    CKrakenStateDead *pState = new CKrakenStateDead;
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
void CKrakenStateDead::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CKraken::MOTION_MAX - 1) - CKraken::MOTION_DEATH), 60);
}

//=====================================================================
// 更新処理
//=====================================================================
void CKrakenStateDead::Update()
{
    CKraken* pKraken = GetKrakenPtr();
    if (pKraken)
    {
        D3DXVECTOR3 pos = pKraken->GetPos();
        pos.y -= 50.0f;
        pKraken->SetPos(pos);
    }
}