#ifndef _CHECK_POINT_H_
#define _CHECK_POINT_H_
//=============================================================================
//
// �N���X [check_point.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "main.h"

//=========================================================================
// �O���錾
//=========================================================================
class CCheckFlag;

//=========================================================================
// �N���X��`
//=========================================================================
class CCheckPoint
{
public:
	CCheckPoint();		// �R���X�g���N�^
	~CCheckPoint();		// �f�X�g���N�^

	static CCheckPoint *Create();							// �C���X�^���X����
	HRESULT Init();											// ����������
	void Uninit();											// �I������
	void Update();											// �X�V����
	D3DXVECTOR3 GetPointPos()		{ return m_PointPos; }	// �`�F�b�N�|�C���g�̍��W
	inline int GetPointNum()const	{ return m_nPointNum; }	// �`�F�b�N�|�C���g�̒l
private:
	// private�֐�
	void CreateFlag();					// ���̐���

	D3DXVECTOR3 m_PointPos;				// ���W�̎擾
	vector<CCheckFlag*> m_apChackFlag;	// ���̃|�C���^
	int m_nPointNum;					// ���݂̔ԍ�
};

#endif