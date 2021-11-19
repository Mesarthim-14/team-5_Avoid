//=============================================================================
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "mouse.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "fade.h"
#include "resource_manager.h"
#include "motion.h"
#include "library.h"
#include "camera.h"
#include "game.h"
#include "test_model.h"
#include "model.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "collisionModel.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define PLAYER_SPEED			(10.0f)									// プレイヤーの移動量
#define PLAYER_ROT_SPEED		(0.1f)									// キャラクターの回転する速度
#define SIZE					(D3DXVECTOR3 (250.0f,500.0f,250.0f))	// サイズ
#define PLAYER_INERTIA			(0.08f)		// 慣性の大きさ
#define PLAYER_LITTLESIZE_VALUE (10)									// 最小サイズモデルの値
#define PLAYER_MIDLLESIZE_VALUE (50)									// 中サイズモデルの値
#define PLAYER_LARGESIZE_VALUE  (100)									// 最大サイズモデルの値
#define CHARGEJUMP_COUNT_MAX (10)										// タメ判定用カウント
#define CHARGEJUMP_MAX (100)												// タメカウント最大
#define AVOID_CONSUME (1)												// 回避した時のライフ減少量
#define HIGHJUMP_CONSUME (1)												// ためジャンプした時のライフ減少量
//=============================================================================
// 生成処理関数
// Author : Konishi Yuuto
//=============================================================================
CPlayer * CPlayer::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	// メモリ確保
	CPlayer *pPlayer = new CPlayer;

	// nullcheck
	if (pPlayer)
	{
		// 初期化処理
		pPlayer->SetCharacterInfo(pos, rot);
		pPlayer->Init();
		return pPlayer;
	}

	// CPlayerを返す
	return nullptr;
}

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
	m_Inertia = ZeroVector3;
	m_fInertiaNum = 0.0f;
	m_fRotationSpeed = 0.1f;
	m_fAngleSpeed = 0.0f;
	m_SlimeState = SLIME_LARGESIZE;
	m_nHP = 60;
	m_fAngle = 0.0f;
	m_ActionState = ACTION_NONE;
	m_fJumpValue = 0.0f;
	m_fDushJumpValue = 0.0f;
	m_nChargeJumpCount = 0;
	m_bIsReadyChargeJump = false;
	m_fAvoidValueY = 30.0f;
	m_fAvoidValueXZ = 5.0f;
	for (int nCount = 0; nCount < SLIME_STATE_MAX; nCount++)
	{
		m_pSkinmeshModel[nCount] = nullptr;
	}
	m_fJumpTimeCount = 0;
	m_fJumpCheck = false;

	m_pCollisionModel = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Konishi Yuuto
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CPlayer::Init(void)
{
	// CXfile取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// nullcheck
	if (pXfile)
	{
		SetUseShadow();									// 影の使用
		//ModelCreate(CXfile::HIERARCHY_XFILE_NUM_TEST);	// モデルの生成
	//	SetShadowRotCalculation();						// 影の向き
	}
	//三つ分モデル出して現在のサイズモデルだけ描画させる
	for (int nCount = 0; nCount < SLIME_STATE_MAX; nCount++)
	{
		m_pSkinmeshModel[nCount] = CSkinmeshModel::Create(GetPos(), GetRot(), CSkinmeshModel::MODEL(nCount));
		if (int(m_SlimeState) != nCount)
		{
			m_pSkinmeshModel[nCount]->IsDraw(false);
		}
		else
		{
			m_pSkinmeshModel[nCount]->IsDraw(true);
		}
	}

	m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->ChangeAnimation(0);
	m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetLoopTime(0, 60);
	m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetShiftTime(0, 60);

	// 初期化処理
	CCharacter::Init();

	// 初期化
	m_rotDest = GetRot();			// 向き
	//SetSize(SIZE);					// サイズ設定
	SetType(CHARACTER_TYPE_PLAYER);	// プレイヤー
	LoadInfo();

	//当たり判定モデルの生成
	if (m_pCollisionModel == nullptr)
	{
		m_pCollisionModel = CCollisionModel::Create(GetPos(), SIZE, GetRot(), CCollisionModel::TYPE_BOX);
	}

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Uninit(void)
{
#ifdef _DEBUG
	//情報保存
	SaveInfo();
#endif // !_DEBUG
	CCharacter::Uninit();
}

//=============================================================================
// 更新関数処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Update(void)
{
	// プレイヤー処理
	PlayerControl();

	// 更新
	CCharacter::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 古い位置設定
	SetPosOld(pos);

	// 状態更新
	UpdateState();

	// モデル変更
	ChangeModel();

	//モデル位置向き反映(いずれcharacterに移動させたい）
	m_pSkinmeshModel[m_SlimeState]->SetPos(GetPos());
	m_pSkinmeshModel[m_SlimeState]->SetRot(GetRot());

	// 更新処理
	UpdateRot();

#ifdef _DEBUG
	//情報確認
	ShowInfo();
#endif // !_DEBUG
}

//=============================================================================
// 描画処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画
	CCharacter::Draw();
}

//=============================================================================
// 状態更新
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::UpdateState(void)
{
	// アニメーション制御
	AnimationProcess();
}

//=============================================================================
// プレイヤーの処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PlayerControl(void)
{
	// 移動
	Move();
	// アクション
	Action();

	//当たり判定の位置の設定
	if (m_pCollisionModel != nullptr)
	{
		m_pCollisionModel->SetPos(GetPos());
	}
}

//=============================================================================
// 移動処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Move(void)
{
	// キーボード移動
	KeyBoardMove();
}

//=============================================================================
// アクション処理
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::Action(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// キーボード更新

	if (GetLanding() == true && GetState() == STATE_JUMP)//ジャンプ終了
	{
		SetState(STATE_NORMAL);
		m_fJumpTimeCount = 0;
	}
	if (GetLanding() == true && GetState() == STATE_AVOID)//ジャンプ終了
	{
		SetState(STATE_NORMAL);
	}

	// ジャンプ
	Jump();

	// 回避
	Avoidance();
}

//=============================================================================
// 移動処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::KeyBoardMove(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// キーボード更新
	D3DXVECTOR3 pos = GetPos();								// 座標
	D3DXVECTOR3 rot = GetRot();								// 角度
	float fSpeed = GetSpeed();								// 移動量
	float fCameraRot = D3DXToRadian(CManager::GetCamera()->GetRot().y);	// カメラの角度

	// 前に移動
	if (pKeyboard->GetPress(DIK_W))
	{
		// 移動量・角度の設定
		m_Inertia.x = +sinf(m_fAngle)*fSpeed;
		m_Inertia.z = -cosf(m_fAngle)*fSpeed;
		//進行方向に向きを合わせる
		m_rotDest.y = atan2f(m_Inertia.x, m_Inertia.z) + D3DXToRadian(180.0f);
		m_bMove = true;
	}

	// 後ろに移動
	if (pKeyboard->GetPress(DIK_S))
	{
		// 移動量・角度の設定
		m_Inertia.x = -sinf((m_fAngle))*fSpeed;
		m_Inertia.z = +cosf((m_fAngle))*fSpeed;
		//進行方向に向きを合わせる
		m_rotDest.y = atan2f(m_Inertia.x, m_Inertia.z) + D3DXToRadian(-180.0f);
		m_bMove = true;
	}

	// 左に移動
	if (pKeyboard->GetPress(DIK_A))
	{
		// 移動量・角度の設定
		m_Inertia.x = +sinf((m_fAngle + D3DXToRadian(90.0f)))*fSpeed;
		m_Inertia.z = -cosf((m_fAngle + D3DXToRadian(90.0f)))*fSpeed;

		//進行方向に向きを合わせる
		m_rotDest.y = atan2f(m_Inertia.x, m_Inertia.z) + D3DXToRadian(180.0f);
		m_bMove = true;
	}

	// 右に移動
	if (pKeyboard->GetPress(DIK_D))
	{
		// 移動量・角度の設定
		m_Inertia.x = +sinf((m_fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		m_Inertia.z = -cosf((m_fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		//進行方向に向きを合わせる
		m_rotDest.y = atan2f(m_Inertia.x, m_Inertia.z) + D3DXToRadian(-180.0f);
		m_bMove = true;
	}

	//左前に移動
	if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_A))
	{
		// 移動量・角度の設定
		m_Inertia.x = +sinf((m_fAngle + D3DXToRadian(45.0f)))*fSpeed;
		m_Inertia.z = -cosf((m_fAngle + D3DXToRadian(45.0f)))*fSpeed;
		m_rotDest.y = atan2f(m_Inertia.x, m_Inertia.z) + D3DXToRadian(180.0f);
		m_bMove = true;
	}

	//右前に移動
	if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_D))
	{
		// 移動量・角度の設定
		m_Inertia.x = +sinf((m_fAngle + D3DXToRadian(-45.0f)))*fSpeed;
		m_Inertia.z = -cosf((m_fAngle + D3DXToRadian(-45.0f)))*fSpeed;
		m_rotDest.y = atan2f(m_Inertia.x, m_Inertia.z) + D3DXToRadian(180.0f);
		m_bMove = true;
	}

	//左後ろに移動
	if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_A))
	{
		// 移動量・角度の設定
		m_Inertia.x = -sinf((m_fAngle + D3DXToRadian(-45.0f)))*fSpeed;
		m_Inertia.z = +cosf((m_fAngle + D3DXToRadian(-45.0f)))*fSpeed;
		m_rotDest.y = atan2f(m_Inertia.x, m_Inertia.z) + D3DXToRadian(180.0f);
		m_bMove = true;
	}

	//右後ろに移動
    if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_D))
	{
		// 移動量・角度の設定
		m_Inertia.x = -sinf((m_fAngle + D3DXToRadian(45.0f)))*fSpeed;
		m_Inertia.z = +cosf((m_fAngle + D3DXToRadian(45.0f)))*fSpeed;
		m_rotDest.y = atan2f(m_Inertia.x, m_Inertia.z) + D3DXToRadian(180.0f);
		m_bMove = true;
	}

	// 座標設定
	SetPos(pos);

	if(!m_bMove)
	{
		m_Inertia = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		if (GetState() == STATE_WALK)
		{
			SetState(STATE_NORMAL);
		}
	}
	else
	{
		m_bMove = false;
		if (GetState() == STATE_NORMAL)
		{
			SetState(STATE_WALK);
		}
	}

	//角度補正
	while (fCameraRot - m_fAngle > D3DXToRadian(180))
	{
		fCameraRot -= D3DXToRadian(360);
	}

	while (fCameraRot - m_fAngle < D3DXToRadian(-180))
	{
		fCameraRot += D3DXToRadian(360);
	}

	//カメラの転換速度よりちょっと遅く向かせる
	m_fAngle += (fCameraRot - m_fAngle) * m_fAngleSpeed;

	// 慣性
	D3DXVECTOR3 move = GetMove();
	move += (m_Inertia - move) * m_fInertiaNum;

	SetMove(move);
}

//=============================================================================
// 更新処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::UpdateRot(void)
{
	// 角度の取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	rot += (m_rotDest - rot) * m_fRotationSpeed;

	// 角度の更新処理
	CLibrary::RotFix(rot.y);

	// 角度の設定
	SetRot(rot);

	//当たり判定の角度の設定
	if (m_pCollisionModel != nullptr)
	{
		m_pCollisionModel->SetRot(rot);
	}
}

//=============================================================================
// スライムモデルチェンジ
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::ChangeModel(void)
{
	SLIME_STATE OldState = m_SlimeState; //前回の状態を保存

	//現在のライフを見てスライムの見た目を変える
	if (m_nHP == PLAYER_LARGESIZE_VALUE)//最大
	{
		//スライムの状態を最大に
		m_SlimeState = SLIME_LARGESIZE;

	}
	else if (m_nHP < PLAYER_LARGESIZE_VALUE && m_nHP >= PLAYER_MIDLLESIZE_VALUE)//中くらい
	{
		//スライムの状態を中に
		m_SlimeState = SLIME_MIDDLESIZE;
		//HP量で大きさ変える
	}
	else if (m_nHP < PLAYER_MIDLLESIZE_VALUE && m_nHP >= 0)//小
	{
		//スライムの状態を最小に
		m_SlimeState = SLIME_LITTLESIZE;
		//HP量で大きさ変える
	}

	if (m_SlimeState != OldState)
	{
		//モデル変更
		for (int nCount = 0; nCount < SLIME_STATE_MAX; nCount++)
		{
			if (int(m_SlimeState) != nCount)
			{
				m_pSkinmeshModel[nCount]->IsDraw(false);
			}
			else
			{
				m_pSkinmeshModel[nCount]->IsDraw(true);
			}
		}
	}
}

//=============================================================================
// ジャンプ
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::Jump(void)
{
	D3DXVECTOR3 move = GetMove();
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// キーボード更新

	//ジャンプ中の処理
	//JumpProcess();

	// ためジャンプ
	if (pKeyboard->GetPress(DIK_SPACE))
	{
   		m_nChargeJumpCount++;
		if (GetLanding() == true && GetState() != STATE_JUMP && m_nChargeJumpCount >= CHARGEJUMP_COUNT_MAX)//こっからタメジャンプ判定スタート
		{
			//エフェクト発生
			if (m_nChargeJumpCount >= CHARGEJUMP_MAX)
			{
				m_bIsReadyChargeJump = true;
				SetLanding(false);
			}
		}
	}

	if (pKeyboard->GetRelease(DIK_SPACE) && m_bIsReadyChargeJump == true)//ため状態で離したら
	{
		m_fJumpCheck = true;
		move.y += m_fJumpValue * 3;
		move.x += move.x * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
		move.z += move.z * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
		SetState(STATE_JUMP);
		SetMove(move);
		m_nChargeJumpCount = 0;
		m_bIsReadyChargeJump = false;

		// Hp消費
		if (m_nHP != 0)
		{
			SubLife(HIGHJUMP_CONSUME);
		}
	}

	else if (GetLanding() == true && pKeyboard->GetRelease(DIK_SPACE) && GetState() != STATE_JUMP)//通常ジャンプ
	{
		m_fJumpCheck = true;
		move.y += m_fJumpValue;
		move.x += move.x * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
		move.z += move.z * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
		//m_fJumpTimeCount += 1.0f;
		//move.y = 0.5f * CGame::GetGravity()*m_fJumpTimeCount*m_fJumpTimeCount + m_fJumpValue*m_fJumpTimeCount;
		SetState(STATE_JUMP);
		SetMove(move);
		m_nChargeJumpCount = 0;
 		SetLanding(false);
	}
}

void CPlayer::JumpProcess(void)
{
	D3DXVECTOR3 move = GetMove();

	if (GetState() == STATE_JUMP)
	{
		if (m_fJumpTimeCount <= 2)
		{
			m_fJumpTimeCount += 1.0f;
			move.y = 0.5f * CGame::GetGravity()*m_fJumpTimeCount*m_fJumpTimeCount + m_fJumpValue*m_fJumpTimeCount;
		}
		else
		{

		}

		SetMove(move);
	}
}

//=============================================================================
// アニメーション処理
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::AnimationProcess(void)
{
	switch (GetState())
	{
	case STATE_NORMAL:
		m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->ChangeAnimation(1);
		m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetLoopTime(1,60);
		/*m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetShiftTime(2, 60);*/
		break;
	case STATE_WALK:
		m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->ChangeAnimation(0);
		m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetLoopTime(0, 60);
		/*m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetShiftTime(1, 60);*/
		break;
	case STATE_JUMP:
		m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->ChangeAnimation(0);
		m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetLoopTime(0, 60);
		/*m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetShiftTime(0, 60);*/
		break;
	case STATE_AVOID:
		break;
	default:
		break;
	}
}

//=============================================================================
// 回避
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::Avoidance(void)
{
	D3DXVECTOR3 move = GetMove();
	CMouse *pMouse = CManager::GetMouse();	// キーボード更新
	if (GetLanding() == true && pMouse->GetButtonTrigger(CMouse::MOUSE_LEFT) && GetState() != STATE_AVOID)//回避
	{
		move.y += m_fAvoidValueY;
		move.x += move.x * (m_fAvoidValueXZ * tanf(move.y / m_fAvoidValueY));
		move.z += move.z * (m_fAvoidValueXZ * tanf(move.y / m_fAvoidValueY));
		SetState(STATE_AVOID);
		SetMove(move);

		// Hp消費
		if (m_nHP != 0)
		{
			SubLife(AVOID_CONSUME);
		}
	}
}

//=============================================================================
// Imgui 情報
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::ShowInfo(void)
{
#ifdef _DEBUG

	//レンダラーで管理してるやつの情報
	ImGui::Begin("DebugInfo");

	if (ImGui::CollapsingHeader("PlayerInfo"))
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

		if (ImGui::TreeNode("Player"))
		{
			// 移動量
			D3DXVECTOR3 pos = GetPos();
			ImGui::Text("Pos : %.1ff %.1ff %.1ff", pos.x, pos.y, pos.z);

			// 移動量
			D3DXVECTOR3 rot = GetRot();
			ImGui::Text("Rot : %.1ff %.1ff %.1ff", rot.x, rot.y, rot.z);

			// 移動量
			D3DXVECTOR3 move = GetMove();
			ImGui::Text("Move : %.1ff %.1ff %.1ff", move.x, move.y, move.z);

			// 状態
			ImGui::Text("STATE : %d", GetState());

			// 状態
			ImGui::Text("SLIME_SIZE : %d", m_SlimeState);

			// ジャンプ時間
			ImGui::Text("JUMP_TIME : %.1f", m_fJumpTimeCount);

			// 移動量
			float fSpeed = GetSpeed();
			ImGui::SliderFloat("Speed", &fSpeed, 0.0f, 50.0f);
			SetSpeed(fSpeed);

			// ライフの値
			ImGui::SliderInt("HP", &m_nHP, 0, 100);

			// ジャンプの値
			ImGui::SliderFloat("JumpValue", &m_fJumpValue, 0.0f, 200.0f);

			// ダッシュジャンプの値
			ImGui::SliderFloat("DushJumpValue", &m_fDushJumpValue, 0.0f, 50.0f);

			// 慣性の値
			ImGui::SliderFloat("InertiaNum", &m_fInertiaNum, 0.0f, 0.5f);

			// 目的の角度の値
			ImGui::SliderFloat("rotDest", &m_rotDest.y, D3DXToRadian(-180), D3DXToRadian(180));

			// 回転速度の値
			ImGui::SliderFloat("RotationSpeed", &m_fRotationSpeed, 0.0f, 1.0f);

			// 目標向きに向かうまでの速度の値
			ImGui::SliderFloat("AngleSpeed", &m_fAngleSpeed, 0.0f, 1.0f);

			ImGui::TreePop();
		}
	}

	ImGui::End();
#endif // !_DEBUG
}

//=============================================================================
// データロード
// Author : Konishi Yuuto
//=============================================================================
HRESULT CPlayer::LoadInfo(void)
{
	// ファイルデータ取得
	picojson::value& v = CLibrary::JsonLoadFile("data/Text/json/test.json");

	// ステータス取得
	CLibrary::JsonGetState(v, "Player", "SPEED", GetSpeed());
	CLibrary::JsonGetState(v, "Player", "INERTIA_NUM", m_fInertiaNum);
	CLibrary::JsonGetState(v, "Player", "ROTATION_SPEED", m_fRotationSpeed);
	CLibrary::JsonGetState(v, "Player", "ANGLE_SPEED", m_fAngleSpeed);
	CLibrary::JsonGetState(v, "Player", "JUMP_VALUE", m_fJumpValue);
	CLibrary::JsonGetState(v, "Player", "DUSH_JUMP_VALUE", m_fDushJumpValue);
	return S_OK;
}

//=============================================================================
// データセーブ
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::SaveInfo(void)
{
	string FileName = "data/Text/json/test.json";

	// ファイルデータ取得
	CLibrary::JsonSetState(FileName, "Player", "SPEED", GetSpeed());				// 速度
	CLibrary::JsonSetState(FileName, "Player", "INERTIA_NUM", m_fInertiaNum);		// 慣性
	CLibrary::JsonSetState(FileName, "Player", "ROTATION_SPEED", m_fRotationSpeed);	// 回転の速度
	CLibrary::JsonSetState(FileName, "Player", "ANGLE_SPEED", m_fAngleSpeed);	// 回転遅さの速度
	CLibrary::JsonSetState(FileName, "Player", "JUMP_VALUE", m_fJumpValue);	// 回転遅さの速度
	CLibrary::JsonSetState(FileName, "Player", "DUSH_JUMP_VALUE", m_fDushJumpValue);	// 回転遅さの速度
}

//=============================================================================
// ライフ減少
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::SubLife(int nDamage)
{
	if (m_nHP > 0)
	{
		m_nHP -= nDamage;
	}
}
