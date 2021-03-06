//=======================================================================================
//
// シーン2Dクラス [scene2d.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "keyboard.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "texture_animation.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CScene2D::CScene2D(PRIORITY Priority) : CSceneBase(Priority)
{
    m_fRotasion = 0.0f;
    m_fScaleNum = 0.0f;
    m_fSubFlashNum = 1.0f;
    m_fSubNum = 0.0f;
    m_fFadeSpeedNum = 0.0f;
    m_nFlashFlame = 0;
    m_bDisappearFlag = false;
    m_bFadeOut = false;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CScene2D::~CScene2D()
{

}

//=======================================================================================
// Sceneクラスの生成
//=======================================================================================
CScene2D* CScene2D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
    // オブジェクトを生成
    CScene2D* pScene = new CScene2D();

    // nullcheck
    if (pScene)
    {
        // 初期化処理
        pScene->SetSceneInfo(pos, size);
        pScene->Init();
        return pScene;
    }
    return nullptr;
}

//=======================================================================================
// Sceneクラスの生成 (Fade有り)
//=======================================================================================
CScene2D * CScene2D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const float &fFadeNum)
{
    // オブジェクトを生成
    CScene2D* pScene = new CScene2D();

    // !nullcheck
    if (pScene)
    {
        pScene->m_fFadeSpeedNum = fFadeNum;
        pScene->m_fSubFlashNum = 0.0f;
        float fAlpha = 0.0f;
        pScene->GetColor().a = 0.0f;
        pScene->m_bFadeOut = true;

        // 初期化処理
        pScene->SetSceneInfo(pos, size);
        pScene->Init();

        return pScene;
    }

    return nullptr;
}

//=======================================================================================
// ポリゴンの初期化
//=======================================================================================
HRESULT CScene2D::Init()
{
    // 頂点の生成
    CreateVertex();

    return S_OK;
}

//=======================================================================================
// ポリゴンの終了処理
//=======================================================================================
void CScene2D::Uninit()
{
    // 終了処理
    CSceneBase::Uninit();
}

//=======================================================================================
// ポリゴンの更新処理
//=======================================================================================
void CScene2D::Update()
{
    // 更新処理
    CSceneBase::Update();

    if (m_bFadeOut)
    {
        FadeOut(m_fFadeSpeedNum);
    }
}

//=======================================================================================
// ポリゴンの描画処理
//=======================================================================================
void CScene2D::Draw()
{
    // Rendererクラスからデバイスを取得
    LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //アルファテストを有効化
    pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    //アルファテスト基準値の設定
    pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

    //アルファテストの比較方法の設定(GREATERは基準値より大きい場合)
    pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

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

//======================================================
//色の取得
//======================================================
void CScene2D::SetColor(const D3DXCOLOR &col)
{
    VERTEX_2D *pVtx = nullptr;    //頂点情報へのポインタ
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();    // バッファ

    // 色の設定
    CSceneBase::SetColor(col);

    //頂点データ範囲をロックし、頂点バッファへのポインタを所得
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //頂点カラーの設定(0~255の数値で設定)
    pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r,g,b,aは0~255の範囲で決めること
    pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r:レッド g:グリーン　b:ブルー
    pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //aは、透明度を表している
    pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

    //頂点データをアンロック
    pVtxBuff->Unlock();
}

//=============================================
// 頂点の生成関数
//=============================================
void CScene2D::CreateVertex()
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

    // 頂点データをロックする
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    // 頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

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

//=============================================
// 頂点の設定
//=============================================
void CScene2D::SetVertexPos()
{
    // Rendererクラスからデバイスを取得
    LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();        // バッファ

    // 頂点情報を設定
    VERTEX_2D *pVtx = nullptr;
    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 size = GetSize();

    // 頂点データをロックする
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // 頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

    // 頂点データをアンロックする
    pVtxBuff->Unlock();

    // 頂点バッファの設定
    BindVtxBuff(pVtxBuff);
}

//=============================================
// アニメーション情報取得
//=============================================
void CScene2D::InitAnimation(const int &nPatternNum, const int &nSpeed, const int &nLoop)
{
    // 頂点情報を設定
    VERTEX_2D *pVtx = nullptr;
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();        // バッファ取得

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //テクスチャ座標を更新
    pVtx[0].tex = D3DXVECTOR2((float)(1.0f / nPatternNum)*(float)0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2((float)(1.0f / nPatternNum)*(float)0.0f + (float)(1.0f / nPatternNum), 0.0f);
    pVtx[2].tex = D3DXVECTOR2((float)(1.0f / nPatternNum)*(float)0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2((float)(1.0f / nPatternNum)*(float)0.0f + (float)(1.0f / nPatternNum), 1.0f);

    // テクスチャ座標を渡す
    D3DXVECTOR2 tex[NUM_VERTEX] = {};
    for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        tex[nCount] = pVtx[nCount].tex;
    }

    // テクスチャアニメーション生成
    CTextureAnimation *pTextureAnimation = CTextureAnimation::Create(tex);
    pTextureAnimation->InitAnimationInfo(nPatternNum, nSpeed, nLoop);
    SetTextureAnimationPtr(pTextureAnimation);

    // 頂点バッファをアンロックする
    pVtxBuff->Unlock();
}

//=============================================
// アニメーション更新関数
//=============================================
void CScene2D::UpdateAnimation()
{
    // テクスチャポインタ取得
    CTextureAnimation *pTextureAnimation = GetTextureAnimationPtr();
    // 頂点情報を設定
    VERTEX_2D *pVtx = nullptr;
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();        // バッファ取得

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // テクスチャ座標の設定
    for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].tex = pTextureAnimation->GetTex(nCount);
    }

    // 頂点バッファをアンロックする
    pVtxBuff->Unlock();
}

//=============================================
// テクスチャのスクロール情報を取得
//=============================================
void CScene2D::InitScroll(const int &nSpeed, const float &fDivision)
{
    // 頂点情報を設定
    VERTEX_2D *pVtx = nullptr;
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();        // バッファ取得

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // テクスチャ座標を渡す
    D3DXVECTOR2 tex[NUM_VERTEX] = {};
    for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        tex[nCount] = pVtx[nCount].tex;
    }

    // テクスチャアニメーション生成
    CTextureAnimation *pTextureAnimation = CTextureAnimation::Create(tex);
    pTextureAnimation->InitScroll(nSpeed, fDivision);
    SetTextureAnimationPtr(pTextureAnimation);

    // 頂点バッファをアンロックする
    pVtxBuff->Unlock();
}

//=============================================
// テクスチャのスクロール情報を更新
//=============================================
void CScene2D::UpdateScroll()
{
    // テクスチャポインタ取得
    CTextureAnimation *pTextureAnimation = GetTextureAnimationPtr();
    if (pTextureAnimation)
    {
        // テクスチャが更新されていたら
        if (pTextureAnimation->GetUpdate())
        {
            // 頂点情報を設定
            VERTEX_2D *pVtx = nullptr;
            LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();        // バッファ取得

            // 頂点バッファをロックし、頂点情報へのポインタを取得
            pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

            // テクスチャ座標の設定
            for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
            {
                pVtx[nCount].tex = pTextureAnimation->GetTex(nCount);
            }

            // 頂点バッファをアンロックする
            pVtxBuff->Unlock();
        }
    }
}

//======================================================
// 拡大関数
//======================================================
void CScene2D::ScaleUp(const float &fScaleUp)
{
    // 情報取得
    D3DXVECTOR3 pos = GetPos();        // 座標
    D3DXVECTOR3 size = GetSize();    // サイズ
    m_fScaleNum += fScaleUp;

    VERTEX_2D*pVtx = nullptr;    //頂点情報へのポインタ
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

    //頂点データ範囲をロックし、頂点バッファへのポインタを所得
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // 頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(pos.x - (size.x / 2 * m_fScaleNum), pos.y - (size.y / 2 * m_fScaleNum), 0.0f);
    pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x / 2 * m_fScaleNum), pos.y - (size.y / 2 * m_fScaleNum), 0.0f);
    pVtx[2].pos = D3DXVECTOR3(pos.x - (size.x / 2 * m_fScaleNum), pos.y + (size.y / 2 * m_fScaleNum), 0.0f);
    pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x / 2 * m_fScaleNum), pos.y + (size.y / 2 * m_fScaleNum), 0.0f);

    //頂点データをアンロック
    pVtxBuff->Unlock();
}

//======================================================
// ローテーションの取得
//======================================================
void CScene2D::SetRotation(const float& rotasion)
{
    // 情報取得
    D3DXVECTOR3 pos = GetPos();         // 座標
    D3DXVECTOR3 size = GetSize()*0.5f;  // サイズ

    VERTEX_2D*pVtx = nullptr;    //頂点情報へのポインタ
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

    //頂点データ範囲をロックし、頂点バッファへのポインタを所得
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // 中心から頂点の距離
    float fDistance = sqrtf(powf(size.x, 2) + powf(size.y, 2));
    // 中心から右上の頂点の角度
    float fAngle = atan2f(size.y, size.x);
    // 中心から左上の頂点の角度
    float  fAngle2 = atan2f(size.y, -size.x);

    // 頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(pos.x + (cosf(-fAngle2 + rotasion) * fDistance), pos.y + (sinf(-fAngle2 + rotasion) * fDistance), 0);
    pVtx[1].pos = D3DXVECTOR3(pos.x + (cosf(-fAngle + rotasion) * fDistance), pos.y + (sinf(-fAngle + rotasion) * fDistance), 0);
    pVtx[2].pos = D3DXVECTOR3(pos.x + (cosf(fAngle2 + rotasion) * fDistance), pos.y + (sinf(fAngle2 + rotasion) * fDistance), 0);
    pVtx[3].pos = D3DXVECTOR3(pos.x + (cosf(fAngle + rotasion)  * fDistance), pos.y + (sinf(fAngle + rotasion)  * fDistance), 0);
    
    pVtxBuff->Unlock();
}

//=============================================
// 拡大の値設定
//=============================================
void CScene2D::SetScale(const float &fScale)
{
    m_fScaleNum = fScale;
}

//====================================================================
// ポリゴンの点滅
//====================================================================
void CScene2D::FlashPolygon(const float &fFlashFlame)
{
    // 頂点情報を設定
    VERTEX_2D *pVtx = nullptr;
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // 点滅の反転状態
    if (!m_bDisappearFlag)
    {
        // カラーの減算
        m_fSubFlashNum += fFlashFlame;
    }
    else
    {
        // カラーの減算
        m_fSubFlashNum -= fFlashFlame;
    }

    // 上限に行ったら
    if (m_fSubFlashNum >= 1.0f)
    {
        m_fSubFlashNum = 1.0f;
        m_bDisappearFlag = true;
    }
    if (m_fSubFlashNum <= 0.0f)
    {
        m_fSubFlashNum = 0.0f;
        m_bDisappearFlag = false;
    }

    // カラー情報の更新
    D3DXCOLOR color = GetColor();

    // 頂点カラーの設定
    pVtx[0].col = D3DXCOLOR(color.r, color.g, color.b, m_fSubFlashNum);    // 左上頂点の色    透明度255
    pVtx[1].col = D3DXCOLOR(color.r, color.g, color.b, m_fSubFlashNum);    // 右上頂点の色    透明度255
    pVtx[2].col = D3DXCOLOR(color.r, color.g, color.b, m_fSubFlashNum);    // 左下頂点の色    透明度255
    pVtx[3].col = D3DXCOLOR(color.r, color.g, color.b, m_fSubFlashNum);    // 右下頂点の色    透明度255

    // 頂点バッファをアンロックする
    pVtxBuff->Unlock();
}

//====================================================================
// フェードアウト
//====================================================================
void CScene2D::FadeOut(const float &fSpeed)
{
    // 頂点情報を設定
    VERTEX_2D *pVtx = nullptr;
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

    // 透明度の値
    m_fSubFlashNum += fSpeed;

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // α値を足す
    GetColor().a = m_fSubFlashNum;

    // カラー情報の更新
    D3DXCOLOR color = GetColor();

    // 頂点カラーの設定
    pVtx[0].col = D3DXCOLOR(color.r, color.g, color.b, color.a);    // 左上頂点の色    透明度255
    pVtx[1].col = D3DXCOLOR(color.r, color.g, color.b, color.a);    // 右上頂点の色    透明度255
    pVtx[2].col = D3DXCOLOR(color.r, color.g, color.b, color.a);    // 左下頂点の色    透明度255
    pVtx[3].col = D3DXCOLOR(color.r, color.g, color.b, color.a);    // 右下頂点の色    透明度255

    // 頂点バッファをアンロックする
    pVtxBuff->Unlock();

    // 引く値が無くなったら
    if (m_fSubFlashNum > 1.0f)
    {
        m_fSubFlashNum = 1.0;
        m_bFadeOut = false;
    }
}