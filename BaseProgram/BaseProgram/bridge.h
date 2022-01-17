#ifndef _BRIDGE_H_
#define _BRIDGE_H_
//=============================================================================
//
// ���N���X [bridge.h]
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
class CBridge : public CMap
{
public:
    CBridge(PRIORITY Priority);    // �R���X�g���N�^
    ~CBridge();                    // �f�X�g���N�^

    static CBridge *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // ����������
    void Uninit();                                                          // �I������
    void Update();                                                          // �X�V����

private:
    void Col(); // �����蔻��

    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻��|�C���^�z��
};

#endif