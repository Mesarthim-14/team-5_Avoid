//=======================================================================================
//
// ゲーム処理 [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "joypad.h"
#include "sound.h"
#include "keyboard.h"
#include "resource_manager.h"
#include "fade.h"
#include "test_2d.h"
#include "test_model.h"
#include "test_character.h"
#include "ground.h"
#include "skinmesh_model.h"
#include "library.h"

float CGame::m_fGravity = 4.0f;
//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_bGameEnd = false;
	m_pFont = nullptr;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{
	// 終了処理
	Uninit();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init(void)
{
	// プレイヤーの生成
	CreatePlayer();
	CGround::Create();
	//CSkinmeshModel::Create(D3DXVECTOR3(0.0f,100.0f,0.0f),ZeroVector3);

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	// プレイヤーの終了処理
	if (m_pPlayer)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	// デバッグ情報表示用フォントの破棄
	if (m_pFont)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
#ifdef _DEBUG
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// タイトルに戻る
	if (pKey->GetTrigger(DIK_TAB) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}

	ShowInfo();
#endif // !_DEBUG
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{

}

//=======================================================================================
// プレイヤーの生成
//=======================================================================================
void CGame::CreatePlayer(void)
{
	// プレイヤーの生成
	if (!m_pPlayer)
	{
		m_pPlayer = CPlayer::Create(ZeroVector3, ZeroVector3);
	}

//	CTestCharacter::Create(D3DXVECTOR3(1000.0f, 0.0f, 0.0f));
//	CTestCharacter::Create(ZeroVector3);
//	CTestCharacter::Create(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f));
	CTestModel::Create();
}

//=======================================================================================
// 情報表示
//=======================================================================================
void CGame::ShowInfo(void)
{
#ifdef _DEBUG

	//レンダラーで管理してるやつの情報
	ImGui::Begin("DebugInfo");

	if (ImGui::CollapsingHeader("WorldInfo"))
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

			// 重力の値
			ImGui::SliderFloat("Gravity", &m_fGravity, 0.0f, 50.0f);

			//ImGui::TreePop();
	}

	ImGui::End();
#endif // !_DEBUG
}
