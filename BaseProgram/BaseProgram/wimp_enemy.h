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
    void GravitySwitch();               // �d�͂̐؂�ւ�
    int m_nRushCount;                   // ��񂾃J�E���g
    bool isRush;                        // ��񂾂�true
    CCollisionModelOBB* m_pCollision;   // �����蔻��
    bool m_bHit;                        // ���������t���O
    int m_nHitInter;                    // �����蔻��̃J�E���g
};
#endif