//=============================================================================
//
// タイトルクラス [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "player_editor.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_pObject2D.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
	// 終了処理
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	for (auto &object : m_pObject2D)
	{
		// 終了処理
		object->Uninit();
	}

	// オブジェクト削除
	m_pObject2D.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{

	CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetInstance()->GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetInstance()->GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	// エディットモード
	if (pKey->GetTrigger(DIK_1) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetInstance()->GetFade();
		pFade->SetFade(CManager::MODE_TYPE_PLAYER_EDITOR);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}