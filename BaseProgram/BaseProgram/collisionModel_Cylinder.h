#ifndef _COLLISION_MODEL_CYLINDER_H_
#define _COLLISION_MODEL_CYLINDER_H_
//=============================================================================
//
// �����蔻�胂�f��(�~��)�̏��� [collisionModel_Cylinder.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "collisionModel.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCollisionModelCylinder :public CCollisionModel
{
public:
    //�~�����̍\����
    struct CYLINDER
    {
        INFO info;      // [�ʒu/�傫��/�p�x]���̍\����
        float radius;   // ���a
        float length;   // ����
    };

    CCollisionModelCylinder(PRIORITY Priority); // �R���X�g���N�^
    ~CCollisionModelCylinder();                 // �f�X�g���N�^

    static CCollisionModelCylinder *Create(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot);    // ��������

    HRESULT Init(); // ����������
    void Uninit();  // �I������
    void Update();  // �X�V����
    void Draw();    // �`�揈��

    inline CYLINDER GetCylinder()const { return{ GetInfo(), m_radius, m_length }; }   // �~�����̎擾

private:
    float m_radius;   // ���a
    float m_length;   // ����
};
#endif