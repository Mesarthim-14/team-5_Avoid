//=====================================================================
//
//�@�Z���N�g�J�����ʏ��ԊǗ��N���X [state_camera_select.h]
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
#define DISTANCE        (30000.0f)  // ����
#define HEIGHT          (30000.0f)  // ����
#define ANGLE_POS       (15000.0f)   // ���_�̍���

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

    //    D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, PLAYER_HEIGHT, 0.0f);
    //    D3DXVECTOR3 posV = ZeroVector3;
    //    float fDistance = GAME_CAMERA_DISTANCE;
    //    float fVartical = GAME_CAMERA_DEFAULT_F��;
    //    float fHorizontal = GAME_CAMERA_DEFAULT_H��;
    //
    //    SetDistance(fDistance);
    //    SetVartical(fVartical);
    //    SetHorizontal(fHorizontal);					// �����l�G�̂ق�������
    //    GetposR() = posR;
    //    GetposU() = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������x�N�g��
    //
    //    posV.x = posR.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// �J�����ʒuX
    //    posV.y = posR.z + fDistance * cosf(fVartical);						// �J�����ʒuY
    //    posV.z = posR.y + fDistance * sinf(fVartical) * cosf(fHorizontal);	// �J�����ʒuZ
    //
    //    GetposV() = posV;

    // �J�������W
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = pCamera->GetposRDest();  // �ړI�̊p�x
    D3DXVECTOR3 pos = ZeroVector3;                  // �ʒu
    D3DXVECTOR3 rot = ZeroVector3;                  // �p�x
    rot.y += D3DXToRadian(90.0f);

    float fDistance = DISTANCE;                     // ����
    float fVartical = pCamera->GetVartical();       // �p�x
    float fHorizontal = pCamera->GetHorizontal();   // �p�x

    posRDest = D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z);    //�����_�ݒ�

    // �J�����̈ʒu�ݒ�
    VDest.x = pos.x + fDistance * sinf(fVartical) * sinf(rot.y + fHorizontal);  // �J�����ʒuX�ݒ�
    VDest.y = pos.y + ANGLE_POS * cosf(fVartical);                              // �J�����ʒuY�ݒ�
    VDest.z = pos.z + fDistance * sinf(fVartical) * cosf(rot.y + fHorizontal);  // �J�����ʒuZ�ݒ�

    //�ݒ�l�̔��f
    pCamera->GetposV() += (VDest - pCamera->GetposV());
    //    pCamera->GetposR() += (posRDest - pCamera->GetposR());

}