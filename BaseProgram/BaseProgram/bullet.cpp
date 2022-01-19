//=============================================================================
//
// 発射弾 [bullet.cpp]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "bullet.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_Sphere.h"
#include "collisionModel_OBB.h"
#include "collision.h"
#include "state_player_knockback.h"
#include "gauge.h"
#include "particlepop.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS		(ZeroVector3)
#define TEST_ROT		(ZeroVector3)

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(PRIORITY Priority) : CScene(Priority)
{
	m_pos = ZeroVector3;						// 座標
	m_move = ZeroVector3;						// 移動量
	m_rot = ZeroVector3;						// 現在の回転
    m_ColRadius = 0.0f;					        // 当たり判定サイズ
    m_colSizeOBB = ZeroVector3;
	m_nLife = 0;							    // 生存時間
	m_fSpeed = 0.0f;							// スピード
	m_nDamage = 0;							    // ダメージ量
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
    m_pCollisionModelSphere = nullptr;
    m_pColModelOBB = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init()
{
    // 当たり判定モデル(球体)の生成
    if (!m_pCollisionModelSphere)
    {
         m_pCollisionModelSphere = CCollisionModelSphere::Create(m_pos, m_ColRadius, m_rot);
    }

    // 当たり判定モデル(OBB)の生成
    if (!m_pColModelOBB)
    {
        m_pColModelOBB = CCollisionModelOBB::Create(m_pos, m_colSizeOBB, m_rot);
    }

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit()
{
    // 当たり判定モデル(球体)の終了処理
    if (m_pCollisionModelSphere)
    {
        m_pCollisionModelSphere->Uninit();
        m_pCollisionModelSphere = nullptr;
    }

    // 当たり判定モデル(OBB)の終了処理
    if (m_pColModelOBB)
    {
        m_pColModelOBB->Uninit();
        m_pColModelOBB = nullptr;
    }

    Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update()
{
	// 位置更新
	m_pos += m_move;

	m_nLife--;

	if (m_nLife < 0)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw()
{
}

//=============================================================================
// 衝突判定
//=============================================================================
void CBullet::Hit()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CGauge * pGauge = CManager::GetInstance()->GetGame()->GetGauge();
    D3DXVECTOR3 pos = pPlayer->GetPos();
    if (!pPlayer)
    {
        return;
    }

    if (m_pCollisionModelSphere)
    {
        if (pPlayer->GetCollision())
        {
            if (CCollision::ColSphereAndCapsule(m_pCollisionModelSphere->GetSphere(), pPlayer->GetColCapsulePtr()->GetInfo()))
            {
                // 吹っ飛ぶ値
                D3DXVECTOR3 move = GetMove();
                move.x *= 0.5f;
                move.z *= 0.5f;
                move.y = 10.0f;
                pPlayer->ChangeState(CPlayerStateKnockback::Create(move));  // プレイヤーをノックバック
                pPlayer->SubLife(20);                                       // 体力を減らす
                // 自身の終了処理
                pGauge->SetHitDown(true);
                pGauge->SetDown(20);
                // パーティクルの生成
                for (int nCntParticle = 0; nCntParticle <= 20; nCntParticle++)
                {
                    CParticlePop::Create(pos);
                }
                Uninit();
                return;
            }
        }
    }
}