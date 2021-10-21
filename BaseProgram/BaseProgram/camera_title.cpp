//=============================================================================
//
// タイトルカメラの処理 [camera_title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera_title.h"
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
#define TITLE_CAMERA_DISTANCE		(3000.0f)				// 距離
#define TITLE_CAMERA_DEFAULT_Fθ	(D3DXToRadian(89.0f))	// カメラ角度縦
#define TITLE_CAMERA_DEFAULT_Hθ	(D3DXToRadian(95.0f))	// カメラ角度横
#define CAMERA_HEIGHT				(600.0f)				// 注視点の高さ

//=============================================================================
// インスタンス生成
//=============================================================================
CCameraTitle * CCameraTitle::Create(void)
{
	// メモリ確保
	CCameraTitle *pCamera = new CCameraTitle;

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
CCameraTitle::CCameraTitle()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CCameraTitle::~CCameraTitle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCameraTitle::Init(void)
{
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, CAMERA_HEIGHT, 0.0f);
	D3DXVECTOR3 posV = ZeroVector3;
	float fDistance = TITLE_CAMERA_DISTANCE;
	float fVartical = TITLE_CAMERA_DEFAULT_Fθ;
	float fHorizontal = TITLE_CAMERA_DEFAULT_Hθ;

	SetDistance(fDistance);
	SetVartical(fVartical);
	SetHorizontal(fHorizontal);					// 初期値敵のほう向ける
	GetposR() = posR;
	GetposU() = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 上方向ベクトル

	posV.x = posR.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// カメラ位置X
	posV.y = posR.z + fDistance * cosf(fVartical);						// カメラ位置Y
	posV.z = posR.y + fDistance * sinf(fVartical) * cosf(fHorizontal);	// カメラ位置Z

	GetposV() = posV;

	return S_OK;
}

//=============================================================================
// 通常状態の更新処理
//=============================================================================
void CCameraTitle::NomalUpdate(void)
{

}

void CCameraTitle::MouseUpdate(void)
{
}
