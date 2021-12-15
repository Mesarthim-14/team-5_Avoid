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
#include "model.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CSwirlScaffoldObject : public CModel
{
public:
    CSwirlScaffoldObject(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CSwirlScaffoldObject();                              // �f�X�g���N�^

    static CSwirlScaffoldObject *Create(const D3DXVECTOR3 &pos);    // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);                           // ����������
    void Update();                                                  // �X�V����

private:
};

#endif