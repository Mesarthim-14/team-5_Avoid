//=============================================================================
//
// 波クラス [wave.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "wave.h"
#include "resource_manager.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CWave::CWave(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters) : CShaderSquare(pd3dDevice, pd3dParameters)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
    for (int nCount = 0; nCount < 2; nCount++)
    {
        m_pWaveMapTexture[nCount] = nullptr;
        m_pWaveMapSurface[nCount] = nullptr;
    }
    m_pBumpMapTexture = nullptr;
    m_pBumpMapSurface = nullptr;
    m_RenderTargetIndex = 0;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CWave::CWave(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height) : CShaderSquare(pd3dDevice, Width, Height)
{
    m_pd3dDevice = pd3dDevice;

    m_pEffect = nullptr;

    for (int nCount = 0; nCount < 2; nCount++)
    {
        m_pWaveMapTexture[nCount] = nullptr;
        m_pWaveMapSurface[nCount] = nullptr;
    }

    m_pBumpMapTexture = nullptr;
    m_pBumpMapSurface = nullptr;

    m_RenderTargetIndex = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CWave::~CWave()
{
    // エフェクト解放
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }

    // 終了処理
    Uninit();
}

//=============================================================================
// 終了処理
//=============================================================================
void CWave::Uninit()
{
    if (m_pEffect)
    {
        m_pEffect->OnLostDevice();
    }

    //波マップ
    for (int nCount = 0; nCount < 2; nCount++)
    {
        if (m_pWaveMapTexture[nCount])
        {
            m_pWaveMapTexture[nCount]->Release();
            m_pWaveMapTexture[nCount] = nullptr;
        }
        if (m_pWaveMapSurface[nCount])
        {
            m_pWaveMapSurface[nCount]->Release();
            m_pWaveMapSurface[nCount] = nullptr;
        }
    }
    if (m_pBumpMapTexture)
    {
        m_pBumpMapTexture->Release();
        m_pBumpMapTexture = nullptr;
    }
    if (m_pBumpMapSurface)
    {
        m_pBumpMapSurface->Release();
        m_pBumpMapSurface = nullptr;
    }

    m_RenderTargetIndex = 0;
}

//=============================================================================
//デバイスがリストアしたときにコールする関数
//=============================================================================
void CWave::Restore()
{
    if (m_pEffect)
    {
        m_pEffect->OnResetDevice();

        for (int nCount = 0; nCount < 2; nCount++)
        {
            // 描画対象の波マップテクスチャを生成
            D3DXCreateTexture(m_pd3dDevice,
                (DWORD)CShaderSquare::GetWidth(),    // テクスチャの大きさ
                (DWORD)CShaderSquare::GetHeight(),    // テクスチャの大きさ
                1,                                    // ミニマップのレベル
                D3DUSAGE_RENDERTARGET,
                D3DFMT_G16R16F,
                D3DPOOL_DEFAULT,
                &m_pWaveMapTexture[nCount]);

            // テクスチャからサーフェスへのポインタを取得
            m_pWaveMapTexture[nCount]->GetSurfaceLevel(0, &m_pWaveMapSurface[nCount]);
        }

        // 波マップを黒で初期化
        // 現在のレンダーターゲットを取得
        LPDIRECT3DSURFACE9 OldSurface = nullptr;
        m_pd3dDevice->GetRenderTarget(0, &OldSurface);

        // バックバッファの深度バッファを取得
        LPDIRECT3DSURFACE9 OldDepthStencilSurface = nullptr;
        m_pd3dDevice->GetDepthStencilSurface(&OldDepthStencilSurface);

        //デプスバッファは使用しないので無効にする
        m_pd3dDevice->SetDepthStencilSurface(nullptr);

        for (int nCount = 0; nCount < 2; nCount++)
        {
            // レンダーターゲットを指定
            m_pd3dDevice->SetRenderTarget(0, m_pWaveMapSurface[nCount]);
            m_pd3dDevice->Clear(
                0,                            // クリアする矩形領域の数
                NULL,                        // 矩形領域
                D3DCLEAR_TARGET,
                BlackColor,                    // 黒
                1.0f,                        // Zバッファのクリア値
                0                            // ステンシルバッファのクリア値
            );
        }

        // レンダーターゲットをバックバッファに戻す
        m_pd3dDevice->SetRenderTarget(0, OldSurface);
        if (OldSurface)
        {
            // サーフェス情報の開放
            OldSurface->Release();
        }

        // バックバッファの深度バッファを戻す
        m_pd3dDevice->SetDepthStencilSurface(OldDepthStencilSurface);
        if (OldDepthStencilSurface)
        {
            // 深度バッファの開放
            OldDepthStencilSurface->Release();
        }

        // バンプマップ用のターゲットテクスチャ生成
        D3DXCreateTexture(m_pd3dDevice,
            (DWORD)CShaderSquare::GetWidth(),
            (DWORD)CShaderSquare::GetHeight(),
            1,
            D3DUSAGE_RENDERTARGET,
            D3DFMT_A8R8G8B8,
            D3DPOOL_DEFAULT,
            &m_pBumpMapTexture);
        // サーフェス情報取得
        m_pBumpMapTexture->GetSurfaceLevel(0, &m_pBumpMapSurface);
    }
}

//=============================================================================
// シェーダロード
//=============================================================================
HRESULT CWave::Load()
{
    D3DCAPS9 caps;
    HRESULT hr;

    m_pd3dDevice->GetDeviceCaps(&caps);
    if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
    {
        hr = CShaderSquare::Load();
        if (FAILED(hr))
            return -1;

        //シェーダーの初期化
        LPD3DXBUFFER pErr = nullptr;
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/wave.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pTexOffset = m_pEffect->GetParameterByName(nullptr, "TexOffset");
        m_pSpringPower = m_pEffect->GetParameterByName(nullptr, "SpringPower");
        m_pAddWavePos = m_pEffect->GetParameterByName(nullptr, "AddWavePos");
        m_pAddWaveHeight = m_pEffect->GetParameterByName(nullptr, "AddWaveHeight");

        m_pEffect->SetTechnique(m_pTechnique);

        D3DXVECTOR2 Size;
        Size.x = 1.0f / CShaderSquare::GetWidth();
        Size.y = 1.0f / CShaderSquare::GetHeight();
        m_pEffect->SetFloatArray(m_pTexOffset, (float*)&Size, sizeof(D3DXVECTOR2));
    }
    else
    {
        return -3;
    }

    return S_OK;
}

//=============================================================================
// 波の速度設定
//=============================================================================
void CWave::SetWaveSpeed(float SpringPower)
{
    if (m_pEffect)
    {
        m_pEffect->SetFloat(m_pSpringPower, SpringPower);
    }
}

//=============================================================================
// 波の追加
//=============================================================================
void CWave::AddWave(float Pos_X, float Pos_Y, float Height)
{
    if (m_pEffect)
    {
        //波を追加する位置を設定
        D3DXVECTOR2 AddWavePos = D3DXVECTOR2(Pos_X, Pos_Y);
        m_pEffect->SetValue(m_pAddWavePos, &AddWavePos, sizeof(D3DXVECTOR2));

        //追加する波の高さを設定する
        m_pEffect->SetFloat(m_pAddWaveHeight, Height);
    }
}

//=============================================================================
// 描画処理
//=============================================================================
LPDIRECT3DTEXTURE9 CWave::Draw()
{
    if (m_pEffect)
    {
        // ビューポート変数
        D3DVIEWPORT9 OldViewport, NewViewport;

        //ビューポートを波マップのサイズに合わせる
        m_pd3dDevice->GetViewport(&OldViewport);
        CopyMemory(&NewViewport, &OldViewport, sizeof(D3DVIEWPORT9));
        NewViewport.Width = (DWORD)CShaderSquare::GetWidth();
        NewViewport.Height = (DWORD)CShaderSquare::GetHeight();
        // 新しくビューポート設定
        m_pd3dDevice->SetViewport(&NewViewport);
    
        //現在のレンダーターゲットサーフェイスを取得
        LPDIRECT3DSURFACE9 OldSurface = nullptr;
        m_pd3dDevice->GetRenderTarget(0, &OldSurface);

        // 現在のサーフェス取得
        LPDIRECT3DSURFACE9 OldDepthStencilSurface = nullptr;
        m_pd3dDevice->GetDepthStencilSurface(&OldDepthStencilSurface);
        //デプスバッファを使用しないので無効にする(注意２)
        m_pd3dDevice->SetDepthStencilSurface(nullptr);

        // レンダーターゲットの番号設定
        m_RenderTargetIndex = 1 - m_RenderTargetIndex;
        // レンダーターゲットをセットする
        m_pd3dDevice->SetRenderTarget(0, m_pWaveMapSurface[1 - m_RenderTargetIndex]);
        // 波マップをテクスチャーステージ０にセットする
        m_pd3dDevice->SetTexture(0, m_pWaveMapTexture[m_RenderTargetIndex]);

        // 波マップの更新
        m_pEffect->Begin(nullptr, 0);
        m_pEffect->BeginPass(0);
        CShaderSquare::Draw();   //2Dスプライトのレンダリング
        m_pEffect->EndPass();    

        // 更新した波マップを参照し水面を凸凹にしてレンダリングする
        m_pd3dDevice->SetRenderTarget(0, m_pBumpMapSurface);
        m_pd3dDevice->SetTexture(0, m_pWaveMapTexture[1 - m_RenderTargetIndex]);

        // 2Dテクスチャの描画
        m_pEffect->BeginPass(1);
        CShaderSquare::Draw();   //2Dスプライトのレンダリング
        m_pEffect->EndPass();
        m_pEffect->End();

        // レンダーターゲットを戻す
        m_pd3dDevice->SetRenderTarget(0, OldSurface);
        if (OldSurface)
        {
            OldSurface->Release();
        }

        // 深度バッファを戻す
        m_pd3dDevice->SetDepthStencilSurface(OldDepthStencilSurface);
        if (OldDepthStencilSurface)
        {
            OldDepthStencilSurface->Release();
        }

        // ビューポートを戻す
        m_pd3dDevice->SetViewport(&OldViewport);
    }

    return m_pBumpMapTexture;
}

//=============================================================================
// 頂点データの再生成
//=============================================================================
HRESULT CWave::SetVertexDecl(LPDIRECT3DDEVICE9 pd3dDevice, const D3DVERTEXELEMENT9 *pDecl, LPD3DXMESH &meshWater, const LPD3DXMESH &mesh)
{
    LPD3DXMESH pTempSysMemMesh = nullptr;

    //メッシュ情報をコピーする
    if (mesh)
    {
        if (FAILED(mesh->CloneMesh(mesh->GetOptions(),
            pDecl,
            pd3dDevice, &pTempSysMemMesh)))
            return E_FAIL; 
    }

    //頂点情報を参照し、法線ベクトル、接線ベクトル、従法線ベクトルがあるか調べる
    DWORD Normal = D3DX_DEFAULT;
    DWORD Tangent = D3DX_DEFAULT;
    DWORD Binormal = D3DX_DEFAULT;
    if (pTempSysMemMesh)
    {
        for (UINT index = 0; index < D3DXGetDeclLength(pDecl); ++index)
        {
            if (pDecl[index].Usage == D3DDECLUSAGE_NORMAL)
                Normal = D3DDECLUSAGE_NORMAL;
            else if (pDecl[index].Usage == D3DDECLUSAGE_TANGENT)
                Tangent = D3DDECLUSAGE_TANGENT;
            else if (pDecl[index].Usage == D3DDECLUSAGE_BINORMAL)
                Binormal = D3DDECLUSAGE_BINORMAL;
        }
    }

    if (pTempSysMemMesh)
    {
        //頂点情報に基づき頂点データを再生成する   
        if (Normal != D3DX_DEFAULT || Tangent != D3DX_DEFAULT || Binormal != D3DX_DEFAULT)
        {
            D3DXComputeTangentFrameEx(pTempSysMemMesh,
                D3DDECLUSAGE_TEXCOORD,
                0,
                D3DDECLUSAGE_TANGENT,
                0,
                D3DDECLUSAGE_BINORMAL,
                0,
                D3DDECLUSAGE_NORMAL,
                0,
                0,
                nullptr,
                0.01f,    //ボケ具合.値をおおきくするとぼけなくなる
                0.25f,
                0.01f,
                &meshWater,
                nullptr
            );
        }

        //頂点データを再生成しない
        else
        {
            pTempSysMemMesh->CloneMesh(pTempSysMemMesh->GetOptions(),
                pDecl,
                pd3dDevice,
                &meshWater);

        }
        pTempSysMemMesh->Release();
    }

    return S_OK;

}
