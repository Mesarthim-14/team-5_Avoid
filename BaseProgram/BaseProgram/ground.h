#ifndef _GROUND_H_
#define _GROUND_H_
//=============================================================================
//
// �n�ʃN���X [ground.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "meshfield.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CGround : public CMeshField
{
public:
	CGround(PRIORITY = PRIORITY_UI);		// �R���X�g���N�^
	~CGround();							// �f�X�g���N�^

	static CGround *Create(void);		// �C���X�^���X����
	HRESULT Init(void);					// ����������
	void Uninit(void);					// ����������
	void Update(void);					// �X�V����
	void Draw(void);					// �`��
private:
};

#endif