#ifndef _SKINMESH_MODEL_H_
#define _SKINMESH_MODEL_H_
//=============================================================================
//
// �X�L�����b�V���p���f���N���X [skinmesh_model.h]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "xfile.h"
#include "skinmesh.h"
#include "model_info.h"

//=============================================================================
// �O���錾
//=============================================================================
class CModelInfo;
class IHighLevelAnimController;

//=============================================================================
// ���f���N���X
//=============================================================================
class CSkinmeshModel : public CScene
{
public:

	typedef enum
	{
		MODEL_PLAYER_100 = 0,//�X���C���P�O�O���̏��
		MODEL_MAX
	}MODEL;//���f�����O
	CSkinmeshModel(PRIORITY Priority = PRIORITY_EFFECT);	// �R���X�g���N�^
	~CSkinmeshModel();

	HRESULT Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��
	static CSkinmeshModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �C���X�^���X����
	IHighLevelAnimController * GetHLcontroller(void) { return m_HLcontroller; };
	void SetModelNumber(MODEL model);
	void SetPos(D3DXVECTOR3 pos) { m_pModelInfo->SetPos(pos); }						// ���݂̍��W���
	void SetRot(D3DXVECTOR3 rot){ m_pModelInfo->SetRot(rot); }						// �p�x���

protected:
	// Set�֐�
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }				// �ړ��ʂ̐ݒ�
	void SetSize(D3DXVECTOR3 size) { m_size = size; }					// �T�C�Y�̐ݒ�
	void SetTexPattern(int TexPattern) { m_nTexPattern = TexPattern; }	// �e�N�X�`���̃p�^�[��
	void SetLife(int nLife) { m_nLife = nLife; }						// ���C�t�̐ݒ�
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }				// �g�嗦

	// Get�֐�
	D3DXVECTOR3 &GetMove(void) { return m_move; }			// �ړ��ʂ̏��
	D3DXVECTOR3 GetSize(void)const { return m_size; }		// �T�C�Y�̐ݒ�
	int GetTexPattern(void) { return m_nTexPattern; }		// �e�N�X�`��
	int GetLife(void) { return m_nLife; }					// ���C�t�̐ݒ�
	CModelInfo* GetModelInfo(void) { return m_pModelInfo; }	// ���f���̏��

private:
	// private�֐�
	void HasPtrDelete(void);	// �ێ��|�C���^�̊J������
	void CreateInfoPtr(void);	// ���̃|�C���^����

	// �����o�ϐ�
	CModelInfo* m_pModelInfo;									// ���f���̏��
	D3DXVECTOR3 m_move;											// �ړ���
	D3DXVECTOR3 m_size;											// �T�C�Y
	D3DXVECTOR3 m_scale;										// �g�嗦
	int m_nTexPattern;											// �e�N�X�`���̃p�^�[����
	int m_nLife;												// ���C�t
	ID3DXAnimationController * m_pAnimetionController;			//�A�j���[�V�����R���g���[���[
	SkinMesh::SMD3DXFRAME				 * m_pRootFrame;		// ���[�g�t���[��
	std::vector<SkinMesh::SMD3DXMESHCONTAINER*> m_cont;			// SMD3DXMESHCONTAINER(���b�V��)�֘A�̏���ۑ��p
	std::vector<D3DXBONECOMBINATION*> m_combs;					//�{�[���R���r�l�[�V�����e�[�u���̃|�C���^�擾
	IHighLevelAnimController * m_HLcontroller;					//�n�C���x���A�j���[�V�����R���g���[���[
	static const char* m_aParam[MODEL_MAX];						//���f���p�X��
	MODEL			   m_ModelNum;								// ���f���̖��O
};
#endif 