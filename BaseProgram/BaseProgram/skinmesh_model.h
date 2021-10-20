#ifndef _SKINMESH_MODEL_H_
#define _SKINMESH_MODEL_H_
//=============================================================================
//
// �X�L�����b�V���p���f���N���X [skinmesh_model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "xfile.h"
#include "skinmesh.h"

//=============================================================================
// �O���錾
//=============================================================================
class CModelInfo;


//=============================================================================
// ���f���N���X
//=============================================================================
class CSkinmeshModel : public CScene
{
public:
	CSkinmeshModel(PRIORITY Priority = PRIORITY_EFFECT);	// �R���X�g���N�^
	~CSkinmeshModel();

	HRESULT Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��
	static CSkinmeshModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �C���X�^���X����

protected:
	// Set�֐�
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }					// �ړ��ʂ̐ݒ�
	void SetSize(D3DXVECTOR3 size) { m_size = size; }					// �T�C�Y�̐ݒ�
	void SetTexPattern(int TexPattern) { m_nTexPattern = TexPattern; }		// �e�N�X�`���̃p�^�[��
	void SetLife(int nLife) { m_nLife = nLife; }				// ���C�t�̐ݒ�
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }				// �g�嗦

																		// Get�֐�
	D3DXVECTOR3 &GetMove(void) { return m_move; }				// �ړ��ʂ̏��
	D3DXVECTOR3 GetSize(void)const { return m_size; }				// �T�C�Y�̐ݒ�
	int GetTexPattern(void) { return m_nTexPattern; }		// �e�N�X�`��
	int GetLife(void) { return m_nLife; }				// ���C�t�̐ݒ�
	CModelInfo* GetModelInfo(void) { return m_pModelInfo; }		// ���f���̏��

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
	ID3DXAnimationController * m_pAnimetionController; //�A�j���[�V�����R���g���[���[
	SkinMesh::SMD3DXFRAME				 * m_pRootFrame;			// ���[�g�t���[��
	// SMD3DXMESHCONTAINER(���b�V��)�֘A�̏���ۑ��p
	std::vector<SkinMesh::SMD3DXMESHCONTAINER*> m_cont;
	//�{�[���R���r�l�[�V�����e�[�u���̃|�C���^�擾
	std::vector<D3DXBONECOMBINATION*> m_combs;

};
#endif 