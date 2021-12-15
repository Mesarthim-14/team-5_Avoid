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
	m_nLife = 0;							    // 生存時間
	m_fSpeed = 0.0f;							// スピード
	m_nDamage = 0;							        // ダメージ量
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
    m_pCollisionModelSphere = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CBullet * CBullet::Create()
{
	// メモリ確保
	CBullet *pBullet = new CBullet(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pBullet)
	{
		// 初期化処理
		pBullet->Init();

		return pBullet;
	}

	return nullptr;
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

    Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update()
{
    // 当たり判定モデルの更新
    if (m_pCollisionModelSphere)
    {
        m_pCollisionModelSphere->SetInfo(m_pos, D3DXVECTOR3(m_ColRadius, m_ColRadius, m_ColRadius), m_rot);
    }

	// 位置更新
	m_pos += m_move;

	m_nLife--;

	if (m_nLife < 0)
	{
        // 当たり判定モデルの終了処理
        if (m_pCollisionModelSphere)
        {
            m_pCollisionModelSphere->Uninit();
        }

		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw()
{

}