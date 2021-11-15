//=============================================================================
//
// マスククラス [mask.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "mask.h"
#include "main.h"
#include "resource_manager.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMask::CMask(LPDIRECT3DDEVICE9 pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;
	m_pEffect = NULL;
}

CMask::~CMask()
{
	if (m_pEffect)
	{
		m_pEffect->Release();
		m_pEffect = nullptr;
	}
}

void CMask::Invalidate()
{
	if (m_pEffect)
		m_pEffect->OnLostDevice();
}

void CMask::Restore()
{
	if (m_pEffect)
		m_pEffect->OnResetDevice();
}

HRESULT CMask::Load()
{
	D3DCAPS9 caps;

	m_pd3dDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(1, 1))
	{
		LPD3DXBUFFER pErr = NULL;
		HRESULT hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/Mask.fx", NULL, NULL, 0, NULL, &m_pEffect, &pErr);
		if (FAILED(hr))
			return -2;

		m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
		m_pWVP = m_pEffect->GetParameterByName(NULL, "m_WVP");

		m_pEffect->SetTechnique(m_pTechnique);
	}

	else
	{
		return -3;
	}

	return S_OK;
}

//ローカル座標系
void CMask::SetMatrix(D3DXMATRIX* pMatWorld)
{
	if (m_pEffect)
	{
		D3DXMATRIX m;

		m = (*pMatWorld) * m_matView * m_matProj;
		m_pEffect->SetMatrix(m_pWVP, &m);
	}
}

void CMask::Begin()
{
	if (m_pEffect)
	{
		m_pd3dDevice->GetTransform(D3DTS_VIEW, &m_matView);
		m_pd3dDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

		m_pEffect->Begin(NULL, 0);
	}
}

void CMask::BeginPass(UINT Pass)
{
	if (m_pEffect)
	{
		m_pEffect->BeginPass(Pass);
	}
}

void CMask::CommitChanges()
{
	if (m_pEffect)
		m_pEffect->CommitChanges();
}

void CMask::EndPass()
{
	if (m_pEffect)
	{
		m_pEffect->EndPass();
	}
}

void CMask::End()
{
	if (m_pEffect)
	{
		m_pEffect->End();
	}
}

BOOL CMask::IsOK()
{
	if (m_pEffect)
		return TRUE;

	return FALSE;
}