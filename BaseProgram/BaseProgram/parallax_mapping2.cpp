//=============================================================================
//
// 視差マッピングクラス [ParallaxMapping.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "parallax_mapping2.h"

CParallaxMapping2::CParallaxMapping2(LPDIRECT3DDEVICE9 pd3dDevice)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = NULL;
}

CParallaxMapping2::~CParallaxMapping2()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }
}

void CParallaxMapping2::Invalidate()
{
    if (m_pEffect)
        m_pEffect->OnLostDevice();
}

void CParallaxMapping2::Restore()
{
    if (m_pEffect)
        m_pEffect->OnResetDevice();
}

HRESULT CParallaxMapping2::Load()
{
    D3DCAPS9 caps;
    HRESULT hr;

    m_pd3dDevice->GetDeviceCaps(&caps);
    if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
    {
        //シェーダーの初期化
        LPD3DXBUFFER pErr = NULL;
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/ParallaxMapping2.fx", NULL, NULL, 0, NULL, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pWVPP = m_pEffect->GetParameterByName(NULL, "m_WVPP");
        m_pWVPPT = m_pEffect->GetParameterByName(NULL, "m_WVPPT");
        m_pLightDir = m_pEffect->GetParameterByName(NULL, "m_LightDir");
        m_pEyePos = m_pEffect->GetParameterByName(NULL, "m_EyePos");
        m_pAmbient = m_pEffect->GetParameterByName(NULL, "m_Ambient");
        m_pSpecularPower = m_pEffect->GetParameterByName(NULL, "m_SpecularPower");
        m_pSpecular = m_pEffect->GetParameterByName(NULL, "m_Specular");
        m_pHeight = m_pEffect->GetParameterByName(NULL, "m_Height");
        m_pRefraction = m_pEffect->GetParameterByName(NULL, "m_Refraction");
        m_pZF = m_pEffect->GetParameterByName(NULL, "m_ZF");

        m_pEffect->SetTechnique(m_pTechnique);
    }

    else
    {
        return -3;
    }

    return S_OK;
}

void CParallaxMapping2::Begin()
{
    if (m_pEffect)
    {
        m_pd3dDevice->GetTransform(D3DTS_VIEW, &m_matView);
        m_pd3dDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

        m_pEffect->Begin(NULL, 0);
    }
}

void CParallaxMapping2::BeginPass(UINT Pass)
{
    if (m_pEffect)
        m_pEffect->BeginPass(Pass);
}

void CParallaxMapping2::SetAmbient(float Ambient)
{
    if (m_pEffect)
    {
        D3DXVECTOR4 A;
        A = D3DXVECTOR4(Ambient, Ambient, Ambient, 1.0f);
        m_pEffect->SetVector(m_pAmbient, &A);
    }

    else
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

void CParallaxMapping2::SetAmbient(D3DXVECTOR4* pAmbient)
{
    if (m_pEffect)
        m_pEffect->SetVector(m_pAmbient, pAmbient);

    else
    {
        D3DMATERIAL9 old_material;
        m_pd3dDevice->GetMaterial(&old_material);
        old_material.Ambient.r = pAmbient->x;
        old_material.Ambient.g = pAmbient->y;
        old_material.Ambient.b = pAmbient->z;
        old_material.Ambient.a = pAmbient->w;
        m_pd3dDevice->SetMaterial(&old_material);
    }
}

void CParallaxMapping2::SetSpecular(float Specular)
{
    if (m_pEffect)
        m_pEffect->SetFloat(m_pSpecular, Specular);
}

void CParallaxMapping2::SetSpecularPower(float SpecularPower)
{
    if (m_pEffect)
        m_pEffect->SetFloat(m_pSpecularPower, SpecularPower);
}

//高さに対する係数
void CParallaxMapping2::SetHeight(float Height)
{
    if (m_pEffect)
        m_pEffect->SetFloat(m_pHeight, Height);
}

//屈折率
void CParallaxMapping2::SetRefraction(float Refraction)
{
    if (m_pEffect)
        m_pEffect->SetFloat(m_pRefraction, Refraction);
}

void CParallaxMapping2::SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pCameraPos, D3DXVECTOR4* pLightDir, float pZF)
{
    if (m_pEffect)
    {
        D3DXMATRIX m, m1, m2;
        D3DXVECTOR4 v;

        m = (*pMatWorld) * m_matView * m_matProj;
        m_pEffect->SetMatrix(m_pWVPP, &m);

        //行列変換マトリックスをテクスチャー座標系へ変換
        D3DXMatrixScaling(&m1, 0.5f, -0.5f, 1.0f);
        D3DXMatrixTranslation(&m2, 0.5f, 0.5f, 0.0f);
        m = m * m1 * m2;
        m_pEffect->SetMatrix(m_pWVPPT, &m);

        //カメラ位置
        m1 = (*pMatWorld) * m_matView;
        D3DXMatrixInverse(&m1, NULL, &m1);
        D3DXVec4Transform(&v, pCameraPos, &m1);
        m_pEffect->SetVector(m_pEyePos, &v);

        //Light
        D3DXMatrixInverse(&m, NULL, pMatWorld);
        D3DXVec4Transform(&v, pLightDir, &m);
        D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
        m_pEffect->SetVector(m_pLightDir, &v);

        //遠近射影行列の最遠近距離をセット
        m_pEffect->SetFloat(m_pZF, pZF);
    }

    else
        m_pd3dDevice->SetTransform(D3DTS_WORLD, pMatWorld);
}

void CParallaxMapping2::EndPass()
{
    if (m_pEffect)
    {
        m_pEffect->EndPass();
    }
}

void CParallaxMapping2::End()
{
    if (m_pEffect)
    {
        m_pEffect->End();
    }
}

void CParallaxMapping2::CommitChanges()
{
    if (m_pEffect)
        m_pEffect->CommitChanges();
}

BOOL CParallaxMapping2::IsOK()
{
    if (m_pEffect)
        return TRUE;

    return FALSE;
}