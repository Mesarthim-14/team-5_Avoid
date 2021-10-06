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
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "motion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_CAMERA_DEFAULT_Fθ		(D3DXToRadian(60.0f))	// カメラのθDefault値
#define GAME_CAMERA_DEFAULT_Hθ		(D3DXToRadian(95.0f))	// カメラ角度横
#define PLAYER_HEIGHT				(0.0f)					// 注視点の高さ
#define GAME_CAMERA_DISTANCE		(2500.0f)				// 距離
#define CAMERA_MIN_HIGHT			(2.0f)					// カメラの最低高度

//=============================================================================
// インスタンス生成
//=============================================================================
CCameraGame * CCameraGame::Create(void)
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
// コンストラクタ
//=============================================================================
CCameraGame::CCameraGame()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CCameraGame::~CCameraGame()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCameraGame::Init(void)
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

	return S_OK;
}

//=============================================================================
// 通常状態の更新処理
//=============================================================================
void CCameraGame::NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot)
{
	//キーボードクラス情報の取得
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();

	// ジョイパッドの取得
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	// 角度の取得
	float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// コントローラの角度
	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// コントローラの角度
	float fAngle = GetHorizontal();							// カメラの角度

	// カメラ座標
	D3DXVECTOR3 VDest = ZeroVector3;
	D3DXVECTOR3 posRDest = GetposRDest();
	float fDistance = GetDistance();
	float fVartical = GetVartical();

	// カメラの位置設定
	VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(PlayerRot.y);	// カメラ位置X設定
	VDest.y = PlayerPos.y + PLAYER_HEIGHT + fDistance * cosf(fVartical);		// カメラ位置Y設定
	VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(PlayerRot.y);	// カメラ位置Z設定

	posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);	//注視点設定

	//カメラPOSYの下限
	if (VDest.y <= CAMERA_MIN_HIGHT)
	{
		VDest.y = CAMERA_MIN_HIGHT;	//限界値に戻す
	}

	//設定値の反映
	GetposV() += (VDest - GetposV())*0.1f;
	GetposR() += (posRDest - GetposR())*0.9f;
}