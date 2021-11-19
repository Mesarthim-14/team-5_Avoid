//=====================================================================
//
//    �J�����ʏ��ԊǗ��N���X [state_camera_cannon.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_camera_cannon.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "keyboard.h"
#include "renderer.h"
#include "cannon.h"
#include "gimmick_factory.h"
#include "cannon_manager.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define DISTANCE        (3000.0f)               // ����
#define CANNON_HEIGHT   (1000.0f)               // ��C�̍���
#define SHIFT_ANGLE     (D3DXToRadian(20.0f))   // ���炷�p�x
#define ANGLE_POS       (800.0f)                // ���_�̍���

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CCameraStateCannon::CCameraStateCannon()
{

}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CCameraStateCannon::~CCameraStateCannon()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CCameraStateCannon * CCameraStateCannon::Create()
{
    // �������m��
    CCameraStateCannon *pStateNormal = new CCameraStateCannon;
    if (pStateNormal)
    {
        // ����������
        pStateNormal->Init();
        return pStateNormal;
    }

    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CCameraStateCannon::Init()
{

}

//=====================================================================
// �X�V����
//=====================================================================
void CCameraStateCannon::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    // ��C�֒Ǐ]
    TrackingCannon(pCamera);
}

//=====================================================================
// ��C�̌���
//=====================================================================
void CCameraStateCannon::TrackingCannon(CCamera* &pCamera)
{
    CCannon* pCannon = CManager::GetInstance()->GetGame()->GetGimmickFactory()->GetCannonManager()->GetCurrentCannon();
    D3DXVECTOR3 CannonPos = pCannon->GetPos();
    D3DXVECTOR3 CannonRot = pCannon->GetRot();
    float fDistance = DISTANCE;
    float fVartical = pCamera->GetVartical();
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = ZeroVector3;

    // �J�����̈ʒu�ݒ�
    VDest.x = CannonPos.x + fDistance * sinf(fVartical) * -sinf(CannonRot.y- SHIFT_ANGLE);        // �J�����ʒuX�ݒ�
    VDest.y = CannonPos.y /*+ CANNON_HEIGHT*/ + ANGLE_POS * cosf(fVartical);            // �J�����ʒuY�ݒ�
    VDest.z = CannonPos.z + fDistance * sinf(fVartical) * -cosf(CannonRot.y- SHIFT_ANGLE);        // �J�����ʒuZ�ݒ�

    posRDest = D3DXVECTOR3(CannonPos.x, CannonPos.y + CANNON_HEIGHT, CannonPos.z);    //�����_�ݒ�

    //�ݒ�l�̔��f
    pCamera->GetposV() += (VDest - pCamera->GetposV())*0.1f;
    pCamera->GetposR() += (posRDest - pCamera->GetposR())*0.9f;
}