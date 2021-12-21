#ifndef _MAP_CHECK_FLOOR2_H_
#define _MAP_CHECK_FLOOR2_H_
//=============================================================================
//
// �`�F�b�N�|�C���g�̃I�u�W�F [map_check_floor2.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "map.h"

//=========================================================================
// �O���錾
//=========================================================================
class CCollisionModelCylinder;

//=========================================================================
// �N���X��`
//=========================================================================
class CMapCheckFloor2 : public CMap
{
public:
    CMapCheckFloor2(PRIORITY Priority); // �R���X�g���N�^
    ~CMapCheckFloor2();                 // �f�X�g���N�^

    static CMapCheckFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������

private:
    void Col();

    CCollisionModelCylinder* m_pColModelCylinder;   // �����蔻��|�C���^
};

#endif