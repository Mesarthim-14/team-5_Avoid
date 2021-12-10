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
#include "model.h"

//=========================================================================
// �O���錾
//=========================================================================
class CCollisionModelOBB;

//=========================================================================
// �N���X��`
//=========================================================================
class CBridge : public CModel
{
public:
    CBridge(PRIORITY = PRIORITY_TEST_MODEL);    // �R���X�g���N�^
    ~CBridge();                                 // �f�X�g���N�^

    static CBridge *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // ����������
    void Update();                                                          // �X�V����

    void HitOBBs(); // OBB���m�̓����蔻��

private:
    CCollisionModelOBB* m_pColModelOBB; // �����蔻��|�C���^
};

#endif