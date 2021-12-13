//=============================================================================
//
// 線画調シェーダクラス [canvas.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "canvas.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCanvas::CCanvas(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters) : CShaderSquare(pd3dDevice, pd3dParameters)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
}

CCanvas::CCanvas(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height) : CShaderSquare(pd3dDevice, Width, Height)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCanvas::~CCanvas()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }
}

void CCanvas::Invalidate()
{
    if (m_pEffect)
        m_pEffect->OnLostDevice();
}

void CCanvas::Restore()
{
    if (m_pEffect)
        m_pEffect->OnResetDevice();
}

HRESULT CCanvas::Load()
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
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/Canvas.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pEffect->SetTechnique(m_pTechnique);
    }

    else
    {
        return -3;
    }

    return S_OK;
}

//=============================================================================
// 描画処理
//=============================================================================
void CCanvas::Render(LPDIRECT3DTEXTURE9 pBackBuffer, LPDIRECT3DTEXTURE9 pMaterial, LPDIRECT3DTEXTURE9 pCanvas, bool isTex)
{
    if (m_pEffect)
    {
        m_pd3dDevice->SetTexture(0, pBackBuffer);
        m_pd3dDevice->SetTexture(1, pMaterial);
        m_pd3dDevice->SetTexture(2, pCanvas);

        m_pEffect->Begin(nullptr, 0);
        m_pEffect->BeginPass(0);
        CShaderSquare::Draw();
        m_pEffect->EndPass();
        m_pEffect->End();

        m_pd3dDevice->SetTexture(0, nullptr);
        m_pd3dDevice->SetTexture(1, nullptr);
        m_pd3dDevice->SetTexture(2, nullptr);
    }
}

BOOL CCanvas::IsOK()
{
    if (m_pEffect)
        return TRUE;

    return FALSE;
}