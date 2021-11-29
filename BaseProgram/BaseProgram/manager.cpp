//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "billboard.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "joypad.h"
#include "keyboard.h"
#include "mouse.h"
#include "manager.h"
#include "mesh_3d.h"
#include "model.h"
#include "player.h"
#include "renderer.h"
#include "resource_manager.h"
#include "scene3D.h"
#include "sound.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "xfile.h"
#include "polygon.h"
#include "shadow.h"
#include "light.h"
#include "camera.h"
#include "camera_title.h"
#include "camera_game.h"
#include "library.h"
#include "player_editor.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CManager* CManager::m_pManager = nullptr;
bool CManager::m_bPause = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
    m_mode = CManager::MODE_TYPE_TITLE;
    m_pRenderer = nullptr;
    m_pInput = nullptr;
    m_pInputMouse = nullptr;
    m_pFade = nullptr;
    m_pJoypad = nullptr;
    m_pScene = nullptr;
    m_pResourceManager = nullptr;
    m_pModeBase = nullptr;
    m_pLight = nullptr;
    m_pCamera = nullptr;
    m_pPause = nullptr;
    m_pGauge = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
    // �������m��
    m_pRenderer.reset(new CRenderer);
    m_pInput.reset(new CInputKeyboard);
    m_pInputMouse.reset(new CMouse);
    m_pJoypad.reset(new CInputJoypad);
    m_pFade.reset(new CFade);
    m_pResourceManager.reset(CResourceManager::GetInstance());

    //���������m�ۂł�����
    if (m_pRenderer)
    {
        // ����������
        if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
        {
            return -1;
        }
    }

    //���������m�ۂł�����
    if (m_pInput)
    {
        if (FAILED(m_pInput->Init(hInstance, hWnd)))
        {
            return -1;
        }
    }

    //���������m�ۂł�����
    if (m_pInputMouse)
    {
        if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
        {
            return -1;
        }
    }

    //���������m�ۂł�����
    if (m_pJoypad)
    {
        if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
        {
            return -1;
        }
    }

    // nullcheck
    if (m_pFade)
    {
        // ����������
        m_pFade->Init();
    }

    //���C�u��������
    if (FAILED(CLibrary::InitImgui(hWnd)))
    {
        //���s
        MessageBox(hWnd, "���������s", "InputMacro", MB_OK | MB_ICONHAND);
        return E_FAIL;
    }

    //�S�e�N�X�`���̓ǂݍ���
    LoadAll();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit()
{
    //ImGui�I��
    CLibrary::UninitImgui();

    // nullchack
    if (m_pFade)
    {
        //�t�F�[�h�N���X�̏I�������Ăяo��
        m_pFade->Uninit();
        m_pFade.reset();
        m_pFade = nullptr;
    }

    // nullcheck
    if (m_pResourceManager)
    {
        // ���\�[�X�̃��[�h
        m_pResourceManager.reset();
        m_pResourceManager = nullptr;
    }

    // nullchack
    if (m_pInput)
    {
        //���͏����N���X�̏I�������Ăяo��
        m_pInput->Uninit();

        //�������̍폜
        m_pInput.reset();
        m_pInput = nullptr;
    }

    // nullchack
    if (m_pInputMouse)
    {
        //���͏����N���X�̏I�������Ăяo��
        m_pInputMouse->Uninit();

        //�������̍폜
        m_pInputMouse.reset();
        m_pInputMouse = nullptr;
    }

    // nullchack
    if (m_pJoypad)
    {
        //���͏����N���X�̏I�������Ăяo��
        m_pJoypad->Uninit();

        //�������̍폜
        m_pJoypad.reset();
        m_pJoypad = nullptr;
    }

    //�������J��
    if (m_pRenderer)
    {
        // �`��N���X
        m_pRenderer.reset();
        m_pRenderer = nullptr;
    }

    if (m_pModeBase)
    {
        // �`��N���X
        m_pModeBase.reset();
        m_pModeBase = nullptr;
    }

    // �V�[�����̃����[�X
    CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update()
{
    CInputKeyboard* pKey = CManager::GetKeyboard();
    if (m_pInput)
    {
        //���͏����N���X�̍X�V�����Ăяo��
        m_pInput->Update();
    }

    if (m_pInputMouse)
    {
        //���͏����N���X�̍X�V�����Ăяo��
        m_pInputMouse->Update();
    }

    if (m_pJoypad)
    {
        //���͏����N���X�̍X�V�����Ăяo��
        m_pJoypad->Update();
    }

    if (m_pRenderer)
    {
        //�����_���[�N���X�̍X�V�����Ăяo��
        m_pRenderer->Update();
    }
    if (m_pFade)
    {
        //�t�F�[�h�N���X�̍X�V�����Ăяo��
        m_pFade->Update();
    }

    // ���[�h�̍X�V����
    if (m_pModeBase)
    {
        m_pModeBase->Update();
    }

    // �J�����̍X�V����
    if (m_pCamera)
    {
        m_pCamera->Update();
        m_pCamera->ShowInfo();
    }

    if (m_pLight)
    {
        //�����_���[�ŊǗ����Ă��̏��
        ImGui::Begin("DebugInfo");
        m_pLight->ShowLightInfo();
        ImGui::End();
    }

    // �|�[�Y�̐ݒ�
    //if (m_pRenderer)
    //{
    //    if (m_mode == MODE_TYPE_GAME)
    //    {// ���[�h�Q�[���̂Ƃ��|�[�Y��ʂ̏���

    //        if (pKey->GetTrigger(DIK_6))
    //        {

    //            if (m_pPause == NULL)
    //            {
    //                // ����
    //                m_pPause = CPause::Create();
    //            }
    //            // �|�[�Y�̐؂�ւ�
    //            m_bPause ^= true;
    //        }
    //        if (!m_bPause)
    //        {// �|�[�Y����Ȃ��Ƃ�

    //            if (m_pPause != NULL)
    //            {
    //                m_pPause->Uninit();
    //                delete m_pPause;
    //                m_pPause = NULL;
    //            }
    //            m_pRenderer->Update();
    //        }
    //        else
    //        {// �|�[�Y���
    //            if (m_pPause != NULL)
    //            {
    //                // �|�[�Y�̍X�V����
    //                m_pPause->Update();
    //            }
    //        }
    //    }
    //    else
    //    {
    //        //�����_���[�N���X�̍X�V�����Ăяo��
    //        m_pRenderer->Update();
    //    }
    //}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw()
{
    if (m_pRenderer)
    {
        //�����_���[�N���X�̕`�揈���Ăяo��
        m_pRenderer->Draw();
    }

    // ���[�h�̍X�V����
    if (m_pModeBase)
    {
        m_pModeBase->Draw();
    }
}

//=============================================================================
// �e�N�X�`���̑S���[�h����
//=============================================================================
void CManager::LoadAll()
{
    // !nullcheck
    if (m_pResourceManager)
    {
        // ���\�[�X�̃��[�h
        m_pResourceManager->LoadAll();
    }
}

//=============================================================================
// �e�N�X�`���̑S�A�����[�h����
//=============================================================================
void CManager::UnLoadAll()
{
    // !nullcheck
    if (m_pResourceManager)
    {
        // ���\�[�X�̃��[�h
        m_pResourceManager->UnLoadAll();
    }
}

//=============================================================================
// �Q�[�����[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(const MODE_TYPE &mode)
{
    // !nullcheck
    if (m_pModeBase)
    {
        //�������J��
        m_pModeBase.reset();
        m_pModeBase = nullptr;
    }

    // �T�E���h�̏��
    CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

    //�T�E���h�X�g�b�v
    pSound->StopAll();

    // �e�̏I������
    CShadow::PolygonUninit();

    // �V�[�����̃����[�X
    CScene::ReleaseAll();

    // ���[�h��ς���
    m_mode = mode;

    //�ݒ肳�ꂽ���[�h���N���G�C�g
    switch (m_mode)
    {
        // �^�C�g��
    case MODE_TYPE_TITLE:
        // �^�C�g������
        m_pModeBase.reset(new CTitle);
    //    m_pCamera.reset(CCameraTitle::Create());
        break;

        // �Q�[��
    case MODE_TYPE_GAME:
        // �Q�[������
        m_pModeBase.reset(new CGame);
        m_pCamera.reset(CCameraGame::Create());
        m_pLight.reset(CLight::Create());
        break;

    case MODE_TYPE_PLAYER_EDITOR:
        m_pModeBase.reset(new CPlayerEditor);
        m_pCamera.reset(CCameraGame::Create());
        m_pLight.reset(CLight::Create());
    default:
        break;
    }

    // nullcheck
    if (m_pModeBase)
    {
        // ����������
        m_pModeBase->Init();
    }
}

//=============================================================================
// �Q�[�����
//=============================================================================
CModeBase * CManager::GetModePtr()
{
    //�L���X�g
    CModeBase *pMode = ((CModeBase*)m_pModeBase.get());

    // !nullcheck
    if (pMode)
    {
        return pMode;
    }

    return nullptr;
}

//=============================================================================
// �v���C���[�̃|�C���^
//=============================================================================
CPlayer * CManager::GetPlayer()const 
{
    CCharacter *pScene = (CCharacter*)CScene::GetTop(CScene::PRIORITY_CHARACTER);

    // �v���C���[�̏��擾
    if (pScene)
    {
        while (pScene)
        {
            // ���݂̃|�C���^
            CCharacter *pNext = (CCharacter*)pScene->GetNext();

            if (pScene->GetType() == CCharacter::CHARACTER_TYPE_PLAYER)
            {
                return (CPlayer*)pScene;
            }

            // ���̃|�C���^�擾
            pScene = pNext;
        }
    }

    return nullptr;
}

//=============================================================================
// �Q�[�����[�h�̎擾
//=============================================================================
CGame * CManager::GetGame() const
{
    if ((CGame*)m_pModeBase.get())
    {
        return ((CGame*)m_pModeBase.get());
    }

    return nullptr;
}

//=============================================================================
// �C���X�^���X�̎擾
//=============================================================================
CManager * CManager::GetInstance()
{
    if (!m_pManager)
    {
        m_pManager = new CManager;
    }

    return m_pManager;
}
