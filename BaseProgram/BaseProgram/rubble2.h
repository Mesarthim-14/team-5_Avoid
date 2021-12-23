#ifndef _RUBBLE2_H_
#define _RUBBLE2_H_
//=============================================================================
//
// ���I�N���X [rubble2.h]
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
class CRubble2 : public CModel
{
public:
    CRubble2(PRIORITY Priority);   // �R���X�g���N�^
    ~CRubble2();                                // �f�X�g���N�^

    static CRubble2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);    // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);               // ����������
    void Uninit()override;                                                      // ����������
    void Update()override;                                                      // �X�V����
    void Draw()override;                                                        // �`��

private:
};

#endif