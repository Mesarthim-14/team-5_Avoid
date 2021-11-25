#ifndef _COLLISION_MODEL_SPHERE_H_
#define _COLLISION_MODEL_SPHERE_H_
//=============================================================================
//
// �����蔻�胂�f��(����)�̏��� [collisionModel_Sphere.h]
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
class CCollisionModelSphere :public CCollisionModel
{
public:
    CCollisionModelSphere(PRIORITY = PRIORITY_COLLISION); // �R���X�g���N�^
    ~CCollisionModelSphere();                             // �f�X�g���N�^

    static CCollisionModelSphere *Create(const D3DXVECTOR3 &pos, const float &radius, const D3DXVECTOR3 &rot);    // ��������

    HRESULT Init(); // ����������
    void Uninit();  // �I������
    void Update();  // �X�V����
    void Draw();    // �`�揈��
};
#endif