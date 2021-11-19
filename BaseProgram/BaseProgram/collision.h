#ifndef _COLLISION_H_
#define _COLLISION_H_
//=============================================================================
//
// �����蔻�菈�� [collision.h]
// Author : Suzuki Mahiro
//
//=============================================================================
//(^_-)-��
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "model.h"
#include "collisionModel.h"

//=============================================================================
// �����蔻��N���X
//=============================================================================
class CCollision
{
public:
    // ����������
    enum SURFACE
    {
        SURFACE_DOWN = 1,
        SURFACE_UP,
        SURFACE_LEFT,
        SURFACE_RIGHT,
        SURFACE_PREVIOUS,
        SURFACE_BACK
    };

    //OBB��OBB�̏Փ˔���
    static bool ColOBBs(const CCollisionModel::OBB &obb1, const CCollisionModel::OBB &obb2);
    //�����蔻��(��`�Ƌ�`)
    static bool CollisionRectangleAndRectangle(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &size2);
    //�����蔻��(�~�`�Ɖ~�`)
    static bool CollisionCircularAndCircular(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2, const float &radius1, const float &radius2);
    //�����蔻��(��`�Ɖ~�`)
    static bool CollisionRectangleAndCircular(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &CircularPos, const D3DXVECTOR3 &RectangleSize, const float &CircularRadius, const float &RectangleRadian);
};

#endif