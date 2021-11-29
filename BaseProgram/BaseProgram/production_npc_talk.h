#ifndef _PRODUCTION_NPC_TALK_H_
#define _PRODUCTION_NPC_TALK_H_
//=======================================================================================
//
// ��b�̉��o�N���X [production_npc_talk.h]
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
class CProductionNpcTalk : public CProduction
{
public:
    CProductionNpcTalk();    // �R���X�g���N�^
    ~CProductionNpcTalk();   // �f�X�g���N�^

    static CProductionNpcTalk* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                          // ����������
    void Uninit()override;                                                              // �I������
    void Update()override;                                                              // �X�V����

private:
};
#endif