//=========================================================
//
// ボスのHPバークラス	[boss_hp_bar.cpp]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// インクルード
//=========================================================
#include "boss_hp_bar.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"

//=========================================================
// マクロ定義
//=========================================================
#define SIZE    (D3DXVECTOR3(635.0f, 12.0f, 0.0f))
#define POS     (D3DXVECTOR3((SCREEN_WIDTH / 2) - (598.0f * 0.5f), 90.0f, 0.0f))

//=========================================================
// ポリゴン生成
//=========================================================
CBossHpBar * CBossHpBar::Create(const int& nLife)
{
    // メモリ確保
    CBossHpBar *pPtr = new CBossHpBar(PRIORITY_UI);

    if (pPtr)
    {
        pPtr->m_nGage = pPtr->m_nMaxGage = nLife;
        pPtr->Init();   // 初期化
    }

    return pPtr;
}

//=========================================================
// コンストラクタ
//=========================================================
CBossHpBar::CBossHpBar(PRIORITY Priority) : CSceneBase(Priority)
{
    m_nMaxGage = 0;
    m_nGage = m_nMaxGage;
}

//=========================================================
// デストラクタ
//=========================================================
CBossHpBar::~CBossHpBar()
{
}

//=========================================================
// 初期化処理
//=========================================================
HRESULT CBossHpBar::Init()
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BOSS_HP_BAR));

    // 初期化処理
    CreateVertex(POS, SIZE);       // 座標・サイズ
    SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));	// 色の設定

    return S_OK;
}

//=========================================================
// 終了処理
//=========================================================
void CBossHpBar::Uninit()
{
    // 終了処理
    CSceneBase::Uninit();
}

//=========================================================
// 更新処理
//=========================================================
void CBossHpBar::Update()
{

}

//=========================================================
// 描画処理
//=========================================================
void CBossHpBar::Draw()
{
}

//=========================================================
// 頂点設定
//=========================================================
void CBossHpBar::SetGageVertex()
{
    VERTEX_2D *pVtx;	// 頂点情報へのポインタ
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

    // 頂点バッファをロック
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // バーの座標とサイズ
    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 size = GetSize();

    // HPが減った場合、画像の右側から描画をやめる
    pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y - size.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3((pos.x + (size.x )*((float)m_nGage / m_nMaxGage)), pos.y - size.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3((pos.x + (size.x )*((float)m_nGage / m_nMaxGage)), pos.y + size.y, 0.0f);

    // 頂点データをアンロックする
    pVtxBuff->Unlock();
}

//=========================================================
// 頂点の生成
//=========================================================
void CBossHpBar::CreateVertex(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
    // レンダラーの情報を受け取る
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;

    // 頂点バッファの生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_MANAGED,
        &pVtxBuff,
        nullptr);

    SetPos(pos);
    SetSize(size);

    //頂点情報へのポインタ
    VERTEX_2D *pVtx;

    // 頂点データの範囲をロックし、頂点バッファへのポインタを取得
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // HPが減った場合、画像の右側から描画をやめる
    pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y - size.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3((pos.x + (size.x)*((float)m_nGage / m_nMaxGage)), pos.y - size.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3((pos.x + (size.x)*((float)m_nGage / m_nMaxGage)), pos.y + size.y, 0.0f);

    //rhwの設定（値は1.0で設定する）
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //頂点カラーを設定（0～255の値で設定する）
    pVtx[0].col = WhiteColor;
    pVtx[1].col = WhiteColor;
    pVtx[2].col = WhiteColor;
    pVtx[3].col = WhiteColor;

    //テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    //頂点データをアンロックする
    pVtxBuff->Unlock();

    // 頂点情報を渡す
    BindVtxBuff(pVtxBuff);
}

//=========================================================
// HP減算
//=========================================================
void CBossHpBar::SubHp(const int& nNum)
{
    m_nGage -= nNum;
    SetGageVertex();
}


void CBossHpBar::Render()
{
    // Rendererクラスからデバイスを取得
    LPDIRECT3DDEVICE9 pD3DDevice = GET_RENDERER_DEVICE;

    //アルファテストを有効化
    pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    // 頂点バッファをデータストリームに設定
    pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

    // 頂点フォーマットの設定
    pD3DDevice->SetFVF(FVF_VERTEX_2D);

    // テクスチャの設定
    pD3DDevice->SetTexture(0, GetTexture());

    // ポリゴンの描画
    pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
        0,
        NUM_POLYGON);

    //アルファテストを無効化
    pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

    // テクスチャの設定
    pD3DDevice->SetTexture(0, nullptr);

}
