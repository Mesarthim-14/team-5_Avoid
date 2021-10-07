#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter
{
public:
	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);			// �R���X�g���N�^
	~CPlayer();													// �f�X�g���N�^

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �N���G�C�g

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

private:
	// private�֐�
	void UpdateState(void);		// �v���C���[�̏��
	void PlayerControl(void);	// �v���C���[�̐���
	void Move(void);			// �ړ�����

	// �����o�ϐ�
	D3DXVECTOR3 m_rotDest;		// ��](�ڕW�l)
	bool m_bMove;				// �ړ��̃t���O
};
#endif