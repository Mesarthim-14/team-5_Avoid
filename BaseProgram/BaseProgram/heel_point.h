#ifndef _HEEL_POINT_H_
#define _HEEL_POINT_H_
//=============================================================================
//
// �񕜃|�C���g�N���X [heel_point.h]
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
class CHeelPoint : public CModel
{
public:
    CHeelPoint(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CHeelPoint();                              // �f�X�g���N�^

    static CHeelPoint *Create(const D3DXVECTOR3 &pos);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);               // ����������
    void Draw();                                        // �`�揈��
    bool Collision();                                   // �����蔻��
    D3DXVECTOR3 GetPos();                               // ���W�̎擾
private:

};

#endif