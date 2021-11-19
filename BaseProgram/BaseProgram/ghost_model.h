#ifndef _GHOST_MODEL_H_
#define _GHOST_MODEL_H_
//=============================================================================
//
// �H�샂�f���N���X [ghost_model.h]
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
class CGhostModel : public CModel
{
public:
    CGhostModel(PRIORITY = PRIORITY_TEST_MODEL);    // �R���X�g���N�^
    ~CGhostModel();                                 // �f�X�g���N�^

    static CGhostModel *Create(const D3DXVECTOR3 pos);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos);               // ����������
    void Draw();                                        // �`��

    void SetPos(const D3DXVECTOR3 &pos);
private:
};

#endif