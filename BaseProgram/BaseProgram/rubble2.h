#ifndef _RUBBLE2_H_
#define _RUBBLE2_H_
//=============================================================================
//
// ���I�N���X [rubble2.h]
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
#define COL_POLYGON_NUM (4)

//=========================================================================
// �O���錾
//=========================================================================
class CCollisionModelPolygon;

//=========================================================================
// �N���X��`
//=========================================================================
class CRubble2 : public CMap
{
public:
    CRubble2(PRIORITY Priority);   // �R���X�g���N�^
    ~CRubble2();                                // �f�X�g���N�^

    static CRubble2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);    // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);               // ����������
    void Uninit()override;                                                      // ����������
    void Update()override;                                                      // �X�V����
    void Draw()override;                                                        // �`��

private:
    void Col(); // �����蔻��

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻�胂�f���|�C���^(OBB)
    CCollisionModelPolygon* m_pColModelPolygon[COL_POLYGON_NUM];            // �����蔻�胂�f���|�C���^(�|���S��)
};

#endif