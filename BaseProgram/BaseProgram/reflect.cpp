//=============================================================================
//
// 反射クラス [reflect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "reflect.h"
#include "main.h"
#include "resource_manager.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CReflect::CReflect(LPDIRECT3DDEVICE9 pd3dDevice)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
}

CReflect::~CReflect()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }
}

void CReflect::Invalidate()
{
    if (m_pEffect)
        m_pEffect->OnLostDevice();
}

void CReflect::Restore()
{
    if (m_pEffect)
        m_pEffect->OnResetDevice();
}

HRESULT CReflect::Load()
{
    D3DCAPS9 caps;
    HRESULT hr;

    m_pd3dDevice->GetDeviceCaps(&caps);
    if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
    {
        //シェーダーの初期化
        LPD3DXBUFFER pErr = NULL;
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/Reflect.fx", NULL, NULL, 0, NULL, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_pW = m_pEffect->GetParameterByName(NULL, "m_W");
        m_pWVPP = m_pEffect->GetParameterByName(NULL, "m_WVPP");
        m_pLightDir = m_pEffect->GetParameterByName(NULL, "m_LightDir");
        m_pAmbient = m_pEffect->GetParameterByName(NULL, "m_Ambient");
        m_pHeight = m_pEffect->GetParameterByName(NULL, "m_Height");

        m_pEffect->SetTechnique(m_pTechnique);
    }

    else
    {
        return -3;
    }

    return S_OK;
}

void CReflect::Begin()
{
    if (m_pEffect)
    {
        m_pd3dDevice->GetTransform(D3DTS_VIEW, &m_matView);
        m_pd3dDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

        m_pEffect->Begin(NULL, 0);
    }
}

void CReflect::BeginPass(const int& nNum)
{
    if (m_pEffect)
        m_pEffect->BeginPass(nNum);
}

//水面の高さを設定
void CReflect::SetHeight(float Height)
{
    if (m_pEffect)
        m_pEffect->SetFloat(m_pHeight, Height);
}

void CReflect::SetAmbient(float Ambient)
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

void CReflect::SetAmbient(D3DXVECTOR4* pAmbient)
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

void CReflect::SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir)
{
    if (m_pEffect)
    {
        D3DXMATRIX m;
        D3DXVECTOR4 v;

        m_pEffect->SetMatrix(m_pW, pMatWorld);

        m = (*pMatWorld) * m_matView * m_matProj;
        m_pEffect->SetMatrix(m_pWVPP, &m);

        //Light
        D3DXMatrixInverse(&m, NULL, pMatWorld);
        D3DXVec4Transform(&v, pLightDir, &m);
        D3DXVec4Normalize(&v, &v);
        m_pEffect->SetVector(m_pLightDir, &v);
    }

    else
        m_pd3dDevice->SetTransform(D3DTS_WORLD, pMatWorld);
}

void CReflect::EndPass()
{
    if (m_pEffect)
    {
        m_pEffect->EndPass();
    }
}

void CReflect::End()
{
    if (m_pEffect)
    {
        m_pEffect->End();
    }
}

void CReflect::CommitChanges()
{
    if (m_pEffect)
        m_pEffect->CommitChanges();
}

BOOL CReflect::IsOK()
{
    if (m_pEffect)
        return TRUE;

    return FALSE;
}

//===================================================================================================================
// 頂点ブレンド用の情報を送る関数
//===================================================================================================================
void CReflect::SetVertexBlendInfo(D3DXMATRIX *pMtxWorld[4], D3DXMATRIX pMtxView, D3DXMATRIX pMtxProj, int nNum)
{
    if (m_pEffect)
    {
        m_pEffect->SetMatrixPointerArray("matWorld", (const D3DXMATRIX**)pMtxWorld, 4);
        m_pEffect->SetMatrix("matView", &pMtxView);
        m_pEffect->SetMatrix("matProj", &pMtxProj);
        m_pEffect->SetInt("iBlendNum", (INT)nNum);
    }
}
