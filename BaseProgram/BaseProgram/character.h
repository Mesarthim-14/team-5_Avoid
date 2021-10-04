#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// �L�����N�^�[�N���X�w�b�_  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CCharacter : public CScene
{
public:

	//=============================================================================
	// �L�����N�^�[�̏��
	//=============================================================================
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_DEAD,
		STATE_MAX
	};

	CCharacter(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	virtual ~CCharacter();											// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	virtual void Uninit();											// �I������
	virtual void Update();											// �X�V����
	virtual void Draw();											// �`�揈��

	void ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum);			// ���f���̐���
	void ModelAnimeUpdate(void);									// ���f���A�j���[�V����
	void Gravity(void);												// �d��
	void Landing(float fHeight);									// ���n
	void SetMotion(int nMotionState);								// ���[�V�����̐ݒ�
	void SetShadowRotCalculation(void);								// �e����

	// �������z�֐�
	virtual void UpdateState(void) = 0;								// �L�����N�^�[���
	virtual void Move(void) = 0;									// �ړ��֐�

	// Set�֐�
	void SetPos(D3DXVECTOR3 &pos)		{ m_pos = pos; }			// ���W�̐ݒ�
	void SetPosOld(D3DXVECTOR3 &posOld) { m_posOld = posOld; }		// ���W�̐ݒ�
	void SetMove(D3DXVECTOR3 &move)		{ m_move = move; }			// �ړ��ʂ̐ݒ�
	void SetRot(D3DXVECTOR3 &rot)		{ m_rot = rot; }			// �p�x�̐ݒ�
	void SetSize(D3DXVECTOR3 &size)		{ m_size = size; }			// �T�C�Y�ݒ�
	void SetSpeed(float fSpeed)			{ m_fSpeed = fSpeed; }		// ���x�̐ݒ�
	void SetState(STATE state)			{ m_State = state; }		// ��Ԑݒ�
	void SetLanding(bool bLanding)		{ m_bLanding = bLanding; }	// ���n
	void SetUseShadow(void)				{ m_bUseShadow = true; }	// �e�̎g�p����
	void SetGravityFlag(bool bFlag)		{ m_bGravity = bFlag; }		// �d�͂̃t���O

	// Get�֐�
	D3DXVECTOR3 &GetPos(void)				{ return m_pos; }						// ���݂̍��W���
	D3DXVECTOR3 &GetOldPos(void)			{ return m_posOld; }					// �Â����W���
	D3DXVECTOR3 &GetRot(void)				{ return m_rot; }						// �p�x���
	D3DXVECTOR3 &GetMove(void)				{ return m_move; }						// �ړ��ʂ̏��
	D3DXVECTOR3 &GetSize(void)				{ return m_size; }						// �T�C�Y�擾
	CModelAnime *GetModelAnime(int nCount)	{ return m_apModelAnime.at(nCount); }	// ���[�V�����̃J�E���g���
	CMotion *GetMotion(void)				{ return m_pMotion; }					// ���[�V�����̃|�C���^���
	int GetStateCounter(void)				{ return m_nStateCounter; }				// ��ԃJ�E���^�[�̏��
	int GetPartsNum(void)					{ return m_apModelAnime.size(); }		// �p�[�c���擾
	float GetSpeed(void)					{ return m_fSpeed; }					// �X�s�[�h�̏��
	STATE GetState(void)					{ return m_State; }						// ��Ԏ擾

private:
	vector<CModelAnime*> m_apModelAnime;	// ���f���p�[�c�p�|�C���^
	CMotion *m_pMotion;						// ���[�V�����N���X�̃|�C���^
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_posOld;					// �Â����W
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_rot;						// ���݂̉�]
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	STATE m_State;							// ���
	int m_nStateCounter;					// ��Ԃ̃J�E���^�[
	int m_nParts;							// �p�[�c��
	float m_fSpeed;							// �ړ���
	bool m_bLanding;						// ���n�t���O
	bool m_bUseShadow;						// �e������t���O
	bool m_bGravity;						// �d�͂�������t���O
};
#endif
