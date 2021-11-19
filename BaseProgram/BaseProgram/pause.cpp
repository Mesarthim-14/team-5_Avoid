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

//=====================================================================
// �}�N����`
//=====================================================================
#define BACK_SIZE D3DXVECTOR3(300.0f,400.0f,0.0f)                   // �w�ʃT�C�Y
#define BACK_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f)   // �w�ʍ��W

#define STRING_SIZE D3DXVECTOR3(200.0f,70.0f,0.0f)                                              // ������
#define RESUME_POS  D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y - (STRING_SIZE.y + 25),0.0f)    // ������
#define RESTART_POS D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y,0.0f)                           // ���X�^�[�g
#define EXIT_POS       D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y + (STRING_SIZE.y + 25),0.0f)    // �I��

#define MENU_ENTER_COL D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f)     // �I��ł郁�j���[�̐F
#define MENU_NOT_ENTER_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) // �I��łȂ����j���[�̐F

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPause::CPause()
{
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
    // �|�[�Y�̔w�i
    m_pPolygon[BACK] = CPolygon::Create(BACK_POS, BACK_SIZE);
    // ��������
    m_pPolygon[RESUME] = CPolygon::Create(RESUME_POS, STRING_SIZE);
    // ���X�^�[�g
    m_pPolygon[RESTART] = CPolygon::Create(RESTART_POS, STRING_SIZE);
    // �Q�[���I��
    m_pPolygon[EXIT] = CPolygon::Create(EXIT_POS, STRING_SIZE);
    return S_OK;
}

//=====================================================================
// �I������
//=====================================================================
void CPause::Uninit()
{
    for (int nCntTex = 0; nCntTex < MAX; nCntTex++)
    {
        if (m_pPolygon[nCntTex])
        {
            //�I������
            m_pPolygon[nCntTex]->Uninit();
            // �������̉��
            delete m_pPolygon[nCntTex];
            m_pPolygon[nCntTex] = NULL;
        }
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
            m_pPolygon[nCntMenu]->SetColor(MENU_ENTER_COL);
        }
        else
        {// �I��łȂ��Ƃ�
            m_pPolygon[nCntMenu]->SetColor(MENU_NOT_ENTER_COL);
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
            break;
        case EXIT:
            // �I������
            // ���X�^�[�g
            pFade->SetFade(CManager::MODE_TYPE_TITLE);
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
    for (int nCntPolygon = 0; nCntPolygon < MAX; nCntPolygon++)
    {
        if (m_pPolygon[nCntPolygon])
        {
            m_pPolygon[nCntPolygon]->Draw();
        }
    }
}
