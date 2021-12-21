#ifndef _MAP_SQUARE_FLOOR2_H_
#define _MAP_SQUARE_FLOOR2_H_
//=============================================================================
//
// �����̂̏��N���X [map_square_floor2.h]
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
class CMapSquareFloor2 : public CMap
{
public:
    CMapSquareFloor2(PRIORITY Priority); // �R���X�g���N�^
    ~CMapSquareFloor2();                 // �f�X�g���N�^

    static CMapSquareFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������

private:
    void Col();

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻��|�C���^�z��
};

#endif