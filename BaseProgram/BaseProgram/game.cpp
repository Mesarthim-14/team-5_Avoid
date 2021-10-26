//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
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
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_bGameEnd = false;
	m_pFont = nullptr;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{
	// �I������
	Uninit();
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(void)
{
	// �v���C���[�̐���
	CreatePlayer();
	CGround::Create();
	//CSkinmeshModel::Create(D3DXVECTOR3(0.0f,100.0f,0.0f),ZeroVector3);

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit(void)
{
	// �v���C���[�̏I������
	if (m_pPlayer)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
#ifdef _DEBUG
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// �^�C�g���ɖ߂�
	if (pKey->GetTrigger(DIK_TAB) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}

	ShowInfo();
#endif // !_DEBUG
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{

}

//=======================================================================================
// �v���C���[�̐���
//=======================================================================================
void CGame::CreatePlayer(void)
{
	// �v���C���[�̐���
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
// ���\��
//=======================================================================================
void CGame::ShowInfo(void)
{
#ifdef _DEBUG

	//�����_���[�ŊǗ����Ă��̏��
	ImGui::Begin("DebugInfo");

	if (ImGui::CollapsingHeader("WorldInfo"))
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

			// �d�͂̒l
			ImGui::SliderFloat("Gravity", &m_fGravity, 0.0f, 50.0f);

			//ImGui::TreePop();
	}

	ImGui::End();
#endif // !_DEBUG
}
