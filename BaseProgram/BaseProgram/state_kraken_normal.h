#ifndef _STATE_KRAKEN_NORMAL_H_
#define _STATE_KRAKEN_NORMAL_H_
//=====================================================================
//
// �N���[�P����ԊǗ��N���X [state_kraken_normal.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_kraken.h"

//=====================================================================
// �O���錾
//=====================================================================
class CKraken;

//=====================================================================
// �N���X��`
//=====================================================================
class CKrakenStateNormal : public CKrakenState
{
public:
    CKrakenStateNormal();                   // �R���X�g���N�^
    ~CKrakenStateNormal();                  // �f�X�g���N�^
    static CKrakenStateNormal* Create();    // �C���X�^���X����

    void Init();            // ����������
    void Update()override;  // �X�V����

private:
    // private�֐�
    void ShotBullet(CKraken* &pKraken);  // �e����

    // �����o�ϐ�
    int m_nBulletCount;
};
#endif