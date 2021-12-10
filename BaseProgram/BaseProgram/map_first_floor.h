#ifndef _MAP_FIRST_FLOOR_H_
#define _MAP_FIRST_FLOOR_H_
//=============================================================================
//
// �e�X�g���f���N���X [map_first_floor.h]
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
class CMapFirstFloor : public CModel
{
public:

    CMapFirstFloor(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CMapFirstFloor();                              // �f�X�g���N�^

    static CMapFirstFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������
    void Update()override;                                                          // �X�V����
    void Draw()override;                                                            // �`��
    void OBBs();                                                                    // OBB�Փ˔���

private:
};

#endif