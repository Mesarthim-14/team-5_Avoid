#ifndef _STATE_PLAYER_NORMAL_H_
#define _STATE_PLAYER_NORMAL_H_
//=====================================================================
//
//    �ʏ��ԊǗ��N���X [state_player_normal.h]
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
class CPlayerStateNormal : public CPlayerState
{
public:
    CPlayerStateNormal();                   // �R���X�g���N�^
    ~CPlayerStateNormal();                  // �f�X�g���N�^
    static CPlayerStateNormal* Create();    // �C���X�^���X����

    void Init();            // ����������
    void Update()override;  // �X�V����

private:
    void Jump(CPlayer* &pPlayer);       // �W�����v����
    void Avoidance(CPlayer* &pPlayer);  // ���
    
};
#endif