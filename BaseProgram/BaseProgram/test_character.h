#ifndef _TEST_CHARACTER_H_
#define _TEST_CHARACTER_H_
//=============================================================================
//
// �e�X�g�L�����N�^�[�N���X�w�b�_�[ [test_character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "modelanime.h"
#include "json.h"

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CTestCharacter : public CCharacter
{
public:
	CTestCharacter(PRIORITY Priority = PRIORITY_CHARACTER);	// �R���X�g���N�^
	~CTestCharacter();										// �f�X�g���N�^

	static CTestCharacter*Create(D3DXVECTOR3 pos);	// �N���G�C�g

	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��
	void UpdateState(void);				// �v���C���[�̏��
	void Move(void);					// �ړ�����

private:
	HRESULT JsonLoad(void);	
	void JsonWrite(void);
	void CreateModel();

	D3DXVECTOR3 m_rotDest;							// ��](�ڕW�l)
	bool m_bMove;									// �ړ��̃t���O
};
#endif