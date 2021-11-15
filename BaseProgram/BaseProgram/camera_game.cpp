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
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_CAMERA_DEFAULT_Fθ		(D3DXToRadian(55.0f))	// カメラのθDefault値
#define GAME_CAMERA_DEFAULT_Hθ		(D3DXToRadian(0.0f))	// カメラ角度横
#define PLAYER_HEIGHT				(0.0f)					// 注視点の高さ
#define GAME_CAMERA_DISTANCE		(2500.0f)				// 距離
#define CAMERA_MIN_HIGHT			(2.0f)					// カメラの最低高度
#define INPUT_CONVERSION			(D3DXToRadian(1.0f))	// スティック入力変化量

#define CAMERA_DISTANCE			(2000.0f)//プレイヤーとカメラの距離
#define PLAYER_CAMERA_HEIGHT	(300.0f) //プレイヤーの高さ

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
void CCameraGame::NomalUpdate(void)
{
	// プレイヤー
	CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();

	// プレイヤーが使われていたら
	if (pPlayer)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();	//プレイヤー位置
		D3DXVECTOR3 PlayerRot = pPlayer->GetPos();	//プレイヤー位置

		// キーボードクラス情報の取得
		CInputKeyboard *pKeyInput = CManager::GetInstance()->GetKeyboard();

		// カメラ座標
		D3DXVECTOR3 VDest = ZeroVector3;
		D3DXVECTOR3 posRDest = GetposRDest();
		float fDistance = GetDistance();
		float fVartical = GetVartical();
		float fHorizontal = GetHorizontal();							// カメラの角度

		// 追従
		//Tracking(fDistance, fVartical, fHorizontal, PlayerPos, PlayerRot);

		// キーボード更新
		KeyBoardMove(fDistance, fVartical, fHorizontal, PlayerPos);
	}
}

//=============================================================================
// マウスの時の更新処理
// Author Hayashikawa Sarina
//=============================================================================
void CCameraGame::MouseUpdate(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();	// キーボード更新
	// プレイヤー
	CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
	D3DXVECTOR3 fRotateCenter; //カメラ回転の中心

	POINT point;
	GetCursorPos(&point);
	D3DXVECTOR3 CameraRot = CManager::GetInstance()->GetCamera()->GetRot();
	//if (CManager::GetIsActiveWindow() == true)//ウィンドウがアクティブならカーソルセット
	//{
	if (!pKeyboard->GetPress(DIK_LCONTROL))//LCONT押しているときはカーソル開放する
	{
		SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);              //マウス位置をリセット
		CameraRot.y -= (point.x - (SCREEN_WIDTH / 2))*(0.01f*15.0f);    //マウス位置を反映
		CameraRot.x += (point.y - (SCREEN_HEIGHT / 2))*(0.01f*15.0f);
	}

	//rot補正
	if (CameraRot.x >= 50)
	{
		CameraRot.x = 50;
	}
	else if (CameraRot.x <= -50)
	{
		CameraRot.x = -50;
	}

	//反転しないように
	if (CameraRot.y < 0)
	{
		CameraRot.y += 360;
	}
	if (CameraRot.y > 360)
	{
		CameraRot.y -= 360;
	}

	Setrot(CameraRot);

	if (pPlayer != NULL)
	{
		//カメラ回転の中心をプレイヤーの位置にする（少し上に）
		fRotateCenter = pPlayer->GetPos() + D3DXVECTOR3(0.0f, PLAYER_CAMERA_HEIGHT, 0.0f);
	}
	
	//カメラが地面を貫通してしまう場合地面に這わせるように
	if (fRotateCenter.y + sinf(D3DXToRadian(GetRot().x)) * CAMERA_DISTANCE > 0)
	{
		SetposV(fRotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-GetRot().y)) * cosf(D3DXToRadian(GetRot().x)) * CAMERA_DISTANCE, sinf(D3DXToRadian(GetRot().x)) * CAMERA_DISTANCE, cosf(D3DXToRadian(-GetRot().y)) * cosf(D3DXToRadian(GetRot().x)) * CAMERA_DISTANCE));
	}
	else
	{
		SetposV(fRotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-GetRot().y)) * cosf(D3DXToRadian(GetRot().x))* CAMERA_DISTANCE, -fRotateCenter.y + 1, cosf(D3DXToRadian(-GetRot().y)) * cosf(D3DXToRadian(GetRot().x))* CAMERA_DISTANCE));
	}

	//注視点を中心にあわせる
	SetposR(fRotateCenter);
}

//=============================================================================
// 追従処理
//=============================================================================
void CCameraGame::Tracking(const float &fDistance, float &fVartical,
	float &fHorizontal, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerRot)
{
	D3DXVECTOR3 VDest = ZeroVector3;
	D3DXVECTOR3 posRDest = ZeroVector3;

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

//=============================================================================
// キーボードの更新
//=============================================================================
void CCameraGame::KeyBoardMove(const float &fDistance, float &fVartical,
	float &fHorizontal, D3DXVECTOR3 PlayerPos)
{
	// プレイヤー
	CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();

	//キーボードクラス情報の取得
	CInputKeyboard *pKeyInput = CManager::GetInstance()->GetKeyboard();
	D3DXVECTOR3 VDest = ZeroVector3;

	//視点（カメラ座標）の左旋回
	if (pKeyInput->GetPress(DIK_LEFT))
	{
		fHorizontal += INPUT_CONVERSION;
	}
	//視点（カメラ座標）の右旋回
	if (pKeyInput->GetPress(DIK_RIGHT))
	{
		fHorizontal -= INPUT_CONVERSION;
	}
	//視点（カメラ座標）の上旋回
	if (pKeyInput->GetPress(DIK_UP))
	{
		fVartical -= INPUT_CONVERSION;
	}
	//視点（カメラ座標）の下旋回
	if (pKeyInput->GetPress(DIK_DOWN))
	{
		fVartical += INPUT_CONVERSION;
	}

	// 角度の修正
	CLibrary::RotFix(fHorizontal);

	// 角度の設定
	SetVartical(fVartical);
	SetHorizontal(fHorizontal);

	// カメラの位置設定
	VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// カメラ位置X設定
	VDest.y = PlayerPos.y + fDistance * cosf(fVartical);						// カメラ位置Y設定
	VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(fHorizontal);	// カメラ位置Z設定
	
	D3DXVECTOR3 posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);	//注視点設定

	//カメラPOSYの下限
	if (VDest.y <= CAMERA_MIN_HIGHT)
	{
		VDest.y = CAMERA_MIN_HIGHT;	//限界値に戻す
	}

	//設定値の反映
	GetposV() += (VDest - GetposV())*0.1f;
	GetposR() += (posRDest - GetposR())*0.9f;
}