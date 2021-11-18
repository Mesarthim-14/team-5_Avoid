//=============================================================================
//
// カメラの処理 [camera.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera.h"
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

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	//各メンバ変数のクリア
	m_posV = ZeroVector3;
	m_posVDest = ZeroVector3;
	m_posR = ZeroVector3;
	m_posRDest = ZeroVector3;
	m_posU = ZeroVector3;
	m_rot = ZeroVector3;
	m_fDistance = 0.0f;
	m_fMove = 0.0f;
	m_fHorizontal = 0.0f;
	m_fVartical = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init()
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update()
{

}

//=============================================================================
//カメラクラスのセット処理
//=============================================================================
void CCamera::SetCamera()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		500000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

//=============================================================================
// imguiの設定
//=============================================================================
void CCamera::ShowInfo()
{
	ImGui::Begin("DebugInfo");

	if (ImGui::CollapsingHeader("CameraInfo"))
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

		if (ImGui::TreeNode("Camera"))
		{
			ImGui::SliderFloat("Horizontal", &m_fHorizontal, D3DXToRadian(-180), D3DXToRadian(180));
			ImGui::TreePop();
		}
	}

	ImGui::End();
}