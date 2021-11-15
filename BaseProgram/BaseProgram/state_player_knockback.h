#ifndef _STATE_PLAYER_KNOCKBACK_H_
#define _STATE_PLAYER_KNOCKBACK_H_
//=====================================================================
//
//	�W�����v��ԊǗ��N���X [state_player_knockback.h]
//	Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player.h"

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
class CPlayer;

//=====================================================================
// �N���X��`
//=====================================================================
class CPlayerStateKnockback : public CPlayerState
{
public:
	CPlayerStateKnockback();		// �R���X�g���N�^
	~CPlayerStateKnockback();	// �f�X�g���N�^

	static CPlayerStateKnockback* Create();	// �C���X�^���X����
	void Init();						// ����������
	void Update()override;				// �X�V����

private:
	int m_nStanCount;
};
#endif