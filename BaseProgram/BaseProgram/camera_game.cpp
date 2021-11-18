//=============================================================================
//
// ゲームカメラの処理 [camera_game.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera_game.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "game.h"
#include "library.h"
#include "state_camera_normal.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_CAMERA_DEFAULT_Fθ		(D3DXToRadian(55.0f))	// カメラのθDefault値
#define GAME_CAMERA_DEFAULT_Hθ		(D3DXToRadian(0.0f))	// カメラ角度横
#define PLAYER_HEIGHT				(0.0f)					// 注視点の高さ
#define GAME_CAMERA_DISTANCE		(2500.0f)				// 距離

//=============================================================================
// コンストラクタ
//=============================================================================
CCameraGame::CCameraGame()
{
	m_pCurrentState = nullptr;
	m_pNextState = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCameraGame::~CCameraGame()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CCameraGame * CCameraGame::Create()
{
	// メモリ確保
	CCameraGame *pCamera = new CCameraGame;

	if (pCamera)
	{
		// 初期化処理
		pCamera->Init();
		return pCamera;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCameraGame::Init()
{
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, PLAYER_HEIGHT, 0.0f);
	D3DXVECTOR3 posV = ZeroVector3;
	float fDistance = GAME_CAMERA_DISTANCE;
	float fVartical = GAME_CAMERA_DEFAULT_Fθ;
	float fHorizontal = GAME_CAMERA_DEFAULT_Hθ;

	SetDistance(fDistance);
	SetVartical(fVartical);
	SetHorizontal(fHorizontal);					// 初期値敵のほう向ける
	GetposR() = posR;
	GetposU() = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 上方向ベクトル

	posV.x = posR.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// カメラ位置X
	posV.y = posR.z + fDistance * cosf(fVartical);						// カメラ位置Y
	posV.z = posR.y + fDistance * sinf(fVartical) * cosf(fHorizontal);	// カメラ位置Z

	GetposV() = posV;

	// 初期化処理
	CCamera::Init();

	if (!m_pCurrentState)
	{
		// インスタンス生成
		m_pCurrentState = CCameraStateNormal::Create();
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CCameraGame::Update()
{
	StateUpdate();
}

//=============================================================================
// 状態更新処理
//=============================================================================
void CCameraGame::StateUpdate()
{
	// 入れ替え
	if (m_pNextState)
	{
		if (m_pCurrentState)
		{
			delete m_pCurrentState;
			m_pCurrentState = nullptr;
		}

		m_pCurrentState = m_pNextState;
		m_pNextState = nullptr;
	}

	if (m_pCurrentState)
	{
		m_pCurrentState->Update();
	}
}