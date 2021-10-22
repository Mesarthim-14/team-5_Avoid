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
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "fade.h"
#include "resource_manager.h"
#include "motion.h"
#include "library.h"
#include "camera.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define PLAYER_SPEED			(10.0f)									// プレイヤーの移動量
#define PLAYER_ROT_SPEED		(0.1f)									// キャラクターの回転する速度
#define SIZE					(D3DXVECTOR3 (1200.0f,1000.0f,1200.0f))	// サイズ
#define PLAYER_INERTIA			(0.08f)		// 慣性の大きさ
#define PLAYER_LITTLESIZE_VALUE (10)									// 最小サイズモデルの値
#define PLAYER_MIDLLESIZE_VALUE (50)									// 中サイズモデルの値
#define PLAYER_LARGESIZE_VALUE  (100)									// 最大サイズモデルの値
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
	m_SlimeState = SLIME_MIDDLESIZE;
	m_nHP = 50;
	m_fAngle = 0.0f;
	m_ActionState = ACTION_NONE;
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
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_TEST);	// モデルの生成
	//	SetShadowRotCalculation();						// 影の向き
	}

	// 初期化処理
	CCharacter::Init();

	// 初期化
	m_rotDest = GetRot();			// 向き
	SetSize(SIZE);					// サイズ設定
	SetType(CHARACTER_TYPE_PLAYER);	// プレイヤー
	LoadInfo();
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();
}

//=============================================================================
// 更新関数処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Update(void)
{
	// 更新
	CCharacter::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 古い位置設定
	SetPosOld(pos);

	// 状態更新
	UpdateState();

	// プレイヤー処理
	PlayerControl();

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

	// ジャンプ
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		Jump();
	}
	//回避
	if (pKeyboard->GetTrigger(DIK_LSHIFT))
	{
		Avoidance();
	}
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
	}
	else
	{
		m_bMove = false;
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
}

//=============================================================================
// スライムモデルチェンジ
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::ChangeModel(void)
{
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
}

//=============================================================================
// ジャンプ
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::Jump(void)
{
	if (m_ActionState != ACTION_JUMP)
	{
		//状態をジャンプ状態
		m_ActionState = ACTION_JUMP;
	}
}

//=============================================================================
// 回避
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::Avoidance(void)
{
	if (m_ActionState != ACTION_AVOID)
	{
		//状態を回避状態
		m_ActionState = ACTION_AVOID;
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

			// HP
			ImGui::Text("HP : %d", m_nHP);

			// 移動量
			float fSpeed = GetSpeed();
			ImGui::SliderFloat("Speed", &fSpeed, 0.0f, 50.0f);
			SetSpeed(fSpeed);

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
}

//=============================================================================
// ライフ減少
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::SubLife(int nDamage)
{
	m_nHP -= nDamage;
}
