#ifndef _MAP_H_
#define _MAP_H_
//=============================================================================
//
// �}�b�v�e�N���X [map.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"
#include "collisionModel_OBB.h"
#include "collisionModel_Sphere.h"
#include "collisionModel_Cylinder.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CMap : public CModel
{
public:
    CMap(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CMap();                              // �f�X�g���N�^

    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);   // ����������
    void Uninit()override;                                          // ����������
    void Update()override;                                          // �X�V����
    void Draw()override;                                            // �`��

    // �����蔻��
    void HitColOBBs(CCollisionModelOBB** pMapColOBB);                         // �}�b�v�̓����蔻��֐�(�����̓��m)
    void HitColSphereAndCylinder(CCollisionModelCylinder* pMapColCylinder);   // �}�b�v�̓����蔻��֐�(���̂Ɖ~��)

private:
    bool m_bHitOld; // �P�ȏ�}�b�v�ɓ������Ă��邩�̔���
};

#endif