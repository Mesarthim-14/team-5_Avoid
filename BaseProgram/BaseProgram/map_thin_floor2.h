#ifndef _MAP_THIN_FLOOR2_H_
#define _MAP_THIN_FLOOR2_H_
//=============================================================================
//
// �����`�̏��N���X [map_thin_floor2.h]
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
class CMapThinFloor2 : public CModel
{
public:
    CMapThinFloor2(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CMapThinFloor2();                              // �f�X�g���N�^

    static CMapThinFloor2 *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������
    void Update()override;                                                          // �X�V����
    void Draw()override;                                                            // �`��

private:
};

#endif