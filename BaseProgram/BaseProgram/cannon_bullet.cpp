//=============================================================================
//
// 大砲の弾クラス [cannon_bullet.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "cannon_bullet.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "kraken.h"
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SPEED	(100.0f)
#define POS_FIX (1000.0f)
#define POS_FIX_Y (700.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CCannonBullet::CCannonBullet(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CCannonBullet::~CCannonBullet()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CCannonBullet * CCannonBullet::Create(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot)
{
	// メモリ確保
	CCannonBullet *pCannonBullet = new CCannonBullet(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pCannonBullet)
	{
		// 初期化処理
		pCannonBullet->Init(CannonPos, CannonRot);
		return pCannonBullet;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCannonBullet::Init(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot)
{
	D3DXVECTOR3 pos = CannonPos;

	// バレットの情報設定
	SetBulletInfo(pos, CannonRot);

	// 初期化処理
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CANNON_BULLET);
	GetModelInfo()->SetModelStatus(pos, ZeroVector3, model);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CCannonBullet::Update()
{
	CModel::Update();
}

//=============================================================================
// 弾の情報
//=============================================================================
void CCannonBullet::SetBulletInfo(D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	pos = D3DXVECTOR3(
		pos.x + (sinf(rot.y)*POS_FIX),
		pos.y + POS_FIX_Y,
		pos.z + (cos(rot.y)*POS_FIX));

	// Follow
	// ボスのポインタ
	CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
	D3DXVECTOR3 Ppos = pKraken->GetPos();	// 座標取得
	SetMove(CLibrary::FollowMoveXZ(pos, Ppos, SPEED));
}