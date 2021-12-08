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
#include "collisionModel_OBB.h"
#include "collisionModel_Capsule.h"
#include "check_point.h"
#include "gimmick_factory.h"
#include "state_player.h"
#include "state_player_avoid.h"
#include "state_player_jump.h"
#include "state_player_normal.h"
#include "gauge.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define PLAYER_SPEED			(10.0f)									// プレイヤーの移動量
#define PLAYER_ROT_SPEED		(0.1f)									// キャラクターの回転する速度

#define OBB_COLLISION_SIZE_100  (D3DXVECTOR3(300.0f,600.0f,300.0f)) // 直方体当たり判定(100%)の大きさ
#define OBB_COLLISION_SIZE_50   (D3DXVECTOR3(150.0f,300.0f,200.0f)) // 直方体当たり判定(50%)の大きさ
#define OBB_COLLISION_SIZE_0    (D3DXVECTOR3(50.0f,150.0f,100.0f))  // 直方体当たり判定(0%)の大きさ

#define CAPSULE_COLLISION_RADIUS_100    (150.0f)  // カプセル当たり判定(100%)の円の半径
#define CAPSULE_COLLISION_LENGTH_100    (600.0f)  // カプセル当たり判定(100%)の長さ
#define CAPSULE_COLLISION_RADIUS_50     (75.0f)   // カプセル当たり判定(50%)の円の半径
#define CAPSULE_COLLISION_LENGTH_50     (300.0f)  // カプセル当たり判定(50%)の長さ
#define CAPSULE_COLLISION_RADIUS_0      (25.0f)   // カプセル当たり判定(0%)の円の半径
#define CAPSULE_COLLISION_LENGTH_0      (150.0f)  // カプセル当たり判定(0%)の長さ

#define PLAYER_INERTIA			(0.08f)									// 慣性の大きさ
#define PLAYER_LITTLESIZE_VALUE (10)									// 最小サイズモデルの値
#define PLAYER_MIDLLESIZE_VALUE (50)									// 中サイズモデルの値
#define PLAYER_LARGESIZE_VALUE  (100)									// 最大サイズモデルの値

#define RESPORN_POS_Y			(-3000.0f)								// リスポーンの値

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
	for (int nCount = 0; nCount < SLIME_STATE_MAX; nCount++)
	{
		m_pSkinmeshModel[nCount] = nullptr;
	}
	memset(m_nMaxAction, 0, sizeof(m_nMaxAction));
	m_pCurrentState = nullptr;
	m_pNextState = nullptr;

	m_pColModelOBB = nullptr;
    m_pColModelCapsule = nullptr;
    m_bCollision = true;
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
HRESULT CPlayer::Init()
{
	// モデル生成
	CreateModel();

	// 初期化処理
	CCharacter::Init();

	// 初期化
	m_rotDest = GetRot();			// 向き

	SetType(CHARACTER_TYPE_PLAYER);	// プレイヤー

	if (!m_pCurrentState)
	{
		// インスタンス生成
		m_pCurrentState = CPlayerStateNormal::Create();
	}

	LoadInfo();

	//当たり判定モデル(直方体)の生成
	if (!m_pColModelOBB)
	{
		m_pColModelOBB = CCollisionModelOBB::Create(GetPos(), OBB_COLLISION_SIZE_100, GetRot());
	}

    //当たり判定モデル(カプセル)の生成
    if (!m_pColModelCapsule)
    {
        m_pColModelCapsule = CCollisionModelCapsule::Create(GetPos(), CAPSULE_COLLISION_RADIUS_100, CAPSULE_COLLISION_LENGTH_100, GetRot());
    }

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Uninit()
{
#ifdef _DEBUG
	//情報保存

//	SaveInfo();
#endif // !_DEBUG
	CCharacter::Uninit();
}

//=============================================================================
// 更新関数処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Update()
{
	{
		// 位置取得
		D3DXVECTOR3 pos = GetPos();

		// 古い位置設定
		SetPosOld(pos);
	}

	// 状態更新
	UpdateState();

	CCharacter::Update();

	// リスポーン
	ReSporn();

	//モデル位置向き反映(いずれcharacterに移動させたい）
	m_pSkinmeshModel[m_SlimeState]->SetPos(GetPos());
	m_pSkinmeshModel[m_SlimeState]->SetRot(GetRot());

	// 更新処理
	UpdateRot();

    // 当たり判定モデル情報の更新処理
	if (m_pColModelOBB)
	{
        m_pColModelOBB->SetInfo(GetPos(), m_pColModelOBB->GetInfo().size, GetRot());
	}
    if (m_pColModelCapsule)
    {
        m_pColModelCapsule->SetInfo(GetPos(), m_pColModelCapsule->GetInfo().radius, m_pColModelCapsule->GetInfo().length, GetRot());
    }

	ShowInfo();
}

//=============================================================================
// 描画処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Draw()
{
	// 描画
	CCharacter::Draw();
}

//=============================================================================
// 現在のスキンメッシュポインタ
// Author : Konishi Yuuto
//=============================================================================
CSkinmeshModel *CPlayer::GetCurrentSkinMeshPtr()
{
	if (m_pSkinmeshModel[m_SlimeState])
	{
		return m_pSkinmeshModel[m_SlimeState];
	}

	return nullptr;
}

//=============================================================================
// 状態の変更
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::ChangeState(CState *pPlayerState)
{
	m_pNextState = pPlayerState;
}

//=============================================================================
// 状態更新
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::UpdateState()
{
	if (m_pNextState)
	{
		delete m_pCurrentState;
		m_pCurrentState = nullptr;

		m_pCurrentState = m_pNextState;
		m_pNextState = nullptr;
	}

	if (m_pCurrentState)
	{
		// 更新処理
		m_pCurrentState->Update();
	}
}

//=============================================================================
// 更新処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::UpdateRot()
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
void CPlayer::ChangeModel()
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
// Imgui 情報
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::ShowInfo()
{
#ifdef _DEBUG

	//レンダラーで管理してるやつの情報
	ImGui::Begin("DebugInfo");

	if (ImGui::CollapsingHeader("PlayerInfo"))
	{

		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

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


			// 移動量
			float fSpeed = GetSpeed();
			ImGui::SliderFloat("Speed", &fSpeed, 0.0f, 50.0f);
			SetSpeed(fSpeed);

			// ライフの値
			ImGui::SliderInt("HP", &m_nHP, 0, 100);


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

	CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();	// キーボード更新

	if (pKeyboard->GetTrigger(DIK_7))
	{
		SaveInfo();
	}
#endif // !_DEBUG
}

//=============================================================================
// データロード
// Author : Konishi Yuuto
//=============================================================================
HRESULT CPlayer::LoadInfo()
{
	// ファイルデータ取得
	picojson::value& v = CLibrary::JsonLoadFile("data/Text/json/test.json");

	// ステータス取得
	CLibrary::JsonGetState(v, "Player", "SPEED", GetSpeed());
	CLibrary::JsonGetState(v, "Player", "INERTIA_NUM", m_fInertiaNum);
	CLibrary::JsonGetState(v, "Player", "ROTATION_SPEED", m_fRotationSpeed);
	CLibrary::JsonGetState(v, "Player", "ANGLE_SPEED", m_fAngleSpeed);

	return S_OK;
}

//=============================================================================
// データセーブ
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::SaveInfo()
{
	string FileName = "data/Text/json/test.json";

	// ファイルデータ取得
	CLibrary::JsonSetState(FileName, "Player", "SPEED", GetSpeed());				// 速度
	CLibrary::JsonSetState(FileName, "Player", "INERTIA_NUM", m_fInertiaNum);		// 慣性
	CLibrary::JsonSetState(FileName, "Player", "ROTATION_SPEED", m_fRotationSpeed);	// 回転の速度
	CLibrary::JsonSetState(FileName, "Player", "ANGLE_SPEED", m_fAngleSpeed);	// 回転遅さの速度

}

//=============================================================================
// ライフ減少
// Author : Hayashikawa Sarina
//=============================================================================
void CPlayer::SubLife(const int &nDamage)
{
	if (m_nHP > 0)
	{
		m_nHP -= nDamage;

		if (m_nHP < 0)
		{
			m_nHP = 0;
		}
		else
		{
            if (m_nHP > 100)
            {
                m_nHP = 100;
            }
		}
        ChangeModel();
	}
}

//=============================================================================
// リスポーン
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::ReSporn()
{
	// 一定以下の座標になったら
	if (RESPORN_POS_Y > GetPos().y)
	{
		CGame* pGame = (CGame*)CManager::GetInstance()->GetModePtr();
		if (pGame)
		{
			// 座標の取得
			SetPos(pGame->GetGimmickFactory()->GetCheckPoint()->GetPointPos());
			SetMove(ZeroVector3);
            ChangeState(CPlayerStateNormal::Create());
		}
	}
}

//=============================================================================
// モデル生成関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::CreateModel()
{
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

		SetAction(nCount, m_pSkinmeshModel[nCount]->MaxAction());
	}

	m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->ChangeAnimation(0);
	m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetLoopTime(0, 60);
	m_pSkinmeshModel[m_SlimeState]->GetHLcontroller()->SetShiftTime(0, 60);
}