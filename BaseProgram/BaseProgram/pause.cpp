//=====================================================================
//
//    ポーズ処理[pause.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
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
// マクロ定義
//=====================================================================
#define BACK_SIZE           (D3DXVECTOR3(1280.0f,70.0f,0.0f))              // 文字列
#define BACK_POS            (D3DXVECTOR3(640.0f,30.0f,0.0f))               // 続ける

#define STRING_SIZE         (D3DXVECTOR3(400.0f,100.0f,0.0f))              // 文字列
#define RESUME_POS          (D3DXVECTOR3(200.0f,160.0f,0.0f))               // 続ける
#define RESTART_POS         (D3DXVECTOR3(200.0f, 360.0f,0.0f))              // リスタート
#define EXIT_POS            (D3DXVECTOR3(200.0f, 560.0f,0.0f))              // 終了
#define TRANSLATION_SIZE    (D3DXVECTOR3(1280.0f, 720.0f,0.0f))              // リスタート
#define TRANSLATION_POS     (D3DXVECTOR3(640.0f, 360.0f,0.0f))              // 終了

#define MENU_ENTER_COL      (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))     // 選んでるメニューの色
#define MENU_NOT_ENTER_COL  (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f)) // 選んでないメニューの色

//=====================================================================
// コンストラクタ
//=====================================================================
CPause::CPause()
{
    memset(&m_apPolygon, 0, sizeof(m_apPolygon));
    memset(&m_pPolygon, 0, sizeof(m_pPolygon));
    m_nMenu = RESUME;
}

//=====================================================================
// デストラクタ
//=====================================================================
CPause::~CPause()
{
}

//=====================================================================
// 生成処理
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
// 初期化処理
//=====================================================================
HRESULT CPause::Init()
{
    CTexture* pTexture = GET_TEXTURE_PTR;
    m_pPolygon = CPolygon::Create(TRANSLATION_POS, TRANSLATION_SIZE);
    m_pPolygon->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TRANSLATION));
    // 続きから
    m_apPolygon[BACK] = CPolygon::Create(BACK_POS, BACK_SIZE);
    m_apPolygon[BACK]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BACK));
    // 続きから
    m_apPolygon[RESUME] = CPolygon::Create(RESUME_POS, STRING_SIZE);
    m_apPolygon[RESUME]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESUME));
    // リスタート
    m_apPolygon[RESTART] = CPolygon::Create(RESTART_POS, STRING_SIZE);
    m_apPolygon[RESTART]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESTART));
    // ゲーム終了
    m_apPolygon[EXIT] = CPolygon::Create(EXIT_POS, STRING_SIZE);
    m_apPolygon[EXIT]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_EXIT));

    return S_OK;
}

//=====================================================================
// 終了処理
//=====================================================================
void CPause::Uninit()
{
    for (int nCntTex = 0; nCntTex < MAX; nCntTex++)
    {
        if (m_apPolygon[nCntTex])
        {
            //終了処理
            m_apPolygon[nCntTex]->Uninit();
            // メモリの解放
            delete m_apPolygon[nCntTex];
            m_apPolygon[nCntTex] = nullptr;
        }
    }

    if (m_pPolygon)
    {
        //終了処理
        m_pPolygon->Uninit();
        // メモリの解放
        delete m_pPolygon;
        m_pPolygon = nullptr;
    }
}

//=====================================================================
// 更新処理
//=====================================================================
void CPause::Update()
{
    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade *pFade = CManager::GetInstance()->GetFade();

    // 選んでるメニューで色分け
    for (int nCntMenu = RESUME; nCntMenu < MAX; nCntMenu++)
    {
        if (m_nMenu == nCntMenu)
        {// 選んでるとき
            m_apPolygon[nCntMenu]->SetColor(MENU_ENTER_COL);
        }
        else
        {// 選んでないとき
            m_apPolygon[nCntMenu]->SetColor(MENU_NOT_ENTER_COL);
        }
    }

    // メニュー操作
    if (pKey->GetTrigger(DIK_W) || pKey->GetTrigger(DIK_UP))
    {// ↑
        m_nMenu--;
    }
    else if (pKey->GetTrigger(DIK_S) || pKey->GetTrigger(DIK_DOWN))
    {// ↓
        m_nMenu++;
    }

    // 範囲外に行かないように
    if (m_nMenu > EXIT)
    {
        m_nMenu = RESUME;
    }
    else if (m_nMenu < RESUME)
    {
        m_nMenu = EXIT;
    }

    // メニューコマンド
    if (pKey->GetTrigger(DIK_RETURN))
    {
        switch (m_nMenu)
        {
        case RESUME:
            // 続ける
            CManager::SetActivePause(false);
            break;
        case RESTART:
            // リスタート
            pFade->SetFade(CManager::MODE_TYPE_GAME);
            CManager::SetActivePause(false);
            break;
        case EXIT:
            // 終了処理
            // リスタート
            pFade->SetFade(CManager::MODE_TYPE_TITLE);
            CManager::SetActivePause(false);
            break;
        default:
            break;
        }
    }
}

//=====================================================================
// 描画処理
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