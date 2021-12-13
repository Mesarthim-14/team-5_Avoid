#include "edge_filter.h"

CEdgeFilter::CEdgeFilter(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters) : CShaderSquare(pd3dDevice, pd3dParameters)
{
    m_pd3dDevice = pd3dDevice;
    m_pd3dParameters = pd3dParameters;
    m_pEffect = NULL;
}

CEdgeFilter::CEdgeFilter(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height) : CShaderSquare(pd3dDevice, Width, Height)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = NULL;
}

CEdgeFilter::~CEdgeFilter()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }
}

void CEdgeFilter::Invalidate()
{
    if (m_pEffect)
        m_pEffect->OnLostDevice();
}

void CEdgeFilter::Restore()
{
    if (m_pEffect)
        m_pEffect->OnResetDevice();
}

HRESULT CEdgeFilter::Load()
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
        LPD3DXBUFFER pErr = NULL;
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/ToonShader.fx", NULL, NULL, 0, NULL, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pTexel = m_pEffect->GetParameterByName(NULL, "m_Texel");
        m_pLimit = m_pEffect->GetParameterByName(NULL, "m_Limit");

        m_pEffect->SetTechnique(m_pTechnique);
    }

    else
    {
        return -3;
    }

    return S_OK;
}

void CEdgeFilter::SetParameters(D3DXVECTOR2* pTexel, float pLimit)
{
    if (m_pEffect)
    {
        m_pEffect->SetValue(m_pTexel, (LPVOID)pTexel, sizeof(float) * 2);
        m_pEffect->SetFloat(m_pLimit, pLimit);
    }
}

void CEdgeFilter::Render(LPDIRECT3DTEXTURE9 pBackBuffer, LPDIRECT3DTEXTURE9 pZBuffer)
{
    if (m_pEffect)
    {
        m_pd3dDevice->SetTexture(0, pBackBuffer);
        m_pd3dDevice->SetTexture(1, pZBuffer);

        m_pEffect->Begin(NULL, 0);
        m_pEffect->BeginPass(1);
        CShaderSquare::Draw();
        m_pEffect->EndPass();
        m_pEffect->End();

        m_pd3dDevice->SetTexture(0, NULL);
        m_pd3dDevice->SetTexture(1, NULL);
    }
}

BOOL CEdgeFilter::IsOK()
{
    if (m_pEffect)
        return TRUE;

    return FALSE;
}