#ifndef _STATE_PLAYER_STUN_H_
#define _STATE_PLAYER_STUN_H_
//=====================================================================
//
// �W�����v��ԊǗ��N���X [state_player_stun.h]
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
class CPlayerStateStun : public CPlayerState
{
public:
    CPlayerStateStun();     // �R���X�g���N�^
    ~CPlayerStateStun();    // �f�X�g���N�^

    static CPlayerStateStun* Create();  // �C���X�^���X����
    void Init();                        // ����������
    void Update()override;              // �X�V����

private:
    int m_nStunCount;
};
#endif