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

//=========================================================================
// �O���錾
//=========================================================================
class CCollisionModelOBB;
class CPlayer;
class CCautionWimpAttack;

//=============================================================================
// �N���X��`
//=============================================================================
class CWimpEnemy : public CEnemy
{
public:
    CWimpEnemy(PRIORITY Priority = PRIORITY_CHARACTER); // �R���X�g���N�^
    ~CWimpEnemy();                                      // �f�X�g���N�^

    virtual HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot);     // ����������
    virtual void Update();      // �X�V����

protected:
    void Rush();            // �ːi
    bool Follow();          // �Ǐ]
    void Collision();       // �����蔻��
    void AffectPlayer(CPlayer* &pPlayer);    // �v���C���[�ɉe����^����

private:
    // private�֐�
    virtual void Attack() = 0;          // �U��
    void GravitySwitch();               // �d�͂̐؂�ւ�
    bool Search();                      // �v���C���[��T��

    // �����o�ϐ�
    int m_nRushCount;                   // ��񂾃J�E���g
    int m_nHitInter;                    // �����蔻��̃J�E���g
    int m_nCautionCounter;              // �x���̃J�E���g
    bool isRush;                        // ��񂾂�true
    bool m_bHit;                        // ���������t���O
    CCollisionModelOBB* m_pCollision;   // �����蔻��
    CCautionWimpAttack* m_pCaution;     // �U���x��
};
#endif