#ifndef _STATE_KRAKEN_ANGRY_H_
#define _STATE_KRAKEN_ANGRY_H_
//=====================================================================
//
// �{���ԃN���X [state_kraken_angry.h]
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
class CKrakenStateAngry : public CKrakenState
{
public:
    CKrakenStateAngry();   // �R���X�g���N�^
    ~CKrakenStateAngry();  // �f�X�g���N�^

    static CKrakenStateAngry* Create();    // �C���X�^���X����
    void Init();                            // ����������
    void Update()override;                  // �X�V����

private:
};
#endif