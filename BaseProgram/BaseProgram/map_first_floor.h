#ifndef _MAP_FIRST_FLOOR_H_
#define _MAP_FIRST_FLOOR_H_
//=============================================================================
//
// �e�X�g���f���N���X [map_first_floor.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "map.h"
#include "collisionModel_OBB.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CMapFirstFloor : public CMap
{
public:

    CMapFirstFloor(PRIORITY Priority); // �R���X�g���N�^
    ~CMapFirstFloor();                 // �f�X�g���N�^

    static CMapFirstFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������

private:
    void Col();

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻��|�C���^�z��
};

#endif