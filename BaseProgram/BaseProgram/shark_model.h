#ifndef _SHARK_MODEL_H_
#define _SHARK_MODEL_H_
//=============================================================================
//
// �T�����f���N���X [shark_model.h]
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
class CSharkModel : public CModel
{
public:
    CSharkModel(PRIORITY = PRIORITY_TEST_MODEL);    // �R���X�g���N�^
    ~CSharkModel();                                 // �f�X�g���N�^

    static CSharkModel *Create(const D3DXVECTOR3 pos);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);               // ����������
    void Update();                                      // �X�V����
    void Draw();                                        // �`��

    void SetPos(const D3DXVECTOR3 &pos);
private:
};

#endif