#ifndef _STATE_PLAYER_RESPAWN_H_
#define _STATE_PLAYER_RESPAWN_H_
//=====================================================================
//
// ���X�|�[����ԃN���X [state_player_respawn.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CPlayerStateRespawn : public CPlayerState
{
public:
    CPlayerStateRespawn();  // �R���X�g���N�^
    ~CPlayerStateRespawn(); // �f�X�g���N�^

    static CPlayerStateRespawn* Create();  // �C���X�^���X����
    void Init();                           // ����������
    void Update()override;                 // �X�V����

private:
};
#endif