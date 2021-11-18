//=====================================================================
//
//	プレイヤーの状態管理クラス [state_player.h]
//	Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルード
//=====================================================================
#include "state_player.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "camera.h"
#include "particlepop.h"

//=====================================================================
// コンストラクタ
//=====================================================================
CPlayerState::CPlayerState()
{
	m_fAngleSpeed = 0.6f;
	memset(m_bMove, 0, sizeof(m_bMove));
}

//=====================================================================
// デストラクタ
//=====================================================================
CPlayerState::~CPlayerState()
{
}

//=====================================================================
// アニメーション設定
//=====================================================================
void CPlayerState::SetAnimation(const UINT &animID, const FLOAT &time)
{
	CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
	if (!pPlayer)
	{
		return;
	}
	CSkinmeshModel* pSkinMeshModel = pPlayer->GetCurrentSkinMeshPtr();
	if (!pSkinMeshModel)
	{
		return;
	}

	pSkinMeshModel->GetHLcontroller()->ChangeAnimation(animID);
	pSkinMeshModel->GetHLcontroller()->SetLoopTime(animID, time);
}

//=====================================================================
// キーボード処理
//=====================================================================
void CPlayerState::MoveByKeyboard(CPlayer* &pPlayer)
{
	D3DXVECTOR3 pos = pPlayer->GetPos();			// 座標
	D3DXVECTOR3 rot = pPlayer->GetRot();			// 角度
	float fSpeed = pPlayer->GetSpeed();				// 移動量
	float fCameraRot = D3DXToRadian(CManager::GetInstance()->GetCamera()->GetRot().y);	// カメラの角度
	float fAngle = pPlayer->GetAngle();				// アングル
	D3DXVECTOR3 Inertia = pPlayer->GetInertia();	// 慣性
	D3DXVECTOR3 rotDest = pPlayer->GetRotDest();	// 目的の角度
	m_bMove[1] = m_bMove[0];
	m_bMove[0] = false;

	// 前に移動
	if (CLibrary::KeyboardPress(DIK_W))
	{
		// 移動量・角度の設定
		Inertia.x = +sinf(fAngle)*fSpeed;
		Inertia.z = -cosf(fAngle)*fSpeed;
		//進行方向に向きを合わせる
		rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
		m_bMove[0] = true;
	}

	// 後ろに移動
	if (CLibrary::KeyboardPress(DIK_S))
	{
		// 移動量・角度の設定
		Inertia.x = -sinf((fAngle))*fSpeed;
		Inertia.z = +cosf((fAngle))*fSpeed;
		//進行方向に向きを合わせる
		rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(-180.0f);
		m_bMove[0] = true;
	}

	// 左に移動
	if (CLibrary::KeyboardPress(DIK_A))
	{
		// 移動量・角度の設定
		Inertia.x = +sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
		Inertia.z = -cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;

		//進行方向に向きを合わせる
		rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
		m_bMove[0] = true;
	}

	// 右に移動
	if (CLibrary::KeyboardPress(DIK_D))
	{
		// 移動量・角度の設定
		Inertia.x = +sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		Inertia.z = -cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		//進行方向に向きを合わせる
		rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(-180.0f);
		m_bMove[0] = true;
	}

	//左前に移動
	if (CLibrary::KeyboardPress(DIK_W) && CLibrary::KeyboardPress(DIK_A))
	{
		// 移動量・角度の設定
		Inertia.x = +sinf((fAngle + D3DXToRadian(45.0f)))*fSpeed;
		Inertia.z = -cosf((fAngle + D3DXToRadian(45.0f)))*fSpeed;
		rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
		m_bMove[0] = true;
	}

	//右前に移動
	if (CLibrary::KeyboardPress(DIK_W) && CLibrary::KeyboardPress(DIK_D))
	{
		// 移動量・角度の設定
		Inertia.x = +sinf((fAngle + D3DXToRadian(-45.0f)))*fSpeed;
		Inertia.z = -cosf((fAngle + D3DXToRadian(-45.0f)))*fSpeed;
		rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
		m_bMove[0] = true;
	}

	//左後ろに移動
	if (CLibrary::KeyboardPress(DIK_S) && CLibrary::KeyboardPress(DIK_A))
	{
		// 移動量・角度の設定
		Inertia.x = -sinf((fAngle + D3DXToRadian(-45.0f)))*fSpeed;
		Inertia.z = +cosf((fAngle + D3DXToRadian(-45.0f)))*fSpeed;
		rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
		m_bMove[0] = true;
	}

	//右後ろに移動
	if (CLibrary::KeyboardPress(DIK_S) && CLibrary::KeyboardPress(DIK_D))
	{
		// 移動量・角度の設定
		Inertia.x = -sinf((fAngle + D3DXToRadian(45.0f)))*fSpeed;
		Inertia.z = +cosf((fAngle + D3DXToRadian(45.0f)))*fSpeed;
		rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
		m_bMove[0] = true;
	}
	if (CLibrary::KeyboardPress(DIK_Z))
	{
		CParticlePop::Create(pos);
	}

	// 座標設定
	pPlayer->SetPos(pos);

	if (!m_bMove[0])
	{
		Inertia = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//if (pPlayer->GetState() == CPlayer::STATE_WALK)
		if (m_bMove[1])
		{
			// アニメーション設定
			SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
		}
	}
	else
	{
	//	if (pPlayer->GetState() == CPlayer::STATE_NORMAL)
		if (!m_bMove[1])
		{
			// アニメーション設定
			SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_WALK), 60);
		}
	}

	//角度補正
	while (fCameraRot - fAngle > D3DXToRadian(180))
	{
		fCameraRot -= D3DXToRadian(360);
	}

	while (fCameraRot - fAngle < D3DXToRadian(-180))
	{
		fCameraRot += D3DXToRadian(360);
	}

	//カメラの転換速度よりちょっと遅く向かせる
	fAngle += (fCameraRot - fAngle) * m_fAngleSpeed;
	pPlayer->SetAngle(fAngle);

	// 慣性
	D3DXVECTOR3 move = pPlayer->GetMove();
	move += (Inertia - move) * pPlayer->GetInertiaNum();

	pPlayer->SetMove(move);
	pPlayer->SetRotDest(rotDest);
}