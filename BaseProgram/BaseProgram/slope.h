#ifndef _SLOPE_H_
#define _SLOPE_H_
//=============================================================================
//
// �⓹�N���X [slope.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "map.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CCollisionModelOBB;
class CCollisionModelPolygon;

//=========================================================================
// �N���X��`
//=========================================================================
class CSlope : public CMap
{
public:
    CSlope(PRIORITY Priority); // �R���X�g���N�^
    ~CSlope();                 // �f�X�g���N�^

    static CSlope *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // ����������
    void Uninit();                                                          // �I������

private:
    void Col(); // �����蔻��

    CCollisionModelOBB* m_pColModelOBB;         // �����蔻�胂�f��(OBB)
    CCollisionModelPolygon* m_pColModelPolygon; //�����蔻�胂�f��(�|���S��)
};

#endif