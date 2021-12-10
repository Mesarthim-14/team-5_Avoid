#ifndef _NPC_ANGRY_INFO_H_
#define _NPC_ANGRY_INFO_H_
//=============================================================================
//
// �{��NPC�w�b�_  [npc_angry_info.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "non_player_character.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CNpcAngryInfo : public CNonPlayerCharacter
{
public:
    CNpcAngryInfo();    // �R���X�g���N�^
    ~CNpcAngryInfo();   // �f�X�g���N�^

    static CNpcAngryInfo* Create(); // �C���X�^���X����
    HRESULT Init()override;         // ����������
    void Uninit()override;          // �I������
    void Update()override;          // �X�V����
    void Draw()override;            // �`�揈��

private:
    void Talk();                    // ���b

};
#endif
