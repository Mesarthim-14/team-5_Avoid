//=====================================================================
//
//    �|�[�Y����[pause.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "pause.h"
#include "polygon.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "fade.h"
#include "joypad.h"
#include "texture.h"
#include "resource_manager.h"
#include "camera_game.h"
#include "translation.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define BACK_SIZE           (D3DXVECTOR3(1280.0f,70.0f,0.0f))              // ������
#define BACK_POS            (D3DXVECTOR3(640.0f,30.0f,0.0f))               // ������

#define STRING_SIZE         (D3DXVECTOR3(400.0f,100.0f,0.0f))              // ������
#define RESUME_POS          (D3DXVECTOR3(200.0f,160.0f,0.0f))               // ������
#define RESTART_POS         (D3DXVECTOR3(200.0f, 360.0f,0.0f))              // ���X�^�[�g
#define EXIT_POS            (D3DXVECTOR3(200.0f, 560.0f,0.0f))              // �I��
#define TRANSLATION_SIZE    (D3DXVECTOR3(1280.0f, 720.0f,0.0f))              // ���X�^�[�g
#define TRANSLATION_POS     (D3DXVECTOR3(640.0f, 360.0f,0.0f))              // �I��

#define MENU_ENTER_COL      (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))     // �I��ł郁�j���[�̐F
#define MENU_NOT_ENTER_COL  (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f)) // �I��łȂ����j���[�̐F

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPause::CPause()
{
    memset(&m_apPolygon, 0, sizeof(m_apPolygon));
    memset(&m_pPolygon, 0, sizeof(m_pPolygon));
    m_nMenu = RESUME;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPause::~CPause()
{
}

//=====================================================================
// ��������
//=====================================================================
CPause * CPause::Create()
{
    CPause * pPause = new CPause();

    if (pPause)
    { 
        pPause->Init();
        return pPause;
    }

    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
HRESULT CPause::Init()
{
    CTexture* pTexture = GET_TEXTURE_PTR;
    m_pPolygon = CPolygon::Create(TRANSLATION_POS, TRANSLATION_SIZE);
    m_pPolygon->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TRANSLATION));
    // ��������
    m_apPolygon[BACK] = CPolygon::Create(BACK_POS, BACK_SIZE);
    m_apPolygon[BACK]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BACK));
    // ��������
    m_apPolygon[RESUME] = CPolygon::Create(RESUME_POS, STRING_SIZE);
    m_apPolygon[RESUME]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESUME));
    // ���X�^�[�g
    m_apPolygon[RESTART] = CPolygon::Create(RESTART_POS, STRING_SIZE);
    m_apPolygon[RESTART]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESTART));
    // �Q�[���I��
    m_apPolygon[EXIT] = CPolygon::Create(EXIT_POS, STRING_SIZE);
    m_apPolygon[EXIT]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_EXIT));

    return S_OK;
}

//=====================================================================
// �I������
//=====================================================================
void CPause::Uninit()
{
    for (int nCntTex = 0; nCntTex < MAX; nCntTex++)
    {
        if (m_apPolygon[nCntTex])
        {
            //�I������
            m_apPolygon[nCntTex]->Uninit();
            // �������̉��
            delete m_apPolygon[nCntTex];
            m_apPolygon[nCntTex] = nullptr;
        }
    }

    if (m_pPolygon)
    {
        //�I������
        m_pPolygon->Uninit();
        // �������̉��
        delete m_pPolygon;
        m_pPolygon = nullptr;
    }
}

//=====================================================================
// �X�V����
//=====================================================================
void CPause::Update()
{
    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade *pFade = CManager::GetInstance()->GetFade();

    // �I��ł郁�j���[�ŐF����
    for (int nCntMenu = RESUME; nCntMenu < MAX; nCntMenu++)
    {
        if (m_nMenu == nCntMenu)
        {// �I��ł�Ƃ�
            m_apPolygon[nCntMenu]->SetColor(MENU_ENTER_COL);
        }
        else
        {// �I��łȂ��Ƃ�
            m_apPolygon[nCntMenu]->SetColor(MENU_NOT_ENTER_COL);
        }
    }

    // ���j���[����
    if (pKey->GetTrigger(DIK_W) || pKey->GetTrigger(DIK_UP))
    {// ��
        m_nMenu--;
    }
    else if (pKey->GetTrigger(DIK_S) || pKey->GetTrigger(DIK_DOWN))
    {// ��
        m_nMenu++;
    }

    // �͈͊O�ɍs���Ȃ��悤��
    if (m_nMenu > EXIT)
    {
        m_nMenu = RESUME;
    }
    else if (m_nMenu < RESUME)
    {
        m_nMenu = EXIT;
    }

    // ���j���[�R�}���h
    if (pKey->GetTrigger(DIK_RETURN))
    {
        switch (m_nMenu)
        {
        case RESUME:
            // ������
            CManager::SetActivePause(false);
            break;
        case RESTART:
            // ���X�^�[�g
            pFade->SetFade(CManager::MODE_TYPE_GAME);
            CManager::SetActivePause(false);
            break;
        case EXIT:
            // �I������
            // ���X�^�[�g
            pFade->SetFade(CManager::MODE_TYPE_TITLE);
            CManager::SetActivePause(false);
            break;
        default:
            break;
        }
    }
}

//=====================================================================
// �`�揈��
//=====================================================================
void CPause::Draw()
{
    if (m_pPolygon)
    {
        m_pPolygon->Draw();
    }

    for (int nCntPolygon = 0; nCntPolygon < MAX; nCntPolygon++)
    {
        if (m_apPolygon[nCntPolygon])
        {
            m_apPolygon[nCntPolygon]->Draw();
        }
    }
}