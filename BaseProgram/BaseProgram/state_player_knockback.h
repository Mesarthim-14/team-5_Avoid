#ifndef _STATE_PLAYER_KNOCKBACK_H_
#define _STATE_PLAYER_KNOCKBACK_H_
//=====================================================================
//
// �W�����v��ԊǗ��N���X [state_player_knockback.h]
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
class CPlayerStateKnockback : public CPlayerState
{
public:
    CPlayerStateKnockback();    // �R���X�g���N�^
    ~CPlayerStateKnockback();   // �f�X�g���N�^

    static CPlayerStateKnockback* Create(const D3DXVECTOR3& move);  // �C���X�^���X����
    void Init();                                                    // ����������
    void Update()override;                                          // �X�V����

private:
    void SetMove(const D3DXVECTOR3& move);  // �ړ��ʐݒ�
};
#endif