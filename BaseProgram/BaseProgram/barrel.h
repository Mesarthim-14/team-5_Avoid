#ifndef _BARREL_H_
#define _BARREL_H_
//=============================================================================
//
// �M�N���X [barrel.h]
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
class CBarrel : public CModel
{
public:
    CBarrel(PRIORITY = PRIORITY_TEST_MODEL);    // �R���X�g���N�^
    ~CBarrel();                                 // �f�X�g���N�^

    static CBarrel *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // ����������
    void Update();                                                          // �X�V����
private:
    void Rotate();

    float m_fRotateNum;
};

#endif