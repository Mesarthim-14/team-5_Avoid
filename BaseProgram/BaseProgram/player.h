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
#include "skinmesh_model.h"

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
	void SubLife(int nDamage);	// �_���[�W

private:
	// private�֐�
	void UpdateState(void);		// �v���C���[�̏��
	void PlayerControl(void);	// �v���C���[�̐���
	void Move(void);			// �ړ�����
	void KeyBoardMove(void);	// �ړ��֐�
	void UpdateRot(void);		// �p�x�̍X�V����
	void ChangeModel(void);		// ���f���`�F���W
	void Action(void);			// �A�N�V����
	void Jump(void);			// �W�����v
	void Avoidance(void);		// ����A�N�V����
	void JumpProcess(void);		// �W�����v���̏���
	void AnimationProcess(void); // �A�j���[�V��������
	typedef enum
	{
		SLIME_LITTLESIZE = 0,
		SLIME_MIDDLESIZE,
		SLIME_LARGESIZE,
		SLIME_STATE_MAX
	}SLIME_STATE;//�X���C���̏�ԁi�傫���j

	typedef enum
	{
		ACTION_NONE = 0,
		ACTION_JUMP,
		ACTION_AVOID,
		ACTION_STAN
	}ACTION_STATE;//�s�����

	// �����o�ϐ�
	D3DXVECTOR3 m_rotDest;		// ��](�ڕW�l)
	D3DXVECTOR3 m_Inertia;		// ����
	float m_fInertiaNum;		// �����̒l
	float m_fRotationSpeed;		// ��]�̑��x
	bool m_bMove;				// �ړ��̃t���O
	int m_nHP;				    // �X���C��HP ~100�܂Łi�p�[�Z���g�j
	SLIME_STATE	m_SlimeState;	// �X���C���̏��
	float m_fAngle;				// �J���������A���O��
	float m_fAngleSpeed;		// �ڕW�����܂Ō������X�s�[�h
	ACTION_STATE m_ActionState; // �s�����
	float m_fJumpValue;			// �W�����v��
	float m_fDushJumpValue;		// �ړ��W�����v���̉��ړ����Z��
	float m_fAvoidValueY;		// ����ړ��ʁi������j
	float m_fAvoidValueXZ;		// ����ړ��ʁi�������j
	int   m_nChargeJumpCount;   // ���߃W�����v�J�E���g
	bool m_bIsReadyChargeJump;	// ���߃W�����v����������
	CSkinmeshModel * m_pSkinmeshModel[SLIME_STATE_MAX]; //�X�L�����b�V�����f���|�C���^
	float m_fJumpTimeCount;		// �W�����v���ԃJ�E���g
	bool m_fJumpCheck;			// �W�����v���n�߂���
};
#endif