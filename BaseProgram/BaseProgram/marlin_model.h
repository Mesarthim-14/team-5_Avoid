#ifndef _MARLIN_MODEL_H_
#define _MARLIN_MODEL_H_
//=============================================================================
//
// �J�W�L���f���N���X [marlin_model.h]
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
class CMarlinModel : public CModel
{
public:
    CMarlinModel(PRIORITY = PRIORITY_TEST_MODEL);   // �R���X�g���N�^
    ~CMarlinModel();                                // �f�X�g���N�^

    static CMarlinModel *Create(const D3DXVECTOR3 pos); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);               // ����������
    void Draw();                                        // �`��

    void SetPos(const D3DXVECTOR3 &pos);
private:
};

#endif