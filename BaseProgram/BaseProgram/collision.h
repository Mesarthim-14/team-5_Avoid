#ifndef _COLLISION_H_
#define _COLLISION_H_
//=============================================================================
//
// �����蔻�菈�� [collision.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "model.h"
#include "collisionModel_OBB.h"
#include "collisionModel_Capsule.h"

//=============================================================================
// �����蔻��N���X
//=============================================================================
class CCollision
{
public:
    // ���������ʂ̗񋓌^
    enum SURFACE
    {
        SURFACE_NONE = -1,
        SURFACE_UP,         // ���
        SURFACE_DOWN,       // ����
        SURFACE_SIDE        // ����
    };

    // �����蔻��(OBB��OBB)
    static bool ColOBBs(const CCollisionModelOBB::OBB &obb1, const CCollisionModelOBB::OBB &obb2);
    // �����蔻��(���̂ƃJ�v�Z��)
    static bool ColSphereAndCapsule(const CCollisionModel::INFO &SphereInfo, const CCollisionModelCapsule::INFO &CapsuleInfo);
    // �����蔻��(���̂Ɖ~��)
    static void ColSphereAndCylinder(bool &bHit, SURFACE &surface, const CCollisionModel::INFO &SphereInfo, const CCollisionModel::INFO &CylinderInfo);
    // �����蔻��(��`�Ƌ�`)
    static bool ColRectangleAndRectangle(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &size2);
    // �����蔻��(�~�`�Ɖ~�`)
    static bool ColCircularAndCircular(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2, const float &radius1, const float &radius2);
    // �����蔻��(��`�Ɖ~�`)
    static bool ColRectangleAndCircular(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &CircularPos, const D3DXVECTOR3 &RectangleSize, const float &CircularRadius, const float &RectangleRadian);
};

#endif