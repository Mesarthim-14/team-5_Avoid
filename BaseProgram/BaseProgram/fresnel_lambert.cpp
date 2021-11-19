//=============================================================================
//
// 反射光クラス [fresnel_lambert.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "fresnel_lambert.h"
#include "main.h"
#include "resource_manager.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CFrenelLambert::CFrenelLambert(LPDIRECT3DDEVICE9 pd3dDevice)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFrenelLambert::~CFrenelLambert()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }
}

//=============================================================================
// デバイス解放
//=============================================================================
void CFrenelLambert::Invalidate()
{
    if (m_pEffect)
        m_pEffect->OnLostDevice();
}

//=============================================================================
// デバイス設定
//=============================================================================
void CFrenelLambert::Restore()
{
    if (m_pEffect)
        m_pEffect->OnResetDevice();
}

//=============================================================================
// シェーダロード
//=============================================================================
HRESULT CFrenelLambert::Load()
{
    D3DCAPS9 caps;

    m_pd3dDevice->GetDeviceCaps(&caps);
    if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
    {
        LPD3DXBUFFER pErr = NULL;
        HRESULT hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/Lambert18.fx", NULL, NULL, 0, NULL, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pWVPP = m_pEffect->GetParameterByName(NULL, "m_WVPP");
        m_pLightDir = m_pEffect->GetParameterByName(NULL, "m_LightDir");
        m_pAmbient = m_pEffect->GetParameterByName(NULL, "m_Ambient");
        m_pZEnable = m_pEffect->GetParameterByName(NULL, "m_ZEnable");
        m_pZF = m_pEffect->GetParameterByName(NULL, "m_ZF");

        m_pEffect->SetTechnique(m_pTechnique);
    }

    else
    {
        return -3;
    }

    return S_OK;
}

//=============================================================================
// Z値の有効設定
//=============================================================================
void CFrenelLambert::SetZEnable(bool ZEnable)
{
    if (m_pEffect)
    {
        m_pEffect->SetBool(m_pZEnable, ZEnable);
    }
}

//=============================================================================
// 色の設定
//=============================================================================
void CFrenelLambert::SetAmbient(float Ambient)
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

//=============================================================================
// 色の設定
//=============================================================================
void CFrenelLambert::SetAmbient(D3DXVECTOR4* pAmbient)
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

//=============================================================================
// ローカル座標系
//=============================================================================
void CFrenelLambert::SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir, float pZF)
{
    if (m_pEffect)
    {
        D3DXMATRIX m;
        D3DXVECTOR4 v;

        m = (*pMatWorld) * m_matView * m_matProj;
        m_pEffect->SetMatrix(m_pWVPP, &m);

        //Light
        D3DXMatrixInverse(&m, nullptr, pMatWorld);
        D3DXVec4Transform(&v, pLightDir, &m);
        D3DXVec4Normalize(&v, &v);
        m_pEffect->SetVector(m_pLightDir, &v);

        //遠近射影行列の最遠近距離
        m_pEffect->SetFloat(m_pZF, pZF);
    }

    else
        m_pd3dDevice->SetTransform(D3DTS_WORLD, pMatWorld);
}

//=============================================================================
// シェーダ開始
//=============================================================================
void CFrenelLambert::Begin()
{
    if (m_pEffect)
    {
        m_pd3dDevice->GetTransform(D3DTS_VIEW, &m_matView);
        m_pd3dDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

        m_pEffect->Begin(NULL, 0);
    }
}

//=============================================================================
// パスの開始
//=============================================================================
void CFrenelLambert::BeginPass(UINT Pass)
{
    if (m_pEffect)
    {
        m_pEffect->BeginPass(Pass);
    }
}

//=============================================================================
// エフェクトの更新
//=============================================================================
void CFrenelLambert::CommitChanges()
{
    if (m_pEffect)
        m_pEffect->CommitChanges();
}

//=============================================================================
// パスの処理
//=============================================================================
void CFrenelLambert::EndPass()
{
    if (m_pEffect)
    {
        m_pEffect->EndPass();
    }
}

//=============================================================================
// シェーダ終了
//=============================================================================
void CFrenelLambert::End()
{
    if (m_pEffect)
    {
        m_pEffect->End();
    }
}

//=============================================================================
// シェーダロードの確認
//=============================================================================
BOOL CFrenelLambert::IsOK()
{
    if (m_pEffect)
        return TRUE;

    return FALSE;
}