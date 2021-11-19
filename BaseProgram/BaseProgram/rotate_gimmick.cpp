//=============================================================================CRotateGimmick
//
// ��]���̃M�~�b�N�N���X [rotate_gimmick.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "rotate_gimmick.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "check_point.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "rotate_body.h"
#include "rotate_floor.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FIX_POS_Y   (150.0f)    // �����̏C��

//=============================================================================
// �C���X�^���X����
//=============================================================================
CRotateGimmick * CRotateGimmick::Create(const D3DXVECTOR3 &pos)
{
    // �������m��
    CRotateGimmick *pRotateGimmick = new CRotateGimmick;

    // !nullcheck
    if (pRotateGimmick)
    {
        // ����������
        pRotateGimmick->CreateGimmick(pos);
        return pRotateGimmick;
    }

    return nullptr;
}

//=============================================================================
// �M�~�b�N�̐���
//=============================================================================
void CRotateGimmick::CreateGimmick(const D3DXVECTOR3 &pos)
{
    CRotateFloor::Create(pos);
    CRotateBody::Create(D3DXVECTOR3(pos.x, pos.y + FIX_POS_Y, pos.z));
}