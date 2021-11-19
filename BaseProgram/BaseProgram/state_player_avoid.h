#ifndef _STATE_PLAYER_AVOID_H_
#define _STATE_PLAYER_AVOID_H_
//=====================================================================
//
//    �����ԊǗ��N���X [state_player_avoid.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CPlayerStateAvoid : public CPlayerState
{
public:
    CPlayerStateAvoid();    // �R���X�g���N�^
    ~CPlayerStateAvoid();   // �f�X�g���N�^

    static CPlayerStateAvoid* Create(); // �C���X�^���X����
    void Init();                        // ����������
    void Update()override;              // �X�V����
    void SetMove();                     // �ړ��ʂ̐ݒ�
private:
    float m_fAvoidValueY;   // ����ړ��ʁi������j
    float m_fAvoidValueXZ;  // ����ړ��ʁi�������j

};
#endif