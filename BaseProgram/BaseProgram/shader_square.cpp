//=============================================================================
//
// �V�F�[�_�p�|���S���N���X [shader_square.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "shader_square.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShaderSquare::CShaderSquare(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters)
{
	m_pd3dDevice = pd3dDevice;

	//�o�b�N�o�b�t�@�̃T�C�Y�Ŋi�[����
	m_Width = pd3dParameters->BackBufferWidth;
	m_Height = pd3dParameters->BackBufferHeight;

	D3D2DFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

	m_pd3d2DVertex = nullptr;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShaderSquare::CShaderSquare(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height)
{
	m_pd3dDevice = pd3dDevice;

	m_Width = Width;
	m_Height = Height;

	D3D2DFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

	m_pd3d2DVertex = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShaderSquare::~CShaderSquare()
{
	Uninit();
}

//=============================================================================
// �I������
//=============================================================================
void CShaderSquare::Uninit()
{
	if (m_pd3d2DVertex)
	{
		m_pd3d2DVertex->Release();
		m_pd3d2DVertex = nullptr;
	}
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CShaderSquare::Load()
{
	HRESULT hr = -1;

	Uninit();

	//�Q�c�|���S���̍쐬
	hr = m_pd3dDevice->CreateVertexBuffer(sizeof(D3D2DVERTEX) * 4, D3DUSAGE_WRITEONLY, D3D2DFVF, D3DPOOL_MANAGED, &m_pd3d2DVertex, nullptr);
	if (FAILED(hr))
		return -1;

	//�|���S���̒��_�̍��W���X�V����
	hr = Resize(m_Width, m_Height);

	return hr;
}

//=============================================================================
// �T�C�Y�ݒ肵����
//=============================================================================
HRESULT CShaderSquare::Resize(D3DPRESENT_PARAMETERS* pd3dParameters)
{
	HRESULT hr = -1;

	m_Width = pd3dParameters->BackBufferWidth;
	m_Height = pd3dParameters->BackBufferHeight;

	hr = Resize(m_Width, m_Height);

	return hr;
}

//=============================================================================
// �T�C�Y�ݒ肵����
//=============================================================================
HRESULT CShaderSquare::Resize(UINT Width, UINT Height)
{
	HRESULT hr = -1;

	m_Width = Width;
	m_Height = Height;

	D3D2DVERTEX* vtx;
	hr = m_pd3d2DVertex->Lock(0, 0, (void**)&vtx, 0);
	if (FAILED(hr))
		return -3;

	//���_�̍��W
	vtx[0].x = 0.0f;           vtx[0].y = 0.0f;            vtx[0].z = 0.0f; vtx[0].rhw = 1.0f;
	vtx[1].x = (float)m_Width; vtx[1].y = 0.0f;            vtx[1].z = 0.0f; vtx[1].rhw = 1.0f;
	vtx[2].x = 0.0f;           vtx[2].y = (float)m_Height; vtx[2].z = 0.0f; vtx[2].rhw = 1.0f;
	vtx[3].x = (float)m_Width; vtx[3].y = (float)m_Height; vtx[3].z = 0.0f; vtx[3].rhw = 1.0f;

	//�e�N�Z��
	vtx[0].tu = 0.0f + 0.5f / (float)m_Width; vtx[0].tv = 0.0f + 0.5f / (float)m_Height;
	vtx[1].tu = 1.0f + 0.5f / (float)m_Width; vtx[1].tv = 0.0f + 0.5f / (float)m_Height;
	vtx[2].tu = 0.0f + 0.5f / (float)m_Width; vtx[2].tv = 1.0f + 0.5f / (float)m_Height;
	vtx[3].tu = 1.0f + 0.5f / (float)m_Width; vtx[3].tv = 1.0f + 0.5f / (float)m_Height;

	//���_�J���[
	vtx[0].color = 0xFFFFFFFF;
	vtx[1].color = 0xFFFFFFFF;
	vtx[2].color = 0xFFFFFFFF;
	vtx[3].color = 0xFFFFFFFF;

	m_pd3d2DVertex->Unlock();

	hr = S_OK;

	return hr;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CShaderSquare::Draw()
{
	m_pd3dDevice->SetFVF(D3D2DFVF);
	m_pd3dDevice->SetStreamSource(0, m_pd3d2DVertex, 0, sizeof(D3D2DVERTEX));
	//���|���S�����Q���g�p
	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

UINT CShaderSquare::GetWidth()
{
	return m_Width;
}

UINT CShaderSquare::GetHeight()
{
	return m_Height;
}