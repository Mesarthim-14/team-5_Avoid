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

//=============================================================================
// マクロ定義
//=============================================================================
#define SIZE        (D3DXVECTOR3(1200.0f, 700.0f, 0.0f))
#define POS_Y_FIX   (700.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CNpcSentenceEnemy1::CNpcSentenceEnemy1()
{
    m_pTexture = nullptr;
    m_pSurface = nullptr;
    m_pPolygon.clear();
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

    pos.y += POS_Y_FIX;
    SetSceneInfo(pos, SIZE);

    CBillboard::Init();
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_MESSAGE_BACK));

    //カラー情報を格納するマルチレンダーターゲットで使用するテクスチャーを作成する
//    D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT,
//        1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
//        &m_pTexture);
//    //カラー情報を格納するマルチレンダーターゲットサーフェイスを作成する
//    m_pTexture->GetSurfaceLevel(0, &m_pSurface);
//
//    m_pPolygon.push_back(CPolygon::Create(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR3(600.0f, 200.0f, 0.0f)));
//    m_pPolygon.at(0)->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
//
//    m_pPolygon.push_back(CPolygon::Create(D3DXVECTOR3(200.0f, 500.0f, 0.0f), D3DXVECTOR3(600.0f, 200.0f, 0.0f)));
//    m_pPolygon.at(1)->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNpcSentenceEnemy1::Uninit()
{
//    if (m_pTexture)
//    {
//        m_pTexture->Release();
//        m_pTexture = nullptr;
//    }
//    if (m_pSurface)
//    {
//        m_pSurface->Release();
//        m_pSurface = nullptr;
//    }
//
//    for (auto &pPolygon : m_pPolygon)
//    {
//        pPolygon->Uninit();
//        pPolygon = nullptr;
//    }
//    m_pPolygon.clear();

    CBillboard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNpcSentenceEnemy1::Update()
{
    CBillboard::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CNpcSentenceEnemy1::Draw()
{
//    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
//
//    //現在のレンダーターゲットサーフェイスを取得
//    LPDIRECT3DSURFACE9 OldSurface = nullptr;
//    pDevice->GetRenderTarget(0, &OldSurface);
//    // 更新した波マップを参照し水面を凸凹にしてレンダリングする
//    pDevice->SetRenderTarget(0, m_pSurface);
//    pDevice->Clear(0L,
//        NULL,
//        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
//        D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
//        1.0f,
//        0L);
//
//    for (auto &pPolygon : m_pPolygon)
//    {
//        pPolygon->Draw();
//    }
//
//    pDevice->SetRenderTarget(0, OldSurface);
//    //	pDevice->SetRenderTarget(1, NULL);
//    if (OldSurface)
//    {
//        OldSurface->Release();
//        OldSurface = nullptr;
//    }
//    SetTexture(m_pTexture, 1);

    CBillboard::Draw();
}
