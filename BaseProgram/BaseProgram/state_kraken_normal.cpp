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
#include "shark.h"
#include "marlin.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define BULLET_INTERVAL (500)   // たま発射間隔
constexpr int MAX_ENEMY = 5;
constexpr float ANGLE = 5;
constexpr float ROT_ANGLE = ANGLE*2;

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
    SetAnimation(UINT((CKraken::MOTION_MAX - 1) - CKraken::MOTION_IDOL), 60);
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

    // バレットカウント
    m_nBulletCount++;
    if (m_nBulletCount == BULLET_INTERVAL)
    {
        int nNum = CLibrary::Random(0, 10);
        if (nNum < 7)
        {
            // 弾発射
            ShotBullet(pKraken);
        }
        else
        {
            ShotEnemy(pKraken);
        }
    }
}

//=====================================================================
// 弾発射
//=====================================================================
void CKrakenStateNormal::ShotBullet(CKraken* &pKraken)
{
        CBossBullet::Create(pKraken->GetPos(), ZeroVector3);
        m_nBulletCount = 0;
        CLibrary::SetSound(CSound::SOUND_SE_KRAKEN_BULLET_MITING);
}

//=====================================================================
// 敵発射
//=====================================================================
void CKrakenStateNormal::ShotEnemy(CKraken *& pKraken)
{
    for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
    {
        CShark::Create(pKraken->GetPos(),
            pKraken->GetRot() + D3DXVECTOR3(0.0f,
                D3DXToRadian(ROT_ANGLE) - D3DXToRadian(nCount*ANGLE),
                0.0f));
    }
    m_nBulletCount = 0;
}
