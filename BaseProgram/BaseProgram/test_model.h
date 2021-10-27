#ifndef _TEST_MODEL_H_
#define _TEST_MODEL_H_
//=============================================================================
//
// �e�X�g���f���N���X [test_model.h]
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
class CTestModel : public CModel
{
public:
	CTestModel(PRIORITY = PRIORITY_TEST_MODEL);	// �R���X�g���N�^
	~CTestModel();								// �f�X�g���N�^

	static CTestModel *Create(void);	// �C���X�^���X����
	HRESULT Init(void);					// ����������
	void Uninit(void);					// ����������
	void Update(void);					// �X�V����
	void Draw(void);					// �`��

	CModelInfo* GetModelInfo(void) { return CModel::GetModelInfo(); }	// ���f���̏��

private:
};

#endif