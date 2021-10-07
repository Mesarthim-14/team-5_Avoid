#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
// 3D�|���S���N���X�w�b�_�[ [scene3D.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene_base.h"

//=========================================================================
// 3D�|���S���N���X
//=========================================================================
class CScene3D :public CSceneBase
{
public:
	CScene3D(PRIORITY Priority = PRIORITY_EFFECT);	// �R���X�g���N�^
	virtual ~CScene3D();							// �f�X�g���N�^
	
	virtual HRESULT Init(void);						// ����������
	virtual void Uninit(void);						// �I������
	virtual void Update(void);						// �X�V����
	virtual void Draw(void) = 0;					// �`�揈��

protected:
	void SetVertexPos(void);						// ���W�̍X�V

	// Set�֐�
	void SubAlpha(float fAlphaNum);												// �����x�̌��Z
	void InitAnimation(int nPatternNum, int nSpeed, int nLoop);					// �A�j���[�V������񏉊���
	void SetColor(D3DXCOLOR color);												// �J���[�̐ݒ�
	void ScaleUp(float fScale);													// �g�又��
	void SetMove(D3DXVECTOR3 move)			{ m_move = move; }					// �ړ���
	void SetAlpha(bool bAlpha)				{ m_bAlpha = bAlpha; }				// �A���t�@�e�X�g
	void SetAlphaNum(int nAlphaNum)			{ m_nAlphaTestNum = nAlphaNum; }	// �A���t�@�e�X�g�̒l
	void SetBlend(bool bBlend)				{ m_bBlend = bBlend; }				// ���Z����
	void SetMtxWorld(D3DXMATRIX mtxWorld)	{ m_mtxWorld = mtxWorld; }			// ���[���h�}�g���N�X�̐ݒ�

	// Get�֐�
	D3DXMATRIX GetMtxWorld(void)	{ return m_mtxWorld; }				// ���[���h�}�g���N�X
	int GetAlphaTestNum(void)		{ return m_nAlphaTestNum; }			// �A���t�@�e�X�g�̒l

private:
	// private�֐�
	void CreateVertex(void);						// ���_�̐ݒ�
	void UpdateAnimation(void);						// �A�j���[�V�����̍X�V

	// �����o�ϐ�
	D3DXMATRIX	m_mtxWorld;		// ���[���h�}�g���N�X
	D3DXVECTOR3 m_move;			// �ړ���
	int m_nLife;				// ���C�t
	int m_nAlphaTestNum;		// �����̒l
	float m_fScaleNum;			// �g��l
	float m_fAlphaNum;			// �����x
	bool m_bAlpha;				// �������g���t���O
	bool m_bBlend;				// ���Z����
};
#endif