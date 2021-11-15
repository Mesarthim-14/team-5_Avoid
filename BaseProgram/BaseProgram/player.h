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
#include "skinmesh_model.h"

//=============================================================================
// �O���錾
//=============================================================================
class CPlayerState;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter
{
public:
	typedef enum
	{
		ACTION_NONE = -1,
		ACTION_IDOL,
		ACTION_JUMP,
		ACTION_LANDING,
		ACTION_WALK,
	//	ACTION_AVOID,
		ACTION_MAX
	}ACTION_STATE;//�s�����

	enum STATE_PLAYER
	{
		STATE_PLAYER_NONE = -1,		// �����l
		STATE_PLAYER_IDOL,			// �ʏ���
		STATE_PLAYER_JUMP,			// �W�����v���
		STATE_PLAYER_AVOID,			// ������
		STATE_PLAYER_STUN,			// �C��
		STATE_PLAYER_KNOCK_BACK,	// �m�b�N�o�b�N
		STATE_PLAYER_MAX,			// �ő�l
	};

	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);	// �R���X�g���N�^
	~CPlayer();											// �f�X�g���N�^

	static CPlayer*Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// �N���G�C�g

	HRESULT Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��
	void ShowInfo(void);							// ���
	HRESULT LoadInfo(void);							// �f�[�^���[�h
	void SaveInfo(void);							// �f�[�^�Z�[�u
	void SubLife(int nDamage);						// �_���[�W
	CSkinmeshModel* GetCurrentSkinMeshPtr();		// ���݂̃X�L�����b�V���|�C���^
	void ChangeState(CPlayerState* pPlayerState);	// ��ԃ`�F���W

	// Set�֐�
	void SetAction(int nCount, int nMaxAction)			{ m_nMaxAction[nCount] = nMaxAction; }
	inline void SetMove(const D3DXVECTOR3 &move)		{ CCharacter::SetMove(move); }	// �ړ��ʐݒ�
	inline void SetRotDest(const D3DXVECTOR3& rotDest)	{ m_rotDest = rotDest; }		// �ړI�̊p�x
	inline void SetAngle(const float& fAngle)			{ m_fAngle = fAngle; }			// �A���O��

	// Get�֐�
	inline int GetLife()const				{ return m_nHP; }			// HP�̏��
	inline float GetAngle()const			{ return m_fAngle; }		// �A���O��
	inline D3DXVECTOR3 GetRotDest()const	{ return m_rotDest; }		// �ړI
	inline D3DXVECTOR3 GetInertia()const	{ return m_Inertia; }		// �����̏��
	inline float GetInertiaNum()const		{ return m_fInertiaNum; }	// �����̒l

private:
	// private�֐�
	void UpdateState(void);			// �v���C���[�̏��
	void PlayerControl(void);		// �v���C���[�̐���
	void UpdateRot(void);			// �p�x�̍X�V����
	void ChangeModel(void);			// ���f���`�F���W
	void Action(void);				// �A�N�V����
	void Jump(void);				// �W�����v
	void Avoidance(void);			// ����A�N�V����
	void ReSporn();					// ���X�|�[��
	void CreateModel();				// ���f������

	typedef enum
	{
		SLIME_LITTLESIZE = 0,
		SLIME_MIDDLESIZE,
		SLIME_LARGESIZE,
		SLIME_STATE_MAX
	}SLIME_STATE;//�X���C���̏�ԁi�傫���j

	// �����o�ϐ�
	D3DXVECTOR3 m_rotDest;								// ��](�ڕW�l)
	D3DXVECTOR3 m_Inertia;								// ����
	float m_fInertiaNum;								// �����̒l
	float m_fRotationSpeed;								// ��]�̑��x
	bool m_bMove;										// �ړ��̃t���O
	int m_nHP;											// �X���C��HP ~100�܂Łi�p�[�Z���g�j
	SLIME_STATE	m_SlimeState;							// �X���C���̏��
	float m_fAngle;										// �J���������A���O��
	float m_fAngleSpeed;								// �ڕW�����܂Ō������X�s�[�h
	ACTION_STATE m_ActionState;							// �s�����
	CSkinmeshModel *m_pSkinmeshModel[SLIME_STATE_MAX];	// �X�L�����b�V�����f���|�C���^
	int m_nMaxAction[SLIME_STATE_MAX];					// �A�N�V�����̍ő吔

	CPlayerState* m_pCurrentState;						// ���݂̏�ԃ|�C���^
	CPlayerState* m_pNextState;							// ���̏�ԃ|�C���^
};
#endif