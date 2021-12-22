#ifndef _CANNON_H_
#define _CANNON_H_
//=============================================================================
//
// ��C�N���X [cannon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CCannon : public CModel
{
public:
    CCannon(PRIORITY Priority); // �R���X�g���N�^
    ~CCannon();                 // �f�X�g���N�^

    static CCannon *Create(const D3DXVECTOR3 &pos); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);           // ����������
    void Update();                                  // �X�V����
    bool Collision();                               // �����蔻��

    inline void SetUseFlag() { m_bUse = true; } // �g�p���Ă����Ԃɂ���

private:
    // private�֐�
    D3DXVECTOR3 LookAtKraken(const D3DXVECTOR3 &pos);

    // �����o�Εϐ�
    bool m_bUse;    // �g�p�������ǂ���
};

#endif