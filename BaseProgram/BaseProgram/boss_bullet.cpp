//=============================================================================
//
// ボスの発射弾 [boss_bullet.cpp]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "boss_bullet.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collision.h"
#include "collisionModel_Sphere.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS		(ZeroVector3)
#define TEST_ROT		(ZeroVector3)
#define COLLISION_SIZE  (D3DXVECTOR3(90.0f, 90.0f, 90.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CBossBullet::CBossBullet(PRIORITY Priority) : CBullet(Priority)
{
	m_pModel = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBossBullet::~CBossBullet()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CBossBullet * CBossBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	// メモリ確保
	CBossBullet *pTestModel = new CBossBullet(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pTestModel)
	{
		pTestModel->m_pos = pos;
		pTestModel->m_rot = rot;
		pTestModel->m_move = move;
		// 初期化処理
		pTestModel->Init();

		return pTestModel;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBossBullet::Init(void)
{
    // サイズの設定
    m_size = COLLISION_SIZE;

	// 初期化処理
	CBullet::Init();

	m_pModel = CModel::Create(m_pos, m_rot);
	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CANNON_BULLET);
	m_pModel->GetModelInfo()->SetModelStatus(m_pos, m_rot, model);

	m_nLife = 200;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBossBullet::Uninit(void)
{
	if (m_pModel != nullptr)
	{
		m_pModel->Uninit();
		m_pModel = nullptr;
	}
	CBullet::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBossBullet::Update(void)
{
	// 衝突判定
	Hit();

	if (m_pModel != nullptr)
	{
		m_pModel->GetModelInfo()->SetPos(m_pos);
	}
 	
	CBullet::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CBossBullet::Draw(void)
{
	CBullet::Draw();
}

//=============================================================================
// 衝突判定
//=============================================================================
void CBossBullet::Hit(void)
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();

    if (pPlayer)
    {
        if (GetColSpherePtr() && pPlayer->GetColCapsulePtr())
        {
            if (CCollision::ColSphereAndCapsule(GetColSpherePtr()->GetInfo(), pPlayer->GetColCapsulePtr()->GetInfo()))
            {
                Uninit();
            }
        }
    }
}

//=============================================================================
// 情報のポインタ生成
//=============================================================================
void CBossBullet::Move()
{
}