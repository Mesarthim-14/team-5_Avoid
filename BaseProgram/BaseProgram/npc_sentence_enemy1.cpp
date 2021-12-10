//=============================================================================
//
// エネミーの文章1 [npc_sentence_enemy1.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "npc_sentence_enemy1.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "npc_enemy_info.h"
#include "npc_factory.h"
#include "texture.h"
#include "polygon.h"
#include "camera.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SIZE            (D3DXVECTOR3(650.0f, 300.0f, 0.0f))
#define POS_Y_FIX       (700.0f)
#define SCREEN_CENTER_X (SCREEN_WIDTH*0.5f)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT*0.5f)

//=============================================================================
// コンストラクタ
//=============================================================================
CNpcSentenceEnemy1::CNpcSentenceEnemy1()
{
    m_apSentence.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CNpcSentenceEnemy1::~CNpcSentenceEnemy1()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CNpcSentenceEnemy1 * CNpcSentenceEnemy1::Create()
{
    // メモリ確保
    CNpcSentenceEnemy1* pNpc = new CNpcSentenceEnemy1;
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
HRESULT CNpcSentenceEnemy1::Init()
{
    CNpcEnemyInfo* pNpc = (CNpcEnemyInfo*)CManager::GetInstance()->GetGame()->GetNpcFactory()->GetNPC(CNpcFactory::NPC_TYPE_ENEMY_INFO);
    D3DXVECTOR3 pos = pNpc->GetPos();
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
    SetSceneInfo(D3DXVECTOR3(550.0f, 300.0f, 0.0f), SIZE);

    CScene2D::Init();
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_MESSAGE_BACK));

    // 文章の生成
    CreateSentence();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNpcSentenceEnemy1::Uninit()
{
    for (auto &pSentence : m_apSentence)
    {
        pSentence->Uninit();
    }
    m_apSentence.clear();

    CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNpcSentenceEnemy1::Update()
{
    CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CNpcSentenceEnemy1::Draw()
{
    CScene2D::Draw();

    // 文章の生成
    for (auto &pSentence : m_apSentence)
    {
        pSentence->Draw();
    }
}

//=============================================================================
// 文章の生成
//=============================================================================
void CNpcSentenceEnemy1::CreateSentence()
{
    CTexture *pTexture = GET_TEXTURE_PTR;
    D3DXVECTOR3 pos = GetPos();
    pos.y -= 50.0f;
    CPolygon* pPolygon = 
        CPolygon::Create(pos, D3DXVECTOR3(550.0f, 70.0f, 0.0f));
    pPolygon->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ENEMY_SENTENCE1));
    m_apSentence.push_back(pPolygon);
}