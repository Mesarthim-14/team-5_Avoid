#ifndef _MAP_CHECK_FLOOR_H_
#define _MAP_CHECK_FLOOR_H_
//=============================================================================
//
// �`�F�b�N�|�C���g�̃I�u�W�F [map_check_floor.h]
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
class CMapCheckFloor : public CModel
{
public:
    CMapCheckFloor(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CMapCheckFloor();                              // �f�X�g���N�^

    static CMapCheckFloor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                   // ����������
    void Uninit()override;                                                          // ����������
    void Update()override;                                                          // �X�V����
    void Draw()override;                                                            // �`��

private:
};

#endif