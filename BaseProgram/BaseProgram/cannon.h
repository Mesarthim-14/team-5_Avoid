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
    CCannon(PRIORITY = PRIORITY_TEST_MODEL);    // �R���X�g���N�^
    ~CCannon();                                 // �f�X�g���N�^

    static CCannon *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // ����������
    void Update();                                                          // �X�V����
    bool Collision();                                                       // �����蔻��

    inline void SetUseFlag() { m_bUse = true; } // �g�p���Ă����Ԃɂ���

private:
    bool m_bUse;    // �g�p�������ǂ���
};

#endif