#ifndef _PRODUCTION_ANGRY_KRAKEN_H_
#define _PRODUCTION_ANGRY_KRAKEN_H_
//=======================================================================================
//
// �N���[�P�����{�鉉�o�N���X [production_angry_kraken.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "production.h"

//=======================================================================================
// �N���X��`
//=======================================================================================
class CProductionAngryKraken : public CProduction
{
public:
    CProductionAngryKraken();    // �R���X�g���N�^
    ~CProductionAngryKraken();   // �f�X�g���N�^

    static CProductionAngryKraken* Create();    // �C���X�^���X����
    void Init();                                // ����������
    void Uninit();                              // �I������
    void Update();                              // �X�V����

private:
};
#endif