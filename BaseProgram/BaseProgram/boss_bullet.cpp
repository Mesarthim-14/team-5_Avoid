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

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS		(ZeroVector3)
#define TEST_ROT		(ZeroVector3)

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
	// 初期化処理
	CBullet::Init();

	m_pModel = CModel::Create(m_pos, m_rot);
	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CANNON_BULLET);
	m_pModel->GetModelInfo()->SetModelStatus(m_pos, m_rot, model);

	m_nLife = 100;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBossBullet::Uninit(void)
{
	CBullet::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBossBullet::Update(void)
{
	// 衝突判定
	Hit();
 	m_pModel->GetModelInfo()->SetPos(m_pos);
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
	//CPlayer* pPlayer = nullptr;
	//pPlayer = (CPlayer*)GetTop(PRIORITY_CHARACTER);

	//if (pPlayer != nullptr)
	//{
	//	D3DXVECTOR3 RayDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//	BOOL bHit = FALSE;
	//	FLOAT fDistance = 0.0f;

	//	for (int nCount = 0; nCount < (int)GetModelInfo()->GetMesh()->GetNumFaces(); nCount++)
	//	{
	//		//下方向
	//		D3DXIntersect(
	//			GetModelInfo()->GetMesh(),
	//			&pPlayer->GetPos(),
	//			&RayDir,
	//			&bHit,
	//			nullptr,
	//			nullptr,
	//			nullptr,
	//			&fDistance,
	//			nullptr,
	//			nullptr);

	//		if (bHit && fDistance < 80.0f)
	//		{
	//			// 着地の処理
	//			pPlayer->Landing(pPlayer->GetPos().y + fDistance);

	//			break;
	//		}
	//		else if (!bHit)
	//		{
	//			pPlayer->SetLanding(false);
	//		}
	//	}
	//}
}

//=============================================================================
// 情報のポインタ生成
//=============================================================================
void CBossBullet::Move()
{
}