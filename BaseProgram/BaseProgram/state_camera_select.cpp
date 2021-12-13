//=====================================================================
//
//�@�Z���N�g�J�����ʏ��ԊǗ��N���X [state_camera_select.cpp]
//�@Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_camera_select.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "keyboard.h"
#include "renderer.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define DISTANCE        (150000.0f)  // ����
#define HEIGHT          (30000.0f)      // ����
#define ANGLE_POS       (40000.0f)   // ���_�̍���

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CCameraStateSelect::CCameraStateSelect()
{

}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CCameraStateSelect::~CCameraStateSelect()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CCameraStateSelect * CCameraStateSelect::Create()
{
    // �������m��
    CCameraStateSelect *pState = new CCameraStateSelect;
    if (pState)
    {
        pState->Init();
        return pState;
    }

    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CCameraStateSelect::Init()
{

}

//=====================================================================
// �X�V����
//=====================================================================
void CCameraStateSelect::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    // �J�������W
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = pCamera->GetposRDest();  // �ړI�̊p�x
    D3DXVECTOR3 pos = ZeroVector3;                  // �ʒu
    D3DXVECTOR3 rot = ZeroVector3;                  // �p�x
    rot.y += D3DXToRadian(90.0f);

    // ��]
    float fHorizontal = pCamera->GetHorizontal();
    fHorizontal += D3DXToRadian(0.2f);
    CLibrary::RotFix(fHorizontal);
    pCamera->SetHorizontal(fHorizontal);

    float fDistance = DISTANCE;                 // ����
    float fVartical = pCamera->GetVartical();   // �p�x

    posRDest = D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z);    //�����_�ݒ�

    // �J�����̈ʒu�ݒ�
    VDest.x = pos.x + fDistance * sinf(fVartical) * sinf(rot.y + fHorizontal);  // �J�����ʒuX�ݒ�
    VDest.y = pos.y + ANGLE_POS * cosf(fVartical);                              // �J�����ʒuY�ݒ�
    VDest.z = pos.z + fDistance * sinf(fVartical) * cosf(rot.y + fHorizontal);  // �J�����ʒuZ�ݒ�

    //�ݒ�l�̔��f
    pCamera->GetposV() += (VDest - pCamera->GetposV());
}