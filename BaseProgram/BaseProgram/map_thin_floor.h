#ifndef _MAP_THIN_FLOOR_H_
#define _MAP_THIN_FLOOR_H_
//=============================================================================
//
// �����`�̏��N���X [map_thin_floor.h]
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
class CMapThinFloor : public CMap
{
public:
    CMapThinFloor(PRIORITY Priority); // �R���X�g���N�^
    ~CMapThinFloor();                 // �f�X�g���N�^

    static CMapThinFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������

private:
    void Col();

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻��|�C���^�z��
};

#endif