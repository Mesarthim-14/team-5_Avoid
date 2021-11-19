//=======================================================================================
//
// �v���C���[�̃G�f�B�^�N���X [player_editor.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
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
// �R���X�g���N�^
//=======================================================================================
CPlayerEditor::CPlayerEditor()
{
    m_pPlayer = nullptr;
    m_bGameEnd = false;
    m_pFont = nullptr;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CPlayerEditor::~CPlayerEditor()
{
    // �I������
    Uninit();
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CPlayerEditor::Init()
{
    // �v���C���[�̐���
    PlayerCreate();
    CGround::Create();

    return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CPlayerEditor::Uninit()
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
void CPlayerEditor::Update()
{
    // �v���C���[�̏I������
    if (m_pPlayer)
    {
        m_pPlayer->ShowInfo();
    }

    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
    if (pKey->GetTrigger(DIK_7))
    {
        // �v���C���[�̏���Save
        if (m_pPlayer)
        {
            m_pPlayer->SaveInfo();
        }
    }

    // �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
    if (pKey->GetTrigger(DIK_TAB) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_TITLE);
    }
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CPlayerEditor::Draw()
{

}

//=======================================================================================
// �v���C���[�̐���
//=======================================================================================
void CPlayerEditor::PlayerCreate()
{
    // �v���C���[�̐���
    if (!m_pPlayer)
    {
        m_pPlayer = CPlayer::Create(ZeroVector3, ZeroVector3);
    }
}