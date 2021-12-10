//=======================================================================================
//
// ゲーム処理 [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
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
#include "check_point.h"
#include "water_fresnel.h"
#include "shark.h"
#include "marlin.h"
#include "ghost.h"
#include "gimmick_factory.h"
#include "kraken.h"
#include "sky.h"
#include "gauge.h"
#include "gaugebar.h"
#include "npc_enemy_info.h"
#include "npc_factory.h"
#include "gauss_filter.h"
#include "state_player_not_move.h"
#include "state_kraken_not_attack.h"
#include "camera_game.h"
#include "state_camera_descent.h"
#include "pause.h"
#include "map_factory.h"
float CGame::m_fGravity = 1.5f;
CGaussFilter* CGame::m_pGaussFilter = nullptr;
bool CGame::m_bGaussFilter = true;

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame()
{
    m_pPlayer = nullptr;
    m_bGameEnd = false;
    m_pFont = nullptr;
    m_pGimmickFactory = nullptr;
    m_pKraken = nullptr;
    m_pNpcFactory = nullptr;
    m_pPause = nullptr;
    m_pMapFactory = nullptr;
    m_pGauge = nullptr;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{
    // 終了処理
    Uninit();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init()
{
    CreateFilter();
    CreateObject();
    return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit()
{
    // プレイヤーの終了処理
    if (m_pPlayer)
    {
        m_pPlayer->Uninit();
        m_pPlayer = nullptr;
    }
    if (m_pKraken)
    {
        m_pKraken->Uninit();
        m_pKraken = nullptr;
    }
    if (m_pNpcFactory)
    {
        m_pNpcFactory->Uninit();
        m_pNpcFactory = nullptr;
    }
    if (m_pGauge)
    {
        m_pGauge->Uninit();
        m_pGauge = nullptr;
    }

    // デバッグ情報表示用フォントの破棄
    if (m_pFont)
    {
        m_pFont->Release();
        m_pFont = nullptr;
    }
    if (m_pGimmickFactory)
    {
        m_pGimmickFactory->Uninit();
        delete m_pGimmickFactory;
        m_pGimmickFactory = nullptr;
    }
    if (m_pGaussFilter)
    {
        m_pGaussFilter->Uninit();
        m_pGaussFilter = nullptr;
    }
    if (m_pMapFactory)
    {
        m_pMapFactory->Uninit();
        m_pMapFactory = nullptr;
    }
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update()
{
    if (m_pGimmickFactory)
    {
        m_pGimmickFactory->Update();
    }

    if (m_bGameEnd)
    {
        CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();
        if (mode == CFade::FADE_MODE_NONE)
        {
            CFade *pFade = CManager::GetInstance()->GetFade();
            pFade->SetFade(CManager::MODE_TYPE_TITLE);
        }
    }

#ifdef _DEBUG
    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // タイトルに戻る
    if (pKey->GetTrigger(DIK_TAB) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_TITLE);
    }
    // タイトルに戻る
    if (pKey->GetTrigger(DIK_RETURN))
    {
        if (m_pGaussFilter)
        {
            // ガウスのフェードに以降
            m_pGaussFilter->SetFade(true);

            // カメラの種類を変える
            CCameraGame* pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
            pCamera->ChangeState(CCameraStateDescent::Create());
        }
    }

    ShowInfo();
#endif // !_DEBUG
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw()
{
}

//=======================================================================================
// ガウスフィルタの開始
//=======================================================================================
void CGame::BeginGauss()
{
    if (m_pGaussFilter)
    {
        if (m_pGaussFilter->GetUse())
        {
            m_pGaussFilter->BeginSurface();
        }
    }
}

//=======================================================================================
// ガウスフィルタの終了
//=======================================================================================
void CGame::EndGauss()
{
    if (m_pGaussFilter)
    {
        if (m_pGaussFilter->GetUse())
        {
            m_pGaussFilter->DrawPolygon();
        }
    }
}

//=======================================================================================
// プレイヤーの生成
//=======================================================================================
void CGame::CreatePlayer()
{
    // プレイヤーの生成
    if (!m_pPlayer)
    {
        m_pPlayer = CPlayer::Create(D3DXVECTOR3(54500.0f, 0.0f, 25500.0f), ZeroVector3);
        m_pPlayer->ChangeState(CPlayerStateNotMove::Create());
    }
}

//=======================================================================================
// エネミーの生成
//=======================================================================================
void CGame::CreateEnemy()
{
    CShark::Create(D3DXVECTOR3(-61089.5f, 0.0f, -80828.8f), ZeroVector3);
    CShark::Create(D3DXVECTOR3(-85253.0f, 0.0f, -20055.2f), ZeroVector3);
    CShark::Create(D3DXVECTOR3(-51384.1f, 0.0f, -41619.3f), ZeroVector3);
    CShark::Create(D3DXVECTOR3(-29624.6f, 0.0f, -89824.0f), ZeroVector3);
    CShark::Create(D3DXVECTOR3(-26419.4f, 0.0f, -19081.0f), ZeroVector3);

    CMarlin::Create(D3DXVECTOR3(-82303.4f, 0.0f, -56239.8f), ZeroVector3);
    CMarlin::Create(D3DXVECTOR3(-39297.0f, 0.0f, -12532.5f), ZeroVector3);
    CMarlin::Create(D3DXVECTOR3(34013.9f, 0.0f, 3090.2f), ZeroVector3);

    CGhost::Create(D3DXVECTOR3(-1343.6f, 470.8f, -89167.2f), ZeroVector3);
    CGhost::Create(D3DXVECTOR3(-66418.1f, 10247.0f, -52938.6f), ZeroVector3);

    // クラーケン
    if (!m_pKraken)
    {
        m_pKraken = CKraken::Create();
        m_pKraken->ChangeState(CKrakenStateNotAttack::Create());
    }
}

//=======================================================================================
// NPCの生成
//=======================================================================================
void CGame::CreateNPC()
{
    if (!m_pNpcFactory)
    {
        m_pNpcFactory = CNpcFactory::Create();
    }
}

//=======================================================================================
// マップの生成
//=======================================================================================
void CGame::CreateMap()
{
    if (!m_pMapFactory)
    {
        // マップ生成クラス
        m_pMapFactory = CMapFactory::Create();
    }

//    CTestModel::Create();
    CWaterFresnel::Create();
    CSky::Create();

    if (!m_pGimmickFactory)
    {
        m_pGimmickFactory = CGimmickFactory::Create();
    }
}

//=======================================================================================
// 情報表示
//=======================================================================================
void CGame::ShowInfo()
{
#ifdef _DEBUG
    //レンダラーで管理してるやつの情報
    ImGui::Begin("DebugInfo");

    if (ImGui::CollapsingHeader("WorldInfo"))
    {
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();    // デバイスの取得

        //重力の値
        ImGui::SliderFloat("Gravity", &m_fGravity, 0.0f, 50.0f);
        ImGui::Checkbox("Gauss", &m_bGaussFilter);

         ImGui::TreePop();
    }

    ImGui::End();
#endif // !_DEBUG
}

//=======================================================================================
// オブジェクト生成
//=======================================================================================
void CGame::CreateObject()
{
    CreateMap();
    CreatePlayer();
    CreateEnemy();
    CreateNPC();

}

//=======================================================================================
// フィルタの生成
//=======================================================================================
void CGame::CreateFilter()
{
    if (!m_pGaussFilter)
    {
        m_pGaussFilter = new CGaussFilter(GET_RENDERER_DEVICE);
        m_pGaussFilter->Load();
        m_pGaussFilter->Restore();
    }
}

//=======================================================================================
// Uiの生成
//=======================================================================================
void CGame::CreateUi()
{
    m_pGauge = CGauge::Create();
    CGaugebar::Create();
}