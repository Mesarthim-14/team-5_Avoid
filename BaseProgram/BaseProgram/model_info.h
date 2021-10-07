#ifndef _MODEL_INFO_H_
#define _MODEL_INFO_H_
//=============================================================================
//
// ���f���̏��N���X[model_info.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "xfile.h"

//=============================================================================
// �O���錾
//=============================================================================
class CShadow;

//=============================================================================
//�K�w���f���N���X
//=============================================================================
class CModelInfo
{
public:
	// ���f���̎��
	enum MODEL_TYPE
	{
		MODEL_TYPE_NONE = 0,	// �ݒ�Ȃ�
		MODEL_TYPE_CHARACTER,	// �L�����N�^�[
		MODEL_TYPE_OBJECT,		// �I�u�W�F�N�g
		MODEL_TYPE_MAX			// �ő�l
	};

	CModelInfo(MODEL_TYPE type);		// �R���X�g���N�^
	~CModelInfo();		// �f�X�g���N�^

	static CModelInfo *Create(MODEL_TYPE type);	// �C���X�^���X����

	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Draw(D3DXVECTOR3 rot);			// �`�揈��
	void ShadowDraw(D3DXVECTOR3 rot);	// �e�̕`��
	void CreateShadowPtr(void);			// �e�̐���

	// Set�֐�
	void SetPos(const D3DXVECTOR3 pos)		{ m_pos = pos; }					// ���W
	void SetRot(const D3DXVECTOR3 rot)		{ m_rot = rot; }					// �����ݒ�
	void SetModel(CXfile::MODEL model)		{ m_model = model; }				// ���f�����̐ݒ�
	void SetMtxWorld(D3DXMATRIX mtxWorld)	{ m_mtxWorld = mtxWorld; }			// �}�g���N�X���[���h�ݒ�
	void SetModelStatus(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model);	// ���f�����̐ݒ�
	D3DXMATRIX SetShadowInfo(D3DXVECTOR3 rot, D3DXMATRIX pParent);				// �e�̏��̐ݒ�

	// Get���
	D3DXVECTOR3 &GetPos(void)			{ return m_pos; }					// ���W���
	D3DXVECTOR3 &GetRot(void)			{ return m_rot; }					// �p�x�̏��
	D3DXMATRIX GetMtxWorld(void)		{ return m_mtxWorld; }				// ���[���h�}�g���N�X���
	D3DXMATRIX GetOldMtxWorld(void)		{ return m_OldMtxWorld; }			// �Â����[���h�}�g���N�X�̏��
	LPD3DXMESH GetMesh(void)			{ return m_model.pMesh; }			// ���f�����擾
	LPD3DXBUFFER GetBuffMat(void)		{ return m_model.pBuffMat; }		// �o�b�t�@���
	DWORD GetNumMat(void)				{ return m_model.dwNumMat; }		// �}�g���N�X�̐�
	CXfile::MODEL GetModel(void)		{ return m_model; }					// ���f���̏��
	CShadow* GetShadow(void)			{ return m_pShadow; }				// �e�̃|�C���^
	D3DXVECTOR3 GetMtxPos(void);											// �}�g���N�X���W

private:
	// private�֐�
	void HasPtrDelete(void);			// �ێ��|�C���^�̊J������

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXMATRIX m_OldMtxWorld;	// �Â����[���h���W
	CXfile::MODEL m_model;		// ���f�����
	MODEL_TYPE m_type;			// ���

	// �e�̐����p
	CShadow *m_pShadow;		// �e�̃|�C���^
	bool m_bUseShadow;		// �e�̎g�p�t���O

	// ���f���̏�񃊃X�g
	static list<CModelInfo*> m_ModelInfoList[MODEL_TYPE_MAX];
};

#endif 