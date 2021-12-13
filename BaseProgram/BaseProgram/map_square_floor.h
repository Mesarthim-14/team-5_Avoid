#ifndef _MAP_SQUARE_FLOOR_H_
#define _MAP_SQUARE_FLOOR_H_
//=============================================================================
//
// �����̂̏��N���X [map_square_floor.h]
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
class CMapSquareFloor : public CModel
{
public:
    CMapSquareFloor(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CMapSquareFloor();                              // �f�X�g���N�^

    static CMapSquareFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������
    void Update()override;                                                          // �X�V����
    void Draw()override;                                                            // �`��

private:
};

#endif