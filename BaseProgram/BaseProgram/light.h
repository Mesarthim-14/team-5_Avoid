#ifndef _LIGHT_H_
#define _LIGHT_H_
//=============================================================================
//
// ���C�g���� [light.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CLight
{
public:
	CLight();				// �R���X�g���N�^
	~CLight();				// �f�X�g���N�^

	static CLight *Create();	// �C���X�^���X��������
	HRESULT Init();				// ����������
	void Uninit();				// �I������
	void Update();				// �X�V����
	void ShowLightInfo();		//imgui ���C�g���\��

	// Set�֐�
	void SetPos(D3DXVECTOR3 pos)	{ m_Light.Position = pos; }
	void SetVecDir(D3DXVECTOR3 Dir);

	// Get�֐�
	D3DXVECTOR3 GetPos()		{ return m_Light.Position; }	// ���W
	D3DXVECTOR3 GetLightDir()	{ return m_vecDir; }			// ���C�g�̌���

private:
	D3DLIGHT9 m_Light;		// ���C�g�̕ϐ�
	D3DXVECTOR3 m_vecDir;	// ���C�g�̌���
};
#endif