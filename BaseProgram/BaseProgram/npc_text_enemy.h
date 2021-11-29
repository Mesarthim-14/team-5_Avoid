#ifndef _NPC_TEXT_ENEMY_H_
#define _NPC_TEXT_ENEMY_H_
//=============================================================================
//
// NPC�̃G�l�~�[�e�L�X�g [npc_text_enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "npc_text.h"

//=============================================================================
// �O���錾
//=============================================================================
class CBillboard;

//=============================================================================
// �N���X��`
//=============================================================================
class CNpcTextEnemy : public CNpcText
{
public:
    CNpcTextEnemy();    // �R���X�g���N�^
    ~CNpcTextEnemy();   // �f�X�g���N�^

    static CNpcTextEnemy* Create(); // �C���X�^���X����
    HRESULT Init();                 // ����������
    void Uninit();                  // �I������
    void Update();                  // �X�V����

    inline bool GetEnd() { return m_bEnd; }

private:
    void CreateSentence1();     // ���͂̐���
    void CreateSentence2();     // ���͂̐���

    typedef void(CNpcTextEnemy::*SENTENCE_FUNC)();
    vector<SENTENCE_FUNC> m_CreateSentence =
    { &CNpcTextEnemy::CreateSentence1 ,
        &CNpcTextEnemy::CreateSentence2 };

    int m_nCounter;         // �J�E���^�[
    bool m_bEnd;
    CBillboard* m_pSentence;
};
#endif
