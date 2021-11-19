#ifndef _ROTATE_BODY_H_
#define _ROTATE_BODY_H_
//=============================================================================
//
// ��]�{�̃N���X [rotate_body.h]
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
class CRotateBody : public CModel
{
public:
    CRotateBody(PRIORITY = PRIORITY_TEST_MODEL);    // �R���X�g���N�^
    ~CRotateBody();                                 // �f�X�g���N�^

    static CRotateBody *Create(const D3DXVECTOR3 &pos); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);               // ����������
    void Update();                                      // �X�V����

private:
    void Rotate();          // ��]
    float m_fRotateNum;
};

#endif