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
#include "map.h"
#include "collisionModel_OBB.h"

//=========================================================================
// �}�N����`
//=========================================================================
#define COL_NUM (3)

//=========================================================================
// �N���X��`
//=========================================================================
class CRotateFloor : public CMap
{
public:
    CRotateFloor(PRIORITY Priority);   // �R���X�g���N�^
    ~CRotateFloor() {}                              // �f�X�g���N�^

    static CRotateFloor *Create(const D3DXVECTOR3 &pos);    // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);                   // ����������
    void Uninit();                                          // �I������
    void Update();                                          // �X�V����

private:
    void Col(); // �����蔻��

    CCollisionModelOBB* m_pColModelOBB[COL_NUM][CCollisionModelOBB::SURFACE_MAX];    // �����蔻��|�C���^�z��
};

#endif
