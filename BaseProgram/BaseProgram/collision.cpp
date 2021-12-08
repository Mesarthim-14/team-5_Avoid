//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"
#include "collision.h"
#include "library.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBB_INTERVAL (10000.0f)    // OBB���m�̓����蔻����s���͈�

//*****************************************************************************
// �����蔻��(OBB��OBB)
//*****************************************************************************
bool CCollision::ColOBBs(const CCollisionModelOBB::OBB &obb1, const CCollisionModelOBB::OBB &obb2)
{
    // �����蔻�胂�f�����m�̋���
    D3DXVECTOR3 Interval = obb1.info.pos - obb2.info.pos;
    if (D3DXVec3Length(&Interval) > (FLOAT)OBB_INTERVAL)
    { // OBB_INTERVAL��藣��Ă���Ƃ��A�����蔻����s��Ȃ�
        return false;
    }

    // �e�����x�N�g���̊m��
    D3DXVECTOR3 Ae1 = obb1.DirVect[0];
    D3DXVECTOR3 Ae2 = obb1.DirVect[1];
    D3DXVECTOR3 Ae3 = obb1.DirVect[2];
    D3DXVECTOR3 Be1 = obb2.DirVect[0];
    D3DXVECTOR3 Be2 = obb2.DirVect[1];
    D3DXVECTOR3 Be3 = obb2.DirVect[2];

    // ���K�������e�����x�N�g���̊m��
    D3DXVECTOR3 NAe1; D3DXVec3Normalize(&NAe1, &Ae1);
    D3DXVECTOR3 NAe2; D3DXVec3Normalize(&NAe2, &Ae2);
    D3DXVECTOR3 NAe3; D3DXVec3Normalize(&NAe3, &Ae3);
    D3DXVECTOR3 NBe1; D3DXVec3Normalize(&NBe1, &Be1);
    D3DXVECTOR3 NBe2; D3DXVec3Normalize(&NBe2, &Be2);
    D3DXVECTOR3 NBe3; D3DXVec3Normalize(&NBe3, &Be3);

    // ������ : Ae1
    FLOAT rA = D3DXVec3Length(&Ae1);
    FLOAT rB = CLibrary::LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    FLOAT L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NAe1));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : Ae2
    rA = D3DXVec3Length(&Ae2);
    rB = CLibrary::LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NAe2));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : Ae3
    rA = D3DXVec3Length(&Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NAe3));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : Be1
    rA = CLibrary::LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB = D3DXVec3Length(&Be1);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NBe1));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : Be2
    rA = CLibrary::LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB = D3DXVec3Length(&Be2);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NBe2));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : Be3
    rA = CLibrary::LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    rB = D3DXVec3Length(&Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &NBe3));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : C11
    D3DXVECTOR3 Cross;
    D3DXVec3Cross(&Cross, &NAe1, &NBe1);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : C12
    D3DXVec3Cross(&Cross, &NAe1, &NBe2);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : C13
    D3DXVec3Cross(&Cross, &NAe1, &NBe3);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : C21
    D3DXVec3Cross(&Cross, &NAe2, &NBe1);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : C22
    D3DXVec3Cross(&Cross, &NAe2, &NBe2);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : C23
    D3DXVec3Cross(&Cross, &NAe2, &NBe3);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : C31
    D3DXVec3Cross(&Cross, &NAe3, &NBe1);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : C32
    D3DXVec3Cross(&Cross, &NAe3, &NBe2);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // ������ : C33
    D3DXVec3Cross(&Cross, &NAe3, &NBe3);
    rA = CLibrary::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = CLibrary::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = (FLOAT)fabs(D3DXVec3Dot(&Interval, &Cross));
    if (L > rA + rB)
    {
        return false;
    }

    // �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
    return true;
}

//=============================================================================
// �����蔻��(���̂ƃJ�v�Z��)
//=============================================================================
bool CCollision::ColSphereAndCapsule(const CCollisionModel::INFO &SphereInfo, const CCollisionModelCapsule::INFO &CapsuleInfo)
{
    // �����蔻�胂�f�����m�̋���
    D3DXVECTOR3 Interval = SphereInfo.pos - CapsuleInfo.pos;
    if (D3DXVec3Length(&Interval) > (FLOAT)OBB_INTERVAL)
    { // OBB_INTERVAL��藣��Ă���Ƃ��A�����蔻����s��Ȃ�
        return false;
    }

    D3DXVECTOR3 V1 = ZeroVector3;       // �J�v�Z�������̃x�N�g��
    D3DXVECTOR3 V2 = ZeroVector3;       // �J�v�Z�������̎n�_���狅�̂̒��S�܂ł̃x�N�g��
    D3DXVECTOR3 norV1 = ZeroVector3;    // V1�̒P�ʃx�N�g��
    FLOAT fDot = 0.0f;                  // 2�̃x�N�g���̓���

    // �J�v�Z�������̃x�N�g�����v�Z
    V1 = CapsuleInfo.P1 - CapsuleInfo.P0;

    // �P�ʃx�N�g�����v�Z
    D3DXVec3Normalize(&norV1, &V1);

    // �J�v�Z�������̎n�_���狅�̂̒��S�܂ł̃x�N�g���̌v�Z
    V2 = SphereInfo.pos - CapsuleInfo.P0;

    // 2�̃x�N�g���̓��ς��v�Z
    fDot = D3DXVec3Dot(&norV1, &V2);

    D3DXVECTOR3 ret = ZeroVector3;  // ������ŋߓ_
    FLOAT ratio = 0.0f;             // ������0�`1�͈̔͂ŕ\�����Ƃ��̐�����ŋߓ_�̈ʒu

    // ������ŋߓ_���v�Z
    ret = CapsuleInfo.P0 + D3DXVECTOR3(norV1.x * fDot, norV1.y * fDot, norV1.z * fDot);

    // ������0�`1�͈̔͂ŕ\�����Ƃ��̐�����ŋߓ_�̈ʒu���v�Z
    ratio = D3DXVec3Dot(&norV1, &(ret - CapsuleInfo.P0)) / D3DXVec3Dot(&norV1, &V1);

    if (ratio >= 0.0f && ratio <= 1.0f)
    { // ratio��0�ȏ�1�ȉ��̂Ƃ�
        // �u������ŋߓ_�Ƌ��̂̒��S�Ƃ̋����v���J�v�Z���Ƌ��̂̔��a�𑫂����l��菬�����Ƃ�
        if (D3DXVec3Length(&(SphereInfo.pos - ret)) <= (SphereInfo.size.x / 2) + (CapsuleInfo.radius / 2))
        {
             return true;
        }
    }
    else if (ratio > 1.0f)
    { // ratio��1���傫���Ƃ�
        // �u�J�v�Z�������̏I�_���狅�̂̒��S�܂ł̃x�N�g���̒����v�����̂̔��a��菬�����Ƃ�
        if (D3DXVec3Length(&(SphereInfo.pos - CapsuleInfo.P1)) <= (SphereInfo.size.x / 2))
        {
            return true;
        }
    }
    else if (ratio < 0.0f)
    { // ratio��0��菬�����Ƃ�
        // V2�̒������J�v�Z���Ƌ��̂̔��a��菬�����Ƃ�
        if (D3DXVec3Length(&(ret - CapsuleInfo.P0)) <= (SphereInfo.size.x / 2))
        {
            return true;
        }
    }

    return false;
}

//=============================================================================
// �����蔻��(���̂Ɖ~��)
//=============================================================================
void CCollision::ColSphereAndCylinder(bool &bHit, SURFACE &surface, const CCollisionModel::INFO & SphereInfo, const CCollisionModel::INFO & CylinderInfo)
{
    // �����蔻�胂�f�����m�̋���
    D3DXVECTOR3 Interval = SphereInfo.pos - CylinderInfo.pos;
    if (D3DXVec3Length(&Interval) > (FLOAT)OBB_INTERVAL)
    { // OBB_INTERVAL��藣��Ă���Ƃ��A�����蔻����s��Ȃ�
        bHit = false;
        return;
    }

    D3DXVECTOR3 P0 = ZeroVector3;       // �����̎n�_
    D3DXVECTOR3 P1 = ZeroVector3;       // �����̏I�_
    D3DXVECTOR3 V1 = ZeroVector3;       // �~�������̃x�N�g��
    D3DXVECTOR3 V2 = ZeroVector3;       // �~�������̎n�_���狅�̂̒��S�܂ł̃x�N�g��
    D3DXVECTOR3 norV1 = ZeroVector3;    // V1�̒P�ʃx�N�g��
    FLOAT fDot = 0.0f;                  // 2�̃x�N�g���̓���

    // �~�������̎n�_���W���v�Z
    P0 = D3DXVECTOR3(CylinderInfo.pos.x, CylinderInfo.pos.y + (CylinderInfo.size.z / 2), CylinderInfo.pos.z);
    //CLibrary::Rotate3D(P0, CylinderInfo.rot);

    // �~�������̏I�_���W���v�Z
    P1 = D3DXVECTOR3(CylinderInfo.pos.x, CylinderInfo.pos.y - (CylinderInfo.size.z / 2), CylinderInfo.pos.z);
    //CLibrary::Rotate3D(P1, CylinderInfo.rot);

    // �~�������̃x�N�g�����v�Z
    V1 = P1 - P0;

    // �P�ʃx�N�g�����v�Z
    D3DXVec3Normalize(&norV1, &V1);

    // �~�������̎n�_���狅�̂̒��S�܂ł̃x�N�g���̌v�Z
    V2 = SphereInfo.pos - P0;

    // 2�̃x�N�g���̓��ς��v�Z
    fDot = D3DXVec3Dot(&norV1, &V2);

    D3DXVECTOR3 ret = ZeroVector3;  // ������ŋߓ_
    FLOAT ratio = 0.0f;             // ������0�`1�͈̔͂ŕ\�����Ƃ��̐�����ŋߓ_�̈ʒu

    // ������ŋߓ_���v�Z
    ret = P0 + D3DXVECTOR3(norV1.x * fDot, norV1.y * fDot, norV1.z * fDot);

    // �u������ŋߓ_�Ƌ��̂̒��S�Ƃ̋����v���~���Ƌ��̂̔��a�𑫂����l��菬�����Ƃ�
    if (D3DXVec3Length(&(SphereInfo.pos - ret)) <= (SphereInfo.size.x / 2) + (CylinderInfo.size.x / 2))
    {
        // ������0�`1�͈̔͂ŕ\�����Ƃ��̐�����ŋߓ_�̈ʒu���v�Z
        ratio = D3DXVec3Dot(&norV1, &(ret - P0)) / D3DXVec3Dot(&norV1, &V1);

        if (ratio >= 0.0f && ratio <= 1.0f)
        { // ratio��0�ȏ�1�ȉ��̂Ƃ�
            surface = SURFACE::SURFACE_SIDE;
            bHit = true;
            return;
        }

        // �u�~�������̒��S���������ŋߓ_�܂ł̒����v���u�~�������̔����̒��� + ���̂̔��a�v��菬�����Ƃ�
        if (D3DXVec3Length(&(ret - CylinderInfo.pos)) <= (CylinderInfo.size.z / 2) + (SphereInfo.size.x / 2))
        {
            if (ratio < 0.0f)
            { // ratio��0��菬�����Ƃ�
                surface = SURFACE::SURFACE_UP;
                bHit = true;
                return;
            }
            else if (ratio > 1.0f)
            { // ratio��1���傫���Ƃ�
                surface = SURFACE::SURFACE_DOWN;
                bHit = true;
                return;
            }
        }
    }
    
    bHit = false;
    return;
}

//=============================================================================
// �����蔻��(��`�Ƌ�`)
//=============================================================================
bool CCollision::ColRectangleAndRectangle(const D3DXVECTOR3 &pos1,
    const D3DXVECTOR3 &pos2, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &size2)
{
    bool bCollision = false;

    if (pos2.x - (size2.x / 2) < pos1.x + (size1.x / 2) &&
        pos2.x + (size2.x / 2) > pos1.x - (size1.x / 2) &&
        pos2.y - (size2.y / 2) < pos1.y + (size1.y / 2) &&
        pos2.y + (size2.y / 2) > pos1.y - (size1.y / 2)    &&
        pos2.z - (size2.z / 2) < pos1.z + (size1.z / 2) &&
        pos2.z + (size2.z / 2) > pos1.z - (size1.z / 2))
    {
        bCollision = true;
    }

    return bCollision;
}

//=============================================================================
// �����蔻��(�~�`�Ɖ~�`)
//=============================================================================
bool CCollision::ColCircularAndCircular(const D3DXVECTOR3 &pos1,
    const D3DXVECTOR3 &pos2, const float &radius1, const float &radius2)
{
    bool bCollision = false;

    if (pow(pos1.x - pos2.x, 2) +
        pow(pos1.y - pos2.y, 2) +
        pow(pos1.z - pos2.z, 2) <= pow(radius1 + radius2, 2))
    {
        bCollision = true;
    }

    return bCollision;
}

//=============================================================================
// �����蔻��(��`�Ɖ~�`)
//=============================================================================
bool CCollision::ColRectangleAndCircular(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &CircularPos,
    const D3DXVECTOR3 &RectangleSize, const float &CircularRadius, const float &RectangleRadian)
{
    // ��`�̊p�x���O�ɂ������̉~�`�̍��W�����߂�
    D3DXVECTOR3 NewCircularPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    NewCircularPos.x = (float)(cos(RectangleRadian) * (CircularPos.x - RectanglePos.x) -
        sin(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.x);
    NewCircularPos.y = (float)(sin(RectangleRadian) * (CircularPos.x - RectanglePos.x) +
        cos(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.y);

    if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2) - CircularRadius) ||
        NewCircularPos.x >(RectanglePos.x + (RectangleSize.x / 2) + CircularRadius) ||
        NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2) - CircularRadius) ||
        NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2) + CircularRadius))
    { // �u��`�̊O�g + �~�̔��a�v�͈̔͂ɓ����Ă��Ȃ��Ƃ�
        return false;
    }
    if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
        NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
        !(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
            + pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
            < pow(CircularRadius, 2)))
    { // ��`�̍���̔���
        return false;
    }
    if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
        NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
        !(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
            + pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
            < pow(CircularRadius, 2)))
    { // ��`�̉E��̔���
        return false;
    }
    if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
        NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2)) &&
        !(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
            + pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
            < pow(CircularRadius, 2)))
    { // ��`�̍����̔���
        return false;
    }
    if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
        NewCircularPos.y > (RectanglePos.y + (RectangleSize.y / 2)) &&
        !(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
            + pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
            < pow(CircularRadius, 2)))
    { // ��`�̉E���̔���
        return false;
    }

    return true;
}