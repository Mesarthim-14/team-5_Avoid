#ifndef _SWIRL_SCAFFOLD_OBJECT_H_
#define _SWIRL_SCAFFOLD_OBJECT_H_
//=============================================================================
//
// �Q�̑���N���X [swirl_scaffold.h]
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
class CSwirlScaffoldObject : public CMap
{
public:
    CSwirlScaffoldObject(PRIORITY Priority); // �R���X�g���N�^
    ~CSwirlScaffoldObject();                 // �f�X�g���N�^

    static CSwirlScaffoldObject *Create(const D3DXVECTOR3 &pos);    // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);                           // ����������
    void Uninit();                                                  // �I������
    void Update();                                                  // �X�V����

private:
    void Col(); // �����蔻��

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻��|�C���^�z��
};

#endif