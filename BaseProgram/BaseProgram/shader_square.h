#ifndef _SHADER_SQUARE_H_
#define _SHADER_SQUARE_H_
//=============================================================================
//
// �V�F�[�_�p�̃|���S�������N���X [shader_square.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CShaderSquare
{
public:
	CShaderSquare(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters);	// �R���X�g���N�^
	CShaderSquare(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height);				// �R���X�g���N�^
	~CShaderSquare();																	// �f�X�g���N�^
	void Uninit();																		// �I������

	//2D�|���S���̃T�C�Y���擾
	UINT GetWidth();
	UINT GetHeight();
	//2D�|���S���̃T�C�Y��ύX
	HRESULT Resize(UINT Width, UINT Height);
	HRESULT Resize(D3DPRESENT_PARAMETERS* pd3dParameters);
	//������
	HRESULT Load();
	//2D�|���S���������_�����O
	void Draw();

private:
	//���_�t�H�[�}�b�g
	DWORD D3D2DFVF;

	typedef struct _D3D2DVERTEX
	{
		float x, y, z, rhw;	//���_���W
		DWORD color;		//���_�J���[
		float tu, tv;		//�e�N�Z��
	}D3D2DVERTEX;

	LPDIRECT3DVERTEXBUFFER9 m_pd3d2DVertex;
	LPDIRECT3DDEVICE9 m_pd3dDevice;

	//�Q�c�|���S���̃T�C�Y
	UINT m_Width, m_Height;
};

#endif