#ifndef _SWIRL_SCAFFOLD_H_
#define _SWIRL_SCAFFOLD_H_
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
class CSwirlScaffold : public CModel
{
public:
    CSwirlScaffold(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CSwirlScaffold();                              // �f�X�g���N�^

    static CSwirlScaffold *Create(const D3DXVECTOR3 &pos);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);                   // ����������
    void Update();                                          // �X�V����

private:
    void Rotate();  // ��]
    float m_fRotateNum;
};

#endif