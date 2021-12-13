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
#include "model.h"
#include "collisionModel_OBB.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CMapThinFloor : public CModel
{
public:
    CMapThinFloor(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CMapThinFloor();                              // �f�X�g���N�^

    static CMapThinFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������
    void Update()override;                                                          // �X�V����
    void Draw()override;                                                            // �`��

    void HitCol();  // �����蔻��

private:
    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻��|�C���^�z��
};

#endif