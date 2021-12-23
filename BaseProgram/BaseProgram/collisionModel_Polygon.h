#ifndef _COLLISION_MODEL_POLYGON_H_
#define _COLLISION_MODEL_POLYGON_H_
//=============================================================================
//
// �����蔻�胂�f��(�|���S��)�̏��� [collisionModel_Polygon.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "collisionModel.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCollisionModelPolygon :public CCollisionModel
{
public:
    // �|���S�����̍\����
    struct POLYGON
    {
        INFO info;                          // ��{���
        D3DXVECTOR3 norVec;                 // �@���x�N�g��
        D3DXVECTOR3 DirVect[AXIS_NUM_OBB];  // �����x�N�g��
    };

    CCollisionModelPolygon(PRIORITY Priority); // �R���X�g���N�^
    ~CCollisionModelPolygon();                 // �f�X�g���N�^

    static CCollisionModelPolygon *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR2 &size, const D3DXVECTOR3 &rot);    // ��������

    HRESULT Init(); // ����������
    void Uninit();  // �I������
    void Update();  // �X�V����
    void Draw();    // �`�揈��

    inline POLYGON GetPolygon()const { return{ GetInfo(), m_norVec,{ m_DirVect[0], m_DirVect[1], m_DirVect[2] } }; }   // �|���S�����̎擾

private:
    D3DXVECTOR3 m_norVec;                   // �@���x�N�g��
    D3DXVECTOR3 m_DirVect[AXIS_NUM_OBB];    // �����x�N�g��
};
#endif