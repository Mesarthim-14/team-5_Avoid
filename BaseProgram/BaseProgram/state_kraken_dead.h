#ifndef _STATE_KRAKEN_DEAD_H_
#define _STATE_KRAKEN_DEAD_H_
//=====================================================================
//
// ���S��ԃN���X [state_kraken_dead.h]
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
class CKrakenStateDead : public CKrakenState
{
public:
    CKrakenStateDead();   // �R���X�g���N�^
    ~CKrakenStateDead();  // �f�X�g���N�^

    static CKrakenStateDead* Create();    // �C���X�^���X����
    void Init();                            // ����������
    void Update()override;                  // �X�V����

private:
};
#endif