#ifndef _STATE_PLAYER_CANNON_H_
#define _STATE_PLAYER_CANNON_H_
//=====================================================================
//
//    ��C����ԊǗ��N���X [state_player_cannon.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player.h"

//=====================================================================
// �O���錾
//=====================================================================
class CPlayer;

//=====================================================================
// �N���X��`
//=====================================================================
class CPlayerStateCannon : public CPlayerState
{
public:
    CPlayerStateCannon();   // �R���X�g���N�^
    ~CPlayerStateCannon();  // �f�X�g���N�^

    static CPlayerStateCannon* Create();    // �C���X�^���X����
    void Init();                            // ����������
    void Update()override;                  // �X�V����
    void TrackingCannon(CPlayer* &pPlayer); // ��C�̌��֒Ǐ]
private:
    int m_nStunCount;
};
#endif