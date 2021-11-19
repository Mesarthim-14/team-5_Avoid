//=====================================================================
//
// 大砲状態管理クラス [state_player_cannon.h]
//	Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_player_cannon.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "state_player_normal.h"
#include "gimmick_factory.h"
#include "cannon_manager.h"
#include "cannon.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define DISTANCE	(10.0f)		// 距離
#define SPEED		(15.0f)		// 速度
#define POS_FIX		(100.0f)	// 座標の修正

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerStateCannon::CPlayerStateCannon()
{

}

//=====================================================================
// デストラクタ
//=====================================================================
CPlayerStateCannon::~CPlayerStateCannon()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CPlayerStateCannon * CPlayerStateCannon::Create()
{
	// メモリ確保
	CPlayerStateCannon *pStateJump = new CPlayerStateCannon;
	if (pStateJump)
	{
		// 初期化処理
		pStateJump->Init();
		return pStateJump;
	}
	return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CPlayerStateCannon::Init()
{
	// アニメーション設定
	SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
}

//=====================================================================
// 更新処理
//=====================================================================
void CPlayerStateCannon::Update()
{
	CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
	if (!pPlayer)
	{
		return;
	}

	TrackingCannon(pPlayer);
}

//=====================================================================
// 大砲の後ろへ追従
//=====================================================================
void CPlayerStateCannon::TrackingCannon(CPlayer* &pPlayer)
{
	CCannon* pCannon = CManager::GetInstance()->GetGame()->GetGimmickFactory()->GetCannonManager()->GetCurrentCannon();
	D3DXVECTOR3 CannonPos = pCannon->GetPos();
	D3DXVECTOR3 CannonRot = pCannon->GetRot();
	float fDistance = DISTANCE;

	D3DXVECTOR3 pos = D3DXVECTOR3(
		CannonPos.x + (sinf(CannonRot.y)*POS_FIX),
		pPlayer->GetPos().y,
		CannonPos.z + (cos(CannonRot.y)*POS_FIX));

	D3DXVECTOR3 move = ZeroVector3;
	if (fDistance <= CLibrary::CalDistance(pPlayer->GetPos(), pos))
	{
		D3DXVECTOR3 move = CLibrary::FollowMoveXZ(pPlayer->GetPos(), pos, SPEED);
	}

	pPlayer->SetMove(move);

	// 角度設定
	D3DXVECTOR3 rot = pPlayer->GetRot();
	rot.y = D3DXToRadian(180.0f)+CannonRot.y;
	CLibrary::RotFix(rot.y);
	pPlayer->SetRotDest(rot);
}