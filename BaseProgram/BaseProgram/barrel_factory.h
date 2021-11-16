#ifndef _BARREL_FACTORY_H_
#define _BARREL_FACTORY_H_
//=============================================================================
//
// �N���X [barrel_factory.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "main.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CBarrelFactory
{
public:
	CBarrelFactory();		// �R���X�g���N�^
	~CBarrelFactory() {}	// �f�X�g���N�^

	static CBarrelFactory *Create();	// �C���X�^���X����
	void Update();						// �X�V����

	void CreateBarrel();				// �M�̐���
private:
	// private�֐�
	int m_nCreateCount;
};

#endif