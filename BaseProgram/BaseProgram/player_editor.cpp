//=======================================================================================
//
// プレイヤーのエディタクラス [player_editor.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "player_editor.h"
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

//=======================================================================================
// コンストラクタ
//=======================================================================================
CPlayerEditor::CPlayerEditor()
{
	m_pPlayer = nullptr;
	m_bGameEnd = false;
	m_pFont = nullptr;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CPlayerEditor::~CPlayerEditor()
{
	// 終了処理
	Uninit();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CPlayerEditor::Init(void)
{
	// プレイヤーの生成
	PlayerCreate();
	CGround::Create();

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CPlayerEditor::Uninit(void)
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
void CPlayerEditor::Update(void)
{
	// プレイヤーの終了処理
	if (m_pPlayer)
	{
		m_pPlayer->ShowInfo();
	}

	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (pKey->GetTrigger(DIK_7))
	{
		// プレイヤーの情報をSave
		if (m_pPlayer)
		{
			m_pPlayer->SaveInfo();
		}
	}

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (pKey->GetTrigger(DIK_TAB) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CPlayerEditor::Draw(void)
{

}

//=======================================================================================
// プレイヤーの生成
//=======================================================================================
void CPlayerEditor::PlayerCreate(void)
{
	// プレイヤーの生成
	if (!m_pPlayer)
	{
		m_pPlayer = CPlayer::Create(ZeroVector3, ZeroVector3);
	}
}