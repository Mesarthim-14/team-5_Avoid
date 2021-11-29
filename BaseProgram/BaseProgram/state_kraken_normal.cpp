//=====================================================================
//
// クラーケン通常状態管理クラス [state_kraken_normal.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_kraken_normal.h"
#include "player.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "kraken.h"
#include "boss_bullet.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define BULLET_INTERVAL (500)   // たま発射間隔

//=====================================================================
// コンストラクタ
//=====================================================================
CKrakenStateNormal::CKrakenStateNormal()
{
    m_nBulletCount = 0;
}

//=====================================================================
// デストラクタ
//=====================================================================
CKrakenStateNormal::~CKrakenStateNormal()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CKrakenStateNormal * CKrakenStateNormal::Create()
{
    // メモリ確保
    CKrakenStateNormal *pStateNormal = new CKrakenStateNormal;
    if (pStateNormal)
    {
        // 初期化処理
        pStateNormal->Init();
        return pStateNormal;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CKrakenStateNormal::Init()
{
    // アニメーション設定
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
}

//=====================================================================
// 更新処理
//=====================================================================
void CKrakenStateNormal::Update()
{
    CKraken* pKraken = GetKrakenPtr();
    if (!pKraken)
    {
        return;
    }

    // 弾発射
    ShotBullet(pKraken);
}

//=====================================================================
// 弾発射
//=====================================================================
void CKrakenStateNormal::ShotBullet(CKraken* &pKraken)
{
    // バレットカウント
    m_nBulletCount++;
    if (m_nBulletCount == BULLET_INTERVAL)
    {
        CBossBullet::Create(pKraken->GetPos(), ZeroVector3);
        m_nBulletCount = 0;
    }
}
