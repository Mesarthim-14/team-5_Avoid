#ifndef _RUBBLE1_H_
#define _RUBBLE1_H_
//=============================================================================
//
// ���I�N���X [rubble1.h]
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
class CRubble1 : public CModel
{
public:
    CRubble1(PRIORITY = PRIORITY_MAP);   // �R���X�g���N�^
    ~CRubble1();                                // �f�X�g���N�^

    static CRubble1 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);    // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);               // ����������
    void Uninit()override;                                                      // ����������
    void Update()override;                                                      // �X�V����
    void Draw()override;                                                        // �`��

private:
};

#endif