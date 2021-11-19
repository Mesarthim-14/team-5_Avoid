#ifndef _WIMP_ENEMY_H_
#define _WIMP_ENEMY_H_
//=============================================================================
//
// �T�� [wimp_enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CWimpEnemy : public CEnemy
{
public:
    CWimpEnemy(PRIORITY Priority = PRIORITY_CHARACTER); // �R���X�g���N�^
    ~CWimpEnemy();                                      // �f�X�g���N�^

    virtual HRESULT Init();     // ����������
    virtual void Update();      // �X�V����

protected:
    void Rush();    // �ːi
    bool Follow();  // �Ǐ]

private:
    void GravitySwitch();   // �d�͂̐؂�ւ�
    int m_nRushCount;       // ��񂾃J�E���g
    bool isRush;            // ��񂾂�true
};
#endif