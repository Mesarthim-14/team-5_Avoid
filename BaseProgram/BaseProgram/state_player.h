#ifndef _STATE_PLAYER_H_
#define _STATE_PLAYER_H_
//=====================================================================
//
//	��ԊǗ��N���X [state_player.h]
//	Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state.h"

//=====================================================================
// �O���錾
//=====================================================================
class CPlayer;

//=====================================================================
// �N���X��`
//=====================================================================
class CPlayerState : public CState
{
public:
	CPlayerState();				// �R���X�g���N�^
	~CPlayerState();			// �f�X�g���N�^

protected:
	virtual void SetAnimation(const UINT &animID, const FLOAT &time);	// �A�j���[�V�����ݒ�
	void MoveByKeyboard(CPlayer* &pPlayer);								// ���͏���

private:
	 float m_fAngleSpeed;					// �ڕW�����܂Ō������X�s�[�h 
	 bool m_bMove[2];							// �ړ��̃t���O
};
#endif