#ifndef _MODEL_H_
#define _MODEL_H_
//=============================================================================
//
// ���f���N���X [model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// �O���錾
//=============================================================================
class CModelInfo;

//=============================================================================
// ���f���N���X
//=============================================================================
class CModel : public CScene
{
public:
	CModel(PRIORITY Priority);	// �R���X�g���N�^
	virtual ~CModel();

	virtual HRESULT Init(void);									// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void);									// �X�V����
	virtual void Draw(void);									// �`�揈��
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �C���X�^���X����

	// Get�֐�
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetRot();
	CModelInfo* GetModelInfo(void) { return m_pModelInfo; }		// ���f���̏��

protected:
	bool PlayerDisCollision(const float &fDistanse);							// �v���C���[�Ƃ̋����̓����蔻��

	// Set�֐�
	void SetMove(const D3DXVECTOR3 move)	{ m_move = move; }					// �ړ��ʂ̐ݒ�
	void SetSize(D3DXVECTOR3 size)			{ m_size = size; }					// �T�C�Y�̐ݒ�
	void SetTexPattern(int TexPattern)		{ m_nTexPattern = TexPattern; }		// �e�N�X�`���̃p�^�[��
	void SetLife(int nLife)					{ m_nLife = nLife; }				// ���C�t�̐ݒ�
	void SetScale(D3DXVECTOR3 scale)		{ m_scale = scale; }				// �g�嗦

	D3DXVECTOR3 &GetMove(void)			{ return m_move; }				// �ړ��ʂ̏��
	D3DXVECTOR3 GetSize(void)const		{ return m_size; }				// �T�C�Y�̐ݒ�
	int GetTexPattern(void)				{ return m_nTexPattern; }		// �e�N�X�`��
	int GetLife(void)					{ return m_nLife; }				// ���C�t�̐ݒ�

private:
	// private�֐�
	void HasPtrDelete(void);									// �ێ��|�C���^�̊J������
	void CreateInfoPtr(void);									// ���̃|�C���^����

	// �����o�ϐ�
	CModelInfo* m_pModelInfo;			// ���f���̏��
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXVECTOR3 m_scale;				// �g�嗦
	int m_nTexPattern;					// �e�N�X�`���̃p�^�[����
	int m_nLife;						// ���C�t
};
#endif 