//=============================================================================
//
// �^�C�g���N���X [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
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
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
    m_pObject2D.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
    // �I������
    Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init()
{

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit()
{
    for (auto &object : m_pObject2D)
    {
        // �I������
        object->Uninit();
    }

    // �I�u�W�F�N�g�폜
    m_pObject2D.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update()
{

    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
    if (CManager::GetInstance()->GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
        || pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_GAME);
    }

    // �G�f�B�b�g���[�h
    if (pKey->GetTrigger(DIK_1) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_PLAYER_EDITOR);
    }

}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw()
{

}