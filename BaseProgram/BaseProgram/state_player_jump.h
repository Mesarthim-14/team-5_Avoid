#ifndef _STATE_PLAYER_JUMP_H_
#define _STATE_PLAYER_JUMP_H_
//=====================================================================
//
//    �W�����v��ԊǗ��N���X [state_player_normal.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define NOT_COLLISION_TIME (15.0f)  // �����蔻����s��Ȃ�����

//=====================================================================
// �O���錾
//=====================================================================
class CPlayer;

//=====================================================================
// �N���X��`
//=====================================================================
class CPlayerStateJump : public CPlayerState
{
public:
    CPlayerStateJump();     // �R���X�g���N�^
    ~CPlayerStateJump();    // �f�X�g���N�^

    static CPlayerStateJump* Create();  // �C���X�^���X����
    void Init();                        // ����������
    void Update()override;              // �X�V����

    float GetJumpTimeCount()const { return m_fJumpTimeCount; }  // �W�����v���ԃJ�E���g�̎擾
    bool GetJumpCheck()const { return m_bJumpCheck; }           // �W�����v���n�߂����̔���̎擾

private:
    // private�֐�
    void SubLife(CPlayer* &pPlayer);        // ���C�t�̌��Z
    void JumpProcess(CPlayer* &pPlayer);    // �W�����v���̏���
    void Avoidance(CPlayer* &pPlayer);
    void JumpEffect();

    float m_fJumpTimeCount;     // �W�����v���ԃJ�E���g
    float m_fJumpValue;         // �W�����v��
    float m_fDushJumpValue;     // �ړ��W�����v���̉��ړ����Z��
    int m_nChargeJumpCount;     // ���߃W�����v�J�E���g
    bool m_bIsReadyChargeJump;  // ���߃W�����v����������
    bool m_bJumpCheck;          // �W�����v���n�߂���
    bool m_bJumpEffect;
    int m_nCntEffect;
};
#endif