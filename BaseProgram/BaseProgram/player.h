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
#include "json.h"

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter
{
public:
	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);	// �R���X�g���N�^
	~CPlayer();											// �f�X�g���N�^

	static CPlayer*Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// �N���G�C�g

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��
	void ShowInfo(void);		// ���
	HRESULT LoadInfo(void);		// �f�[�^���[�h
	void SaveInfo(void);		// �f�[�^�Z�[�u
	void SubLife(int nDamage);			// �_���[�W

private:
	// private�֐�
	void UpdateState(void);		// �v���C���[�̏��
	void PlayerControl(void);	// �v���C���[�̐���
	void Move(void);			// �ړ�����
	void KeyBoardMove(void);	// �ړ��֐�
	void UpdateRot(void);		// �p�x�̍X�V����
	void ChangeModel(void);		// ���f���`�F���W

	typedef enum
	{
		SLIME_LITTLESIZE = 0,
		SLIME_MIDDLESIZE,
		SLIME_LARGESIZE
	}SLIME_STATE;//�X���C���̏�ԁi�傫���j

	// �����o�ϐ�
	D3DXVECTOR3 m_rotDest;		// ��](�ڕW�l)
	D3DXVECTOR3 m_Inertia;		// ����
	float m_fInertiaNum;		// �����̒l
	float m_fRotationSpeed;		// ��]�̑��x
	bool m_bMove;				// �ړ��̃t���O
	int m_nHP;				    // �X���C��HP ~100�܂Łi�p�[�Z���g�j
	SLIME_STATE	m_SlimeState;	// �X���C���̏��
};
#endif