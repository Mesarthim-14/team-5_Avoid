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
    CCollisionModelCylinder(PRIORITY = PRIORITY_COLLISION); // �R���X�g���N�^
    ~CCollisionModelCylinder();                             // �f�X�g���N�^

    static CCollisionModelCylinder *Create(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot);    // ��������

    HRESULT Init(); // ����������
    void Uninit();  // �I������
    void Update();  // �X�V����
    void Draw();    // �`�揈��
};
#endif