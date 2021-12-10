//=============================================================================
//
// 大砲の管理クラス [cannon_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "cannon_manager.h"
#include "cannon.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "key_e.h"
#include "keyboard.h"
#include "input.h"
#include "cannon_bullet.h"
#include "player.h"
#include "camera_game.h"
#include "production_cannon_manager.h"
#include "state_camera_cannon.h"
#include "state_player_cannon.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCannonManager::CCannonManager()
{
    m_apCannon.clear();
    m_nAttackNum = 0;
    m_pKeyE = nullptr;
    m_nTargetCannon = 0;
    m_pProduction = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCannonManager::~CCannonManager()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CCannonManager * CCannonManager::Create()
{
    // メモリ確保
    CCannonManager *pCheckPoint = new CCannonManager;

    // !nullcheck
    if (pCheckPoint)
    {
        // 初期化処理
        pCheckPoint->Init();
        return pCheckPoint;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCannonManager::Init()
{
    CreateCannon(); // 旗の生成
    CreateUi();     // UIの生成

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCannonManager::Uninit()
{
    if (m_apCannon.size() > 0)
    {
        for (auto &pCannon : m_apCannon)
        {
            // 終了処理
            pCannon->Uninit();
        }

        m_apCannon.clear();
    }
    if (m_pKeyE)
    {
        m_pKeyE->Uninit();
        m_pKeyE = nullptr;
    }
}

//=============================================================================
// 更新処理
//=============================================================================
void CCannonManager::Update()
{
    // 大砲の当たり判定
    CannonCollision();

    if (m_pProduction)
    {
        // 更新処理
        m_pProduction->Update();

        // 終了予定なら削除
        if (m_pProduction->GetEnd())
        {
            delete m_pProduction;
            m_pProduction = nullptr;
        }
    }
}

//=============================================================================
// 旗の生成
//=============================================================================
void CCannonManager::CreateCannon()
{
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(49157.9f, 1008.6f, -5936.7f), D3DXVECTOR3(0.0f, D3DXToRadian(-60.0f), 0.0f)));
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(23678.6f, 5073.4f, -46970.4f), D3DXVECTOR3(0.0f, D3DXToRadian(-0.0f), 0.0f)));
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(-56682.4f, 5202.3f, -14457.8f), D3DXVECTOR3(0.0f, D3DXToRadian(100.0f), 0.0f)));
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(6866.4f, 800.4f, 44881.4f), D3DXVECTOR3(0.0f, D3DXToRadian(190.0f), 0.0f)));
    m_apCannon.push_back(CCannon::Create(D3DXVECTOR3(40178.6f, 800.4f, 25546.3f), D3DXVECTOR3(0.0f, D3DXToRadian(220.0f), 0.0f)));
}

//=============================================================================
// Uiの生成
//=============================================================================
void CCannonManager::CreateUi()
{
    // インスタンス生成
    if (!m_pKeyE)
    {
        m_pKeyE = CKeyE::Create();
    }
}

//=============================================================================
// 大砲の当たり判定
//=============================================================================
void CCannonManager::CannonCollision()
{
    // 大砲の数
    size_t size = m_apCannon.size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        // 大砲の当たり判定
        if (m_apCannon.at(nCount)->Collision())
        {
            // 対象の番号を取得
            m_nTargetCannon = nCount;

            // Eキー表示
            m_pKeyE->SetDrawFlag(true);

            // ボタンの判定
            InputJudge();
            return;
        }
    }

    // Eキー非表示
    m_pKeyE->SetDrawFlag(false);
}

//=============================================================================
// ボタンの判定
//=============================================================================
void CCannonManager::InputJudge()
{
    // 発射ボタンが押されたら
    if (CLibrary::KeyboardTrigger(DIK_E))
    {
        CreateBullet();
    }
}

//=============================================================================
// 弾の発射
//=============================================================================
void CCannonManager::CreateBullet()
{
    // 演出へ以降
    SetProductionMode();

    // 使用状態にする
    m_apCannon.at(m_nTargetCannon)->SetUseFlag();
}

//=============================================================================
// 演出の設定
//=============================================================================
void CCannonManager::SetProductionMode()
{
    // 大砲の演出
    if (!m_pProduction)
    {
        m_pProduction = CProductionCannonManager::Create();
    }
}
