#ifndef _NPC_ENEMY_INFO_H_
#define _NPC_ENEMY_INFO_H_
//=============================================================================
//
// �G�̏��������Ă�NPC�w�b�_  [npc_enemy_info.h]
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
class CNpcEnemyInfo : public CNonPlayerCharacter
{
public:
    CNpcEnemyInfo();    // �R���X�g���N�^
    ~CNpcEnemyInfo();   // �f�X�g���N�^

    static CNpcEnemyInfo* Create(); // �C���X�^���X����
    HRESULT Init()override;         // ����������
    void Uninit()override;          // �I������
    void Update()override;          // �X�V����
    void Draw()override;            // �`�揈��

private:

};
#endif
