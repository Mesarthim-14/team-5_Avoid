#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//=============================================================================
//
// ���b�V���t�B�[���h�N���X [meshfield.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "mesh_3d.h"

//=============================================================================
// ���b�V���t�B�[���h�N���X
//=============================================================================
class CMeshField : public CMesh3d
{
public:
	CMeshField(PRIORITY = PRIORITY_0);	// �R���X�g���N�^
	~CMeshField();						// �f�X�g���N�^

	virtual HRESULT Init(void);			// ����������
	virtual void Update(void);			// �X�V����
	virtual void Draw(void);			// �`�揈��
	static CMeshField*Create(void);		// ���b�V���t�B�[���h

protected:
	void SetInfo(const D3DXVECTOR3 &size, const INT_VERTEX_2D &PieceNum);			// ���̐ݒ�

private:
	// private�֐�
	void CreateVerterx(void);										// ���_�̐���
	void InitAnimation(int nPatternNum, int nSpeed, int nLoop) {}	// �A�j���[�V������񏉊���
	void UpdateAnimation(void) {}									// �A�j���[�V�����X�V
};

#endif