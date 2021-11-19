//=============================================================================
//
// ブラークラス [blur_filter.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "blur_filter.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBlurFilter::CBlurFilter(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters) : CShaderSquare(pd3dDevice, pd3dParameters)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CBlurFilter::CBlurFilter(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height) : CShaderSquare(pd3dDevice, Width, Height)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBlurFilter::~CBlurFilter()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }
}

//=============================================================================
// 終了処理
//=============================================================================
void CBlurFilter::Uninit()
{
    if (m_pEffect)
        m_pEffect->OnLostDevice();
}

//=============================================================================
// デバイス設定
//=============================================================================
void CBlurFilter::Restore()
{
    if (m_pEffect)
    {
        m_pEffect->OnResetDevice();
    }
}

//=============================================================================
// シェーダロード
//=============================================================================
HRESULT CBlurFilter::Load()
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
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/BlurFilter.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pTU = m_pEffect->GetParameterByName(nullptr, "m_TU");
        m_pTV = m_pEffect->GetParameterByName(nullptr, "m_TV");

        //１テクセルの大きさをセット
        float TU = 1.0f / CShaderSquare::GetWidth();
        float TV = 1.0f / CShaderSquare::GetHeight();

        m_pEffect->SetFloat(m_pTU, TU);
        m_pEffect->SetFloat(m_pTV, TV);

        m_pEffect->SetTechnique(m_pTechnique);
    }

    else
    {
        return -3;
    }

    return S_OK;
}

//=============================================================================
// テクセルの設定
//=============================================================================
void CBlurFilter::SetTexel(float TU, float TV)
{
    if (m_pEffect)
    {
        m_pEffect->SetFloat(m_pTU, TU);
        m_pEffect->SetFloat(m_pTV, TV);
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CBlurFilter::Render(UINT Pass)
{
    if (m_pEffect)
    {
        m_pEffect->Begin(nullptr, 0);
        m_pEffect->BeginPass(Pass);

        CShaderSquare::Draw();   //2Dスプライトのレンダリング

        m_pEffect->EndPass();
        m_pEffect->End();
    }
}

//=============================================================================
// nullcheck
//=============================================================================
BOOL CBlurFilter::IsOK()
{
    if (m_pEffect == nullptr)
        return FALSE;

    return TRUE;
}