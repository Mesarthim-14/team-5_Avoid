#ifndef _MAP_BIG_FLOOR2_H_
#define _MAP_BIG_FLOOR2_H_
//=============================================================================
//
// ���������I�u�W�F�N�g�N���X [map_big_floor2.h]
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
class CMapBigFloor2 : public CMap
{
public:

    CMapBigFloor2(PRIORITY Priority); // �R���X�g���N�^
    ~CMapBigFloor2();                 // �f�X�g���N�^

    static CMapBigFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������

private:
    void Col();

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻��|�C���^�z��
};

#endif