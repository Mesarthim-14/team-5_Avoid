//=======================================================================================
//
// 大砲時の演出 [production_cannon_manager.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "production_cannon_manager.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "resource_manager.h"
#include "production_cannon.h"
#include "production_angry_kraken.h"
#include "kraken.h"
#include "game.h"
#include "production_dead_kraken.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CProductionCannonManager::CProductionCannonManager()
{
    m_pProduction = nullptr;
    m_bEnd = false;
    m_nStep = 0;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CProductionCannonManager::~CProductionCannonManager()
{
}

//=======================================================================================
// インスタンス生成
//=======================================================================================
CProductionCannonManager* CProductionCannonManager::Create()
{
    // メモリ確保
    CProductionCannonManager* pProduction = new CProductionCannonManager;
    if (pProduction)
    {
        // インスタンス生成
        pProduction->Init();
        return pProduction;
    }

    return nullptr;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
void CProductionCannonManager::Init()
{
    (this->*m_CreateProduction.at(m_nStep))();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
void CProductionCannonManager::Uninit()
{
    if (m_pProduction)
    {
        m_pProduction->Uninit();
        m_pProduction = nullptr;
    }
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CProductionCannonManager::Update()
{
    if (m_pProduction)
    {
        // 演出の更新処理
        m_pProduction->Update();
        if (m_pProduction->GetEnd())
        {// 演出が終了したら
            // 終了処理
            m_pProduction->Uninit();
            m_pProduction = nullptr;

            // 演出のステップが演出数を上回っていたら
            if (m_nStep >= (int)m_CreateProduction.size())
            {// 終了
                m_bEnd = true;
            }
            else
            {// 次の演出へ
                (this->*m_CreateProduction.at(m_nStep))();
            }
        }
    }
}

//=======================================================================================
// 大砲を打つときの演出生成
//=======================================================================================
void CProductionCannonManager::CreateProductionCannonShot()
{
    if (!m_pProduction)
    {
        // 大砲の発射クラス
        m_pProduction = CProductionCannon::Create();
    }
    m_nStep++;
}

//=======================================================================================
// 怒ったときの演出
//=======================================================================================
void CProductionCannonManager::CreateProductionAngry()
{
    if (!CManager::GetInstance()->GetGame()->GetKraken()->GetDead())
    {
        if (!m_pProduction)
        {
            // 大砲の発射クラス
            m_pProduction = CProductionAngryKraken::Create();
        }
    }
    else
    {
        // 大砲の発射クラス
        m_pProduction = CProductionDeadKraken::Create();
    }
    m_nStep++;
}