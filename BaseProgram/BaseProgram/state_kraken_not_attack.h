#ifndef _STATE_KRAKEN_NOT_ATTACK_H_
#define _STATE_KRAKEN_NOT_ATTACK_H_
//=====================================================================
//
// �U�����Ȃ���ԊǗ��N���X [state_kraken_not_attack.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_kraken.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CKrakenStateNotAttack : public CKrakenState
{
public:
    CKrakenStateNotAttack();    // �R���X�g���N�^
    ~CKrakenStateNotAttack();   // �f�X�g���N�^

    static CKrakenStateNotAttack* Create(); // �C���X�^���X����
    void Init();                            // ����������
    void Update()override;                  // �X�V����

private:
};
#endif