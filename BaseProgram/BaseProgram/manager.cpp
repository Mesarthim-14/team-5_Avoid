//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
//静的メンバ変数宣言
//=============================================================================
CManager* CManager::m_pManager = nullptr;
bool CManager::m_bPause = false;

//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
    // メモリ確保
    m_pRenderer.reset(new CRenderer);
    m_pInput.reset(new CInputKeyboard);
    m_pInputMouse.reset(new CMouse);
    m_pJoypad.reset(new CInputJoypad);
    m_pFade.reset(new CFade);
    m_pResourceManager.reset(CResourceManager::GetInstance());

    //メモリが確保できたら
    if (m_pRenderer)
    {
        // 初期化処理
        if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
        {
            return -1;
        }
    }

    //メモリが確保できたら
    if (m_pInput)
    {
        if (FAILED(m_pInput->Init(hInstance, hWnd)))
        {
            return -1;
        }
    }

    //メモリが確保できたら
    if (m_pInputMouse)
    {
        if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
        {
            return -1;
        }
    }

    //メモリが確保できたら
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
        // 初期化処理
        m_pFade->Init();
    }

    //ライブラリ生成
    if (FAILED(CLibrary::InitImgui(hWnd)))
    {
        //失敗
        MessageBox(hWnd, "初期化失敗", "InputMacro", MB_OK | MB_ICONHAND);
        return E_FAIL;
    }

    //全テクスチャの読み込み
    LoadAll();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit()
{
    //ImGui終了
    CLibrary::UninitImgui();

    // nullchack
    if (m_pFade)
    {
        //フェードクラスの終了処理呼び出し
        m_pFade->Uninit();
        m_pFade.reset();
        m_pFade = nullptr;
    }

    // nullcheck
    if (m_pResourceManager)
    {
        // リソースのロード
        m_pResourceManager.reset();
        m_pResourceManager = nullptr;
    }

    // nullchack
    if (m_pInput)
    {
        //入力処理クラスの終了処理呼び出し
        m_pInput->Uninit();

        //メモリの削除
        m_pInput.reset();
        m_pInput = nullptr;
    }

    // nullchack
    if (m_pInputMouse)
    {
        //入力処理クラスの終了処理呼び出し
        m_pInputMouse->Uninit();

        //メモリの削除
        m_pInputMouse.reset();
        m_pInputMouse = nullptr;
    }

    // nullchack
    if (m_pJoypad)
    {
        //入力処理クラスの終了処理呼び出し
        m_pJoypad->Uninit();

        //メモリの削除
        m_pJoypad.reset();
        m_pJoypad = nullptr;
    }

    //メモリ開放
    if (m_pRenderer)
    {
        // 描画クラス
        m_pRenderer.reset();
        m_pRenderer = nullptr;
    }

    if (m_pModeBase)
    {
        // 描画クラス
        m_pModeBase.reset();
        m_pModeBase = nullptr;
    }

    // シーン情報のリリース
    CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update()
{
    CInputKeyboard* pKey = CManager::GetKeyboard();
    if (m_pInput)
    {
        //入力処理クラスの更新処理呼び出し
        m_pInput->Update();
    }

    if (m_pInputMouse)
    {
        //入力処理クラスの更新処理呼び出し
        m_pInputMouse->Update();
    }

    if (m_pJoypad)
    {
        //入力処理クラスの更新処理呼び出し
        m_pJoypad->Update();
    }

    if (m_pRenderer)
    {
        //レンダラークラスの更新処理呼び出し
        m_pRenderer->Update();
    }
    if (m_pFade)
    {
        //フェードクラスの更新処理呼び出し
        m_pFade->Update();
    }

    // モードの更新処理
    if (m_pModeBase)
    {
        m_pModeBase->Update();
    }

    // カメラの更新処理
    if (m_pCamera)
    {
        m_pCamera->Update();
        m_pCamera->ShowInfo();
    }

    if (m_pLight)
    {
        //レンダラーで管理してるやつの情報
        ImGui::Begin("DebugInfo");
        m_pLight->ShowLightInfo();
        ImGui::End();
    }

    // ポーズの設定
    //if (m_pRenderer)
    //{
    //    if (m_mode == MODE_TYPE_GAME)
    //    {// モードゲームのときポーズ画面の処理

    //        if (pKey->GetTrigger(DIK_6))
    //        {

    //            if (m_pPause == NULL)
    //            {
    //                // 生成
    //                m_pPause = CPause::Create();
    //            }
    //            // ポーズの切り替え
    //            m_bPause ^= true;
    //        }
    //        if (!m_bPause)
    //        {// ポーズじゃないとき

    //            if (m_pPause != NULL)
    //            {
    //                m_pPause->Uninit();
    //                delete m_pPause;
    //                m_pPause = NULL;
    //            }
    //            m_pRenderer->Update();
    //        }
    //        else
    //        {// ポーズ状態
    //            if (m_pPause != NULL)
    //            {
    //                // ポーズの更新処理
    //                m_pPause->Update();
    //            }
    //        }
    //    }
    //    else
    //    {
    //        //レンダラークラスの更新処理呼び出し
    //        m_pRenderer->Update();
    //    }
    //}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw()
{
    if (m_pRenderer)
    {
        //レンダラークラスの描画処理呼び出し
        m_pRenderer->Draw();
    }

    // モードの更新処理
    if (m_pModeBase)
    {
        m_pModeBase->Draw();
    }
}

//=============================================================================
// テクスチャの全ロード処理
//=============================================================================
void CManager::LoadAll()
{
    // !nullcheck
    if (m_pResourceManager)
    {
        // リソースのロード
        m_pResourceManager->LoadAll();
    }
}

//=============================================================================
// テクスチャの全アンロード処理
//=============================================================================
void CManager::UnLoadAll()
{
    // !nullcheck
    if (m_pResourceManager)
    {
        // リソースのロード
        m_pResourceManager->UnLoadAll();
    }
}

//=============================================================================
// ゲームモードの設定処理
//=============================================================================
void CManager::SetMode(const MODE_TYPE &mode)
{
    // !nullcheck
    if (m_pModeBase)
    {
        //メモリ開放
        m_pModeBase.reset();
        m_pModeBase = nullptr;
    }

    // サウンドの情報
    CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

    //サウンドストップ
    pSound->StopAll();

    // 影の終了処理
    CShadow::PolygonUninit();

    // シーン情報のリリース
    CScene::ReleaseAll();

    // モードを変える
    m_mode = mode;

    //設定されたモードをクリエイト
    switch (m_mode)
    {
        // タイトル
    case MODE_TYPE_TITLE:
        // タイトル生成
        m_pModeBase.reset(new CTitle);
    //    m_pCamera.reset(CCameraTitle::Create());
        break;

        // ゲーム
    case MODE_TYPE_GAME:
        // ゲーム生成
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
        // 初期化処理
        m_pModeBase->Init();
    }
}

//=============================================================================
// ゲーム情報
//=============================================================================
CModeBase * CManager::GetModePtr()
{
    //キャスト
    CModeBase *pMode = ((CModeBase*)m_pModeBase.get());

    // !nullcheck
    if (pMode)
    {
        return pMode;
    }

    return nullptr;
}

//=============================================================================
// プレイヤーのポインタ
//=============================================================================
CPlayer * CManager::GetPlayer()const 
{
    CCharacter *pScene = (CCharacter*)CScene::GetTop(CScene::PRIORITY_CHARACTER);

    // プレイヤーの情報取得
    if (pScene)
    {
        while (pScene)
        {
            // 現在のポインタ
            CCharacter *pNext = (CCharacter*)pScene->GetNext();

            if (pScene->GetType() == CCharacter::CHARACTER_TYPE_PLAYER)
            {
                return (CPlayer*)pScene;
            }

            // 次のポインタ取得
            pScene = pNext;
        }
    }

    return nullptr;
}

//=============================================================================
// ゲームモードの取得
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
// インスタンスの取得
//=============================================================================
CManager * CManager::GetInstance()
{
    if (!m_pManager)
    {
        m_pManager = new CManager;
    }

    return m_pManager;
}
