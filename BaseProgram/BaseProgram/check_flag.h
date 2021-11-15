#ifndef _CHECK_FLAG_H_
#define _CHECK_FLAG_H_
//=============================================================================
//
// �e�X�g���f���N���X [check_flag.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CCheckFlag : public CModel
{
public:
	CCheckFlag(PRIORITY = PRIORITY_TEST_MODEL);			// �R���X�g���N�^
	~CCheckFlag();										// �f�X�g���N�^

	static CCheckFlag *Create(const D3DXVECTOR3 &pos);	// �C���X�^���X����
	HRESULT Init(const D3DXVECTOR3 &pos);				// ����������
	bool Collision();									// �����蔻��
	D3DXVECTOR3 GetPos();								// ���W�̎擾
private:

};

#endif