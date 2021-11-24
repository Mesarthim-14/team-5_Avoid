#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// �G�N���X�w�b�_�[ [enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CEnemy : public CCharacter
{
public:
    CEnemy(PRIORITY Priority = PRIORITY_CHARACTER); // �R���X�g���N�^
    virtual ~CEnemy();                              // �f�X�g���N�^

    virtual HRESULT Init(); // ����������
    virtual void Update();  // �X�V����

protected:
    void SetAttackInfo(const int &nInter, 
        const int &nSTR, const float &fPower);  // �U���̏��ݒ�
private:
    // private�֐�
    virtual void Move();            // �ړ�����
    virtual void UpdateState();     // �L�����N�^�[���
    virtual void CreateModel() = 0; // ���f�������֐�
    virtual void Attack() = 0;      // �U��

    int m_nAttackInter; // �U���̊Ԋu
    int m_nAttackCount; // �U���̃J�E���^�[
    int m_nSTR;         // �U����
    float m_fPower;     // ������΂���
};
#endif