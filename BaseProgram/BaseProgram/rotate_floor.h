#ifndef _ROTATE_FLOOR_H_
#define _ROTATE_FLOOR_H_
//=============================================================================
//
// ��]���N���X [rotate_floor.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �O���錾
//=========================================================================
class CCollisionModelCylinder;

//=========================================================================
// �N���X��`
//=========================================================================
class CRotateFloor : public CModel
{
public:
    CRotateFloor(PRIORITY = PRIORITY_TEST_MODEL);   // �R���X�g���N�^
    ~CRotateFloor() {}                              // �f�X�g���N�^

    static CRotateFloor *Create(const D3DXVECTOR3 &pos);    // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);                   // ����������
    void Update();                                          // �X�V����

    void HitCylinderAndSphere(); // �~���Ƌ��̂̓����蔻��

private:
    CCollisionModelCylinder* m_pColModelCylinder;   // �����蔻��|�C���^(�~��)
};

#endif
