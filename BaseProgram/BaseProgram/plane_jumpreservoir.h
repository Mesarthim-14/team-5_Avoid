#ifndef _PLANE_JUMPRESERVOIR_H_
#define _PLANE_JUMPRESERVOIR_H_
//=====================================================================
//
//    �W�����v�G�t�F�N�g����[plane_jump.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "plane.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CPlaneJumpReservoir : public CPlane
{
public:
    //==================
    // �����o�֐�
    //==================
    CPlaneJumpReservoir();
    ~CPlaneJumpReservoir();

    static CPlaneJumpReservoir * Create(const D3DXVECTOR3 &pos);
    HRESULT Init();
    void Update();
    void Uninit();
    void Draw();

private:
    //==================
    // �����o�ϐ�
    //==================
    D3DXVECTOR3 m_pos;      // ���W
    D3DXVECTOR3 m_move;     // �ړ�
    float m_fSize;          // �傫��
    float m_fRot;           // ��]
    float m_fColor;         // �J���[
    int m_nCnt;             // �J�E���g
    int m_nLife;            // ���C�t
};

#endif