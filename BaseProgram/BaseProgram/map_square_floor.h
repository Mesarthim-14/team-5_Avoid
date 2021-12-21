#ifndef _MAP_SQUARE_FLOOR_H_
#define _MAP_SQUARE_FLOOR_H_
//=============================================================================
//
// �����̂̏��N���X [map_square_floor.h]
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
class CMapSquareFloor : public CMap
{
public:
    CMapSquareFloor(PRIORITY Priority); // �R���X�g���N�^
    ~CMapSquareFloor();                 // �f�X�g���N�^

    static CMapSquareFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������

private:
    void Col();

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻��|�C���^�z��
};

#endif