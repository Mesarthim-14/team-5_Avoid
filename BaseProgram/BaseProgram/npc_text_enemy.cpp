//=============================================================================
//
// エネミーの会話(エネミー) [npc_text_enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "npc_text_enemy.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "npc_sentence_enemy1.h"
#include "npc_sentence_enemy2.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CNpcTextEnemy::CNpcTextEnemy()
{
    m_nCounter = 0;
    m_bEnd = false;
    m_pSentence = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CNpcTextEnemy::~CNpcTextEnemy()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CNpcTextEnemy * CNpcTextEnemy::Create()
{
    CNpcTextEnemy* pNpc = new CNpcTextEnemy;
    if (pNpc)
    {
        // 初期化処理
        pNpc->Init();
        return pNpc;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNpcTextEnemy::Init()
{
    (this->*m_CreateSentence.at(m_nCounter))();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNpcTextEnemy::Uninit()
{
    CNpcText::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNpcTextEnemy::Update()
{
    // テキストの更新処理
    CNpcText::Update();

    if (CLibrary::KeyboardTrigger(DIK_E))
    {
        // 演出のステップが演出数を上回っていたら
        if (m_nCounter >= (int)m_CreateSentence.size())
        {
            // 終了
            if (m_pSentence)
            {
                m_pSentence->Uninit();
                m_pSentence = nullptr;
            }

            m_bEnd = true;
        }
        else
        {// 次の演出へ
            (this->*m_CreateSentence.at(m_nCounter))();
        }
    }
}

//=============================================================================
// 文章の生成
//=============================================================================
void CNpcTextEnemy::CreateSentence1()
{
    if (!m_pSentence)
    {
        m_pSentence = CNpcSentenceEnemy1::Create();
    }
    m_nCounter++;
}

//=============================================================================
// 文章の生成
//=============================================================================
void CNpcTextEnemy::CreateSentence2()
{
    if (m_pSentence)
    {
        m_pSentence->Uninit();
        m_pSentence = nullptr;
    }

    m_pSentence = CNpcSentenceEnemy2::Create();
    m_nCounter++;
}