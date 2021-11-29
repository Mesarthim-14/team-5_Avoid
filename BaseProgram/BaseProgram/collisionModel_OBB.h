#ifndef _COLLISION_MODEL_OBB_H_
#define _COLLISION_MODEL_OBB_H_
//=============================================================================
//
// �����蔻�胂�f��(������)�̏��� [collisionModel_OBB.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "collisionModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define AXIS_NUM_OBB (3) //OBB�̎���

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCollisionModelOBB :public CCollisionModel
{
public:
    //OBB���̍\����
    struct OBB
    {
        INFO info;
        D3DXVECTOR3 DirVect[AXIS_NUM_OBB];  // �����x�N�g��
    };

    CCollisionModelOBB(PRIORITY = PRIORITY_COLLISION); // �R���X�g���N�^
    ~CCollisionModelOBB();                             // �f�X�g���N�^

    static CCollisionModelOBB *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot);    // ��������

    HRESULT Init(); // ����������
    void Uninit();  // �I������
    void Update();  // �X�V����
    void Draw();    // �`�揈��

    OBB GetOBB()const { return{ GetInfo(), {m_DirVect[0], m_DirVect[1], m_DirVect[2] } }; }    // OBB�̎擾

private:
    D3DXVECTOR3 m_DirVect[AXIS_NUM_OBB];  // �����x�N�g��
};
#endif