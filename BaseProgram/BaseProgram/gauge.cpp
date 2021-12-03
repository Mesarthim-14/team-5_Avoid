//=====================================================================
//
//    ゲージ処理[gauge.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "gauge.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "keyboard.h"

float CGauge::m_fHP = 0.0f;
float CGauge::m_fSave = 0.0f;
bool CGauge::m_bHitDown = false;
bool CGauge::m_bHitUp = false;
//=====================================================================
// マクロ定義
//=====================================================================
#define POS         (D3DXVECTOR3(80.0f,575.0f,0.0f))
#define SIZE        (D3DXVECTOR3(150.0f,450.0f,0.0f))
#define MAX_GAUGE   (100.0f)

//=====================================================================
// コンストラクタ
//=====================================================================
CGauge::CGauge(PRIORITY priority) : CScene2D(priority)
{
    m_fHP = 60.0f;
    m_fDown = 0.0f;
    m_fUp = 0.0f;
}

//=====================================================================
// デストラクタ
//=====================================================================
CGauge::~CGauge()
{

}

//=====================================================================
// 生成処理
//=====================================================================
CGauge * CGauge::Create()
{
    CGauge * pGauge = new CGauge(PRIORITY_UI);

    if (pGauge)
    {
        pGauge->SetSceneInfo(POS, SIZE);
        pGauge->Init();
        return pGauge;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
HRESULT CGauge::Init()
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GAUGE));
    // ゲージの設定処理
    SetVertexGauge();
    return S_OK;
}

//=====================================================================
// 終了処理
//=====================================================================
void CGauge::Uninit()
{
    CScene2D::Uninit();
}

//=====================================================================
// 更新処理
//=====================================================================
void CGauge::Update()
{
    CScene2D::Update();
    // テスト・ゲージの増加＆現象処理
    SetDownUp();
}

//=====================================================================
// 描画処理
//=====================================================================
void CGauge::Draw()
{
    CScene2D::Draw();
}

//=====================================================================
// テクスチャ情報
//=====================================================================
void CGauge::SetVertexGauge()
{
    // Rendererクラスからデバイスを取得
    LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;        // バッファ

                                                    // 頂点バッファの生成
    pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_MANAGED,
        &pVtxBuff,
        nullptr);

    // 頂点情報を設定
    VERTEX_2D *pVtx = nullptr;
    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 size = GetSize();
    D3DXCOLOR color = GetColor();
    // ゲージの量の計算
    float fDown = MAX_GAUGE / m_fHP;

    // 頂点データをロックする
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f - (1.0f / fDown));
    pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f - (1.0f / fDown));
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    size.y *= (1.0f / fDown);

    // 頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(pos.x - (size.x / 2.0f), pos.y - size.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x / 2.0f), pos.y - size.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(pos.x - (size.x / 2.0f), pos.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x / 2.0f), pos.y, 0.0f);

    // rhwの設定
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    // 頂点カラーの設定
    pVtx[0].col = color;
    pVtx[1].col = color;
    pVtx[2].col = color;
    pVtx[3].col = color;

    // 頂点データをアンロックする
    pVtxBuff->Unlock();

    // 頂点バッファの設定
    BindVtxBuff(pVtxBuff);
}

//=====================================================================
// 増加現象処理
//=====================================================================
void CGauge::SetDownUp()
{
    // 減らす処理
    if (m_fHP >= 0.0f)
    {
        if (m_bHitDown)
        {
            // 減らしたい値
            m_fDown = GetHP();
            m_bHitDown = false;
        }
        if (m_fDown >= 0.0f)
        {
            m_fHP -= 1.0f;
            SetVertexGauge();
            m_fDown -= 1.0f;
            // 0以下に行かないようにする　
            if (m_fHP < 0.0f)
            {
                m_fHP = 0.0f;
            }
        }
    }
    // 増える処理
    if (m_fHP <= MAX_GAUGE)
    {
        if (m_bHitUp)
        {
            // 増やしたい値
            m_fUp = GetHP();
            m_bHitUp = false;
        }
        // 指定の数値分上げる
        if (m_fUp >= 0.0f)
        {
            m_fHP += 1.0f;
            SetVertexGauge();
            m_fUp -= 1.0f;
            // 100以上に行かないようにする
            if (m_fHP > 100.0f)
            {
                m_fHP = 100.0f;
            }
        }
    }
}