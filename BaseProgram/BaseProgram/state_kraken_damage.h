#ifndef _STATE_KRAKEN_DAMAGE_H_
#define _STATE_KRAKEN_DAMAGE_H_
//=====================================================================
//
// �_���[�W��ԃN���X [state_kraken_damage.h]
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
class CKrakenStateDamage : public CKrakenState
{
public:
    CKrakenStateDamage();   // �R���X�g���N�^
    ~CKrakenStateDamage();  // �f�X�g���N�^

    static CKrakenStateDamage* Create();    // �C���X�^���X����
    void Init();                            // ����������
    void Update()override;                  // �X�V����

private:
};
#endif