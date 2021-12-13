//=============================================================================
//
// トゥーンエフェクトクラス [toon_shader.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "toon_shader.h"
#include "edge_filter.h"
#include "manager.h"
#include "camera.h"
#include "light.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"
#include "texture.h"
#include "canvas.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CToonShader::CToonShader(LPDIRECT3DDEVICE9 pd3dDevice)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;

    m_pToonMap = nullptr;
    m_pEdgeFilter = nullptr;
    m_pColorTexture = nullptr;
    m_pColorSurface = nullptr;
    m_pZMapTexture = nullptr;
    m_pZMapSurface = nullptr;
    m_pDiffuseTexture = nullptr;
    m_pDiffuseSurface = nullptr;
    m_fLimit = 0.4f;
    m_OldSurface = nullptr;
    m_pCanvas = nullptr;
    m_pCanvasTexture = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CToonShader::~CToonShader()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }
}

void CToonShader::Invalidate()
{
    if (m_pEffect)
        m_pEffect->OnLostDevice();
}

void CToonShader::Restore()
{
    if (m_pEffect)
        m_pEffect->OnResetDevice();
}

//=============================================================================
// 初期化処理
//=============================================================================
void CToonShader::Init()
{
    Load();
    TextureLoad();
    if (!m_pEdgeFilter)
    {
        //エッジフィルタークラスの初期化
        m_pEdgeFilter = new CEdgeFilter(m_pd3dDevice, (UINT)SCREEN_WIDTH, (UINT)SCREEN_HEIGHT);
        m_pEdgeFilter->Load();
    }
}

//=============================================================================
// 終了処理
//=============================================================================
void CToonShader::Uninit()
{
    if (m_pToonMap)
    {
        m_pToonMap->Release();
        m_pToonMap = nullptr;
    }
    if (m_pEdgeFilter)
    {
        m_pEdgeFilter->Invalidate();
        delete m_pEdgeFilter;
        m_pEdgeFilter = nullptr;
    }

    if (m_pColorTexture)
    {
        m_pColorTexture->Release();
        m_pColorTexture = nullptr;
    }
    if (m_pColorSurface)
    {
        m_pColorSurface->Release();
        m_pColorSurface = nullptr;
    }
    if (m_pZMapTexture)
    {
        m_pZMapTexture->Release();
        m_pZMapTexture = nullptr;
    }
    if (m_pZMapSurface)
    {
        m_pZMapSurface->Release();
        m_pZMapSurface = nullptr;
    }
    if (m_pDiffuseTexture)
    {
        m_pDiffuseTexture->Release();
        m_pDiffuseTexture = nullptr;
    }
    if (m_pDiffuseSurface)
    {
        m_pDiffuseSurface->Release();
        m_pDiffuseSurface = nullptr;
    }
    if (m_OldSurface)
    {
        m_OldSurface->Release();
        m_OldSurface = nullptr;
    }
    if (m_pCanvas)
    {
        m_pCanvas->Uninit();
        delete m_pCanvas;
        m_pCanvas = nullptr;
    }
    if (m_pCanvasTexture)
    {
        m_pCanvasTexture->Release();
        m_pCanvasTexture = nullptr;
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CToonShader::Draw()
{

}

//=============================================================================
// サーフェス切り替え
//=============================================================================
void CToonShader::BeginSurface()
{
    //================================================================================================-
    // トゥーンシェーダ&アウトラインシェーダ
    //================================================================================================-
    //バックバッファを退避
    m_pd3dDevice->GetRenderTarget(0, &m_OldSurface);

    //マルチレンダーターゲットに切り替え
    m_pd3dDevice->SetRenderTarget(0, m_pColorSurface);
    m_pd3dDevice->SetRenderTarget(1, m_pZMapSurface);
    m_pd3dDevice->SetRenderTarget(2, m_pDiffuseSurface);

    m_pd3dDevice->Clear(0L,
        NULL,
        D3DCLEAR_TARGET,
        D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),
        1.0f,
        0L);

    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

    m_pd3dDevice->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(2, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
}

//=============================================================================
// エッジの描画
//=============================================================================
void CToonShader::DrawEdgeFilter()
{
    EndSurface();

    //****************************************************************
    //STEP2:取得したＺ値を元にエッジフィルターを適応する
    //****************************************************************
    //１ピクセルの大きさを取得する
    m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    //１ピクセルの大きさを取得する
    D3DXVECTOR2 Texel = D3DXVECTOR2(1.0f / SCREEN_WIDTH, 1.0f / SCREEN_HEIGHT);
    m_pEdgeFilter->SetParameters(&Texel, m_fLimit);

    //エッジフィルターを適応する。
    m_pEdgeFilter->Render(m_pColorTexture, m_pZMapTexture);

    m_pd3dDevice->SetTexture(0, nullptr);
    m_pd3dDevice->SetTexture(1, nullptr);
    m_pd3dDevice->SetTexture(2, nullptr);
    m_pd3dDevice->SetTexture(3, nullptr);

    //****************************************************************
    // STEP2 : 線画を適応する
    //****************************************************************
    // シーンの色情報
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
    // 拡散反射率マップ
    m_pd3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
    m_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
    m_pd3dDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
    // キャンバステクスチャー
    m_pd3dDevice->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(2, D3DSAMP_MIPFILTER, D3DTEXF_NONE);


    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    //線画を適応する
    m_pCanvas->Render(m_pColorTexture, m_pDiffuseTexture, m_pCanvasTexture, true);

    m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

//=============================================================================
// サーフェスの終了
//=============================================================================
void CToonShader::EndSurface()
{
    //レンダーターゲットをバックバッファに戻す
    m_pd3dDevice->SetRenderTarget(0, m_OldSurface);
    m_pd3dDevice->SetRenderTarget(1, nullptr);
    m_pd3dDevice->SetRenderTarget(2, nullptr);

    if (m_OldSurface)
    {
        m_OldSurface->Release();
        m_OldSurface = nullptr;
    }
}

//=============================================================================
// エフェクト開始
//=============================================================================
void CToonShader::Begin()
{        
    if (m_pEffect)
    {
        // シェーダ開始
        m_pEffect->Begin(NULL, 0);
    }
}

//=============================================================================
// 通常シェーダ
//=============================================================================
void CToonShader::Begin(int nNum, D3DXMATRIX& mtxWorld, CXfile::MODEL model)
{
    if (m_pEffect)
    {
        D3DXVECTOR3 CameraPos = CManager::GetInstance()->GetCamera()->GetposV();
        D3DXVECTOR4 EyePos = D3DXVECTOR4(CameraPos, 1.0f);      // カメラの座標
        D3DXVECTOR4 LightDir = D3DXVECTOR4(CManager::GetInstance()->GetLight()->GetLightDir(), 0.0f);
        CTexture *pTexture = GET_TEXTURE_PTR;
        m_pd3dDevice->GetTransform(D3DTS_VIEW, &m_matView);
        m_pd3dDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

        // トゥーンマップテクスチャーをステージ１にセットする
        m_pd3dDevice->SetTexture(1, m_pToonMap);

        // シェーダ開始
        m_pEffect->Begin(NULL, 0);
        SetAmbient(&D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
        SetMatrix(&mtxWorld, &LightDir, &EyePos);
        for (int nCntMat = 0; nCntMat < (int)model.dwNumMat; nCntMat++)
        {
            // テクスチャの設定
            if (model.apTexture[nCntMat])
            {
                m_pd3dDevice->SetTexture(0, model.apTexture[nCntMat]);
                BeginPass(CToonShader::TOON_PASS_MODEL);

            }
            else
            {
                D3DXMATERIAL* pMat = (D3DXMATERIAL*)model.pBuffMat->GetBufferPointer();
                D3DXVECTOR4 Diffuse = ZeroVector4;
                Diffuse.x = pMat[nCntMat].MatD3D.Diffuse.r;
                Diffuse.y = pMat[nCntMat].MatD3D.Diffuse.g;
                Diffuse.z = pMat[nCntMat].MatD3D.Diffuse.b;
                Diffuse.w = pMat[nCntMat].MatD3D.Diffuse.a;

                m_pd3dDevice->SetTexture(0, nullptr);
                SetDiffuse(Diffuse);
                BeginPass(CToonShader::TOON_PASS_MODEL_DIFFUSE);
            }

            //モデルパーツの描画
            model.pMesh->DrawSubset(nCntMat);
            EndPass();
        }
        End();

        //     DrawEdgeFilter();
    }
}

//=============================================================================
// シェーダ開始
//=============================================================================
void CToonShader::Begin(int nNum, D3DXMATRIX& mtxWorld, D3DXVECTOR4* LightDir)
{
 //   if (m_pEffect)
    {
        D3DXVECTOR3 CameraPos = CManager::GetInstance()->GetCamera()->GetposV();
        D3DXVECTOR4 EyePos = D3DXVECTOR4(CameraPos, 1.0f);      // カメラの座標

        // マトリクス、ライト方向、カメラ座標設定
        SetMatrix(&mtxWorld, LightDir, &EyePos);
        //トゥーンマップテクスチャーをステージ１にセットする
        m_pd3dDevice->SetTexture(1, m_pToonMap);

        BeginPass(nNum);

    }
}

void CToonShader::BeginPass(int nNum)
{
    if (m_pEffect)
    {
        m_pEffect->BeginPass(nNum);
    }
}

//=============================================================================
// シェーダロード
//=============================================================================
HRESULT CToonShader::Load()
{
    D3DCAPS9 caps;

    m_pd3dDevice->GetDeviceCaps(&caps);
    if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
    {
        LPD3DXBUFFER pErr = NULL;
        HRESULT hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/ToonShader.fx", NULL, NULL, 0, NULL, &m_pEffect, &pErr);
        if (SUCCEEDED(hr))
        {
            m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
            m_pWVP = m_pEffect->GetParameterByName(NULL, "m_WVP");
            m_pLightDir = m_pEffect->GetParameterByName(NULL, "m_LightDir");
            m_pTexel = m_pEffect->GetParameterByName(NULL, "m_Texel");
            m_pLimit = m_pEffect->GetParameterByName(NULL, "m_Limit");
            m_pEyePos = m_pEffect->GetParameterByName(NULL, "m_EyePos");
            m_Diffuse = m_pEffect->GetParameterByName(NULL, "m_Diffuse");

            m_pEffect->SetTechnique(m_pTechnique);
        }
        else
        {
            return -1;
        }
    }

    else
    {
        return -2;
    }

    return S_OK;
}

//=============================================================================
// テクスチャロード
//=============================================================================
void CToonShader::TextureLoad()
{
    D3DXCreateTextureFromFileEx(m_pd3dDevice,
        "data/Texture/ToonMap.bmp",		//トゥーンマップテクスチャーファイル名
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        1,
        0,
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0x0,
        NULL,
        NULL,
        &m_pToonMap);

    //カラー情報を格納するマルチレンダーターゲットで使用するテクスチャーを作成する
    D3DXCreateTexture(m_pd3dDevice, SCREEN_WIDTH, SCREEN_HEIGHT,
        1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
        &m_pColorTexture);
    //カラー情報を格納するマルチレンダーターゲットサーフェイスを作成する
    m_pColorTexture->GetSurfaceLevel(0, &m_pColorSurface);

    //Z値情報を格納するマルチレンダーターゲットで使用するテクスチャーを作成する
    D3DXCreateTexture(m_pd3dDevice, SCREEN_WIDTH, SCREEN_HEIGHT,
        1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT,
        &m_pZMapTexture);
    D3DXCreateTexture(m_pd3dDevice, SCREEN_WIDTH, SCREEN_HEIGHT,
        1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
        &m_pZMapTexture);

    //Z値情報を格納するマルチレンダーターゲットサーフェイスを作成する
    m_pZMapTexture->GetSurfaceLevel(0, &m_pZMapSurface);

    //キャンバスシェーダーの初期化
    m_pCanvas = new CCanvas(m_pd3dDevice, SCREEN_WIDTH, SCREEN_HEIGHT);
    m_pCanvas->Load();

    //線画テクスチャーの初期化
    D3DXCreateTextureFromFileEx(m_pd3dDevice,
        "data/Texture/Canvas.bmp",			//ファイル名
        D3DX_DEFAULT,						//幅
        D3DX_DEFAULT,						//高さ
        1,									//ミップマップレベル
        0,									//テクスチャーの使用目的
        D3DFMT_UNKNOWN,						//フォーマット
        D3DPOOL_MANAGED,					//メモリ管理方法
        D3DX_DEFAULT,						//フィルタリング方法
        D3DX_DEFAULT,						//フィルタリング方法
        0x0,								//カラーキー
        NULL,								//ファイルの情報を格納する構造体
        NULL,								//256色パレットを示す構造体
        &m_pCanvasTexture);					//IDirect3DTexture9 インターフェイス
    m_pCanvas->Restore();
    D3DXCreateTexture(m_pd3dDevice,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_R32F,
        D3DPOOL_DEFAULT,
        &m_pDiffuseTexture);
    m_pDiffuseTexture->GetSurfaceLevel(0, &m_pDiffuseSurface);
}

//シェーダー内では環境光は使用しないが、シェーダーが使用できない環境では
//固定機能パイプラインライティングを使用するので設定しておく
void CToonShader::SetAmbient(float Ambient)
{
    if (m_pEffect)
    {
        D3DMATERIAL9 old_material;
        m_pd3dDevice->GetMaterial(&old_material);
        old_material.Ambient.r = Ambient;
        old_material.Ambient.g = Ambient;
        old_material.Ambient.b = Ambient;
        old_material.Ambient.a = 1.0f;
        m_pd3dDevice->SetMaterial(&old_material);
    }
}

//シェーダー内では環境光は使用しないが、シェーダーが使用できない環境では
//固定機能パイプラインライティングを使用するので設定しておく
void CToonShader::SetAmbient(D3DXVECTOR4* pAmbient)
{
    if (m_pEffect)
    {
        m_pEffect->SetVector(m_Diffuse, pAmbient);
    }
}

//ローカル座標系
void CToonShader::SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir, D3DXVECTOR4* pCameraPos)
{
    if (m_pEffect)
    {
        D3DXMATRIX m, m1;
        D3DXVECTOR4 LightDir;
        D3DXVECTOR4 v;

        m = (*pMatWorld) * m_matView * m_matProj;
        m_pEffect->SetMatrix(m_pWVP, &m);

        //カメラ位置
        //	m1 = (*pMatWorld) * m_matView;
        //	D3DXMatrixInverse(&m1, NULL, &m1);
        //	D3DXVec4Transform(&v, pCameraPos, &m1);
        //	m_pEffect->SetVector(m_pEyePos, pCameraPos);

        //Light
        LightDir = *pLightDir;
        D3DXMatrixInverse(&m1, NULL, pMatWorld);
        D3DXVec4Transform(&v, &LightDir, &m1);
        D3DXVec4Normalize(&v, &v);
        m_pEffect->SetVector(m_pLightDir, &v);
    }

    else
        m_pd3dDevice->SetTransform(D3DTS_WORLD, pMatWorld);
}

void CToonShader::CommitChanges()
{
    if (m_pEffect)
        m_pEffect->CommitChanges();
}

void CToonShader::EndPass()
{
    if (m_pEffect)
    {
        m_pEffect->EndPass();
    }
}

void CToonShader::End()
{
    if (m_pEffect)
    {
        m_pEffect->End();
    }
}

void CToonShader::Render(LPDIRECT3DTEXTURE9 pBackBuffer, LPDIRECT3DTEXTURE9 pZBuffer)
{
    if (m_pEffect)
    {
        m_pd3dDevice->SetTexture(0, pBackBuffer);
        m_pd3dDevice->SetTexture(1, pZBuffer);

        //	m_pEffect->Begin(NULL, 0);
        //	m_pEffect->BeginPass(0);
        //	CD3d2dsquare::Draw();
        //	m_pEffect->EndPass();
        //	m_pEffect->End();

        //	m_pd3dDevice->SetTexture(0, NULL);
        //	m_pd3dDevice->SetTexture(1, NULL);
    }
}

void CToonShader::SetParameters(D3DXVECTOR2* pTexel, float pLimit)
{
    if (m_pEffect)
    {
        m_pEffect->SetValue(m_pTexel, (LPVOID)pTexel, sizeof(float) * 2);
        m_pEffect->SetFloat(m_pLimit, pLimit);
    }
}

//===================================================================================================================
// 色の設定
//===================================================================================================================
void CToonShader::SetDiffuse(D3DXVECTOR4 Diffuse)
{
    if (m_pEffect)
    {
        m_pEffect->SetVector(m_Diffuse, &Diffuse);
//        m_pEffect->SetVectorArray("m_Diffuse", &Diffuse, sizeof(&Diffuse));
    }
}

//===================================================================================================================
// 頂点ブレンド用の情報を送る関数
//===================================================================================================================
void CToonShader::SetVertexBlendInfo(D3DXMATRIX *pMtxWorld[4], D3DXMATRIX pMtxView, D3DXMATRIX pMtxProj, int nNum)
{
    if (m_pEffect)
    {
        m_pEffect->SetMatrixPointerArray("matWorld", (const D3DXMATRIX**)pMtxWorld, 4);
        m_pEffect->SetMatrix("matView", &pMtxView);
        m_pEffect->SetMatrix("matProj", &pMtxProj);
        m_pEffect->SetInt("iBlendNum", (INT)nNum);
    }
}
