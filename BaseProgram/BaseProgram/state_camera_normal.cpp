//=====================================================================
//
//    �J�����ʏ��ԊǗ��N���X [state_camera_normal.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_camera_normal.h"
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
#define INPUT_CONVERSION        (D3DXToRadian(1.0f))    // �X�e�B�b�N���͕ω���
#define PLAYER_HEIGHT           (0.0f)                  // �����_�̍���
#define CAMERA_MIN_HIGHT        (2.0f)                  // �J�����̍Œፂ�x
#define PLAYER_CAMERA_HEIGHT    (300.0f)                // �v���C���[�̍���
#define CAMERA_DISTANCE         (2000.0f)               // �v���C���[�ƃJ�����̋���

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CCameraStateNormal::CCameraStateNormal()
{
    m_bMouseCountrol = false;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CCameraStateNormal::~CCameraStateNormal()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CCameraStateNormal * CCameraStateNormal::Create()
{
    // �������m��
    CCameraStateNormal *pStateNormal = new CCameraStateNormal;
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
void CCameraStateNormal::Init()
{

}

//=====================================================================
// �X�V����
//=====================================================================
void CCameraStateNormal::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    if (m_bMouseCountrol)
    {
        // �}�E�X�̍X�V
        MouseUpdate(pCamera);
    }
    else
    {
        // �L�[�{�[�h�X�V
        KeyBoardMove(pCamera);
    }

    // ImGui
    ShowInfo();
}

//=====================================================================
// �}�E�X�̍X�V����
//=====================================================================
void CCameraStateNormal::MouseUpdate(CCamera* &pCamera)
{
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();    // �L�[�{�[�h�X�V
    D3DXVECTOR3 fRotateCenter; //�J������]�̒��S

    POINT point;
    GetCursorPos(&point);
    D3DXVECTOR3 CameraRot = pCamera->GetRot();
    if (!pKeyboard->GetPress(DIK_LCONTROL))//LCONT�����Ă���Ƃ��̓J�[�\���J������
    {
        SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);              //�}�E�X�ʒu�����Z�b�g
        CameraRot.y -= (point.x - (SCREEN_WIDTH / 2))*(0.01f*15.0f);    //�}�E�X�ʒu�𔽉f
        CameraRot.x += (point.y - (SCREEN_HEIGHT / 2))*(0.01f*15.0f);
    }

    //rot�␳
    if (CameraRot.x >= 50)
    {
        CameraRot.x = 50;
    }
    else if (CameraRot.x <= -50)
    {
        CameraRot.x = -50;
    }

    //���]���Ȃ��悤��
    if (CameraRot.y < 0)
    {
        CameraRot.y += 360;
    }
    if (CameraRot.y > 360)
    {
        CameraRot.y -= 360;
    }

    pCamera->Setrot(CameraRot);

    // �v���C���[
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer != nullptr)
    {
        //�J������]�̒��S���v���C���[�̈ʒu�ɂ���i������Ɂj
        fRotateCenter = pPlayer->GetPos() + D3DXVECTOR3(0.0f, PLAYER_CAMERA_HEIGHT, 0.0f);
    }

    D3DXVECTOR3 rot = pCamera->GetRot();
    //�J�������n�ʂ��ђʂ��Ă��܂��ꍇ�n�ʂɔ��킹��悤��
    if (fRotateCenter.y + sinf(D3DXToRadian(rot.x)) * CAMERA_DISTANCE > 0)
    {
        pCamera->SetposV(fRotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-rot.y)) * cosf(D3DXToRadian(rot.x)) * CAMERA_DISTANCE, sinf(D3DXToRadian(rot.x)) * CAMERA_DISTANCE, cosf(D3DXToRadian(-rot.y)) * cosf(D3DXToRadian(rot.x)) * CAMERA_DISTANCE));
    }
    else
    {
        pCamera->SetposV(fRotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-rot.y)) * cosf(D3DXToRadian(rot.x))* CAMERA_DISTANCE, -fRotateCenter.y + 1, cosf(D3DXToRadian(-rot.y)) * cosf(D3DXToRadian(rot.x))* CAMERA_DISTANCE));
    }

    //�����_�𒆐S�ɂ��킹��
    pCamera->SetposR(fRotateCenter);
}

//=====================================================================
// �L�[�{�[�h����
//=====================================================================
void CCameraStateNormal::KeyBoardMove(CCamera* &pCamera)
{
    // �v���C���[
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    D3DXVECTOR3 PlayerPos = pPlayer->GetPos();    //�v���C���[�ʒu
    D3DXVECTOR3 PlayerRot = pPlayer->GetRot();    //�v���C���[�ʒu

    // �J�������W
    float fDistance = pCamera->GetDistance();
    float fVartical = pCamera->GetVartical();
    float fHorizontal = pCamera->GetHorizontal();                            // �J�����̊p�x
    //�L�[�{�[�h�N���X���̎擾
    CInputKeyboard *pKeyInput = CManager::GetInstance()->GetKeyboard();
    D3DXVECTOR3 VDest = ZeroVector3;

    //���_�i�J�������W�j�̍�����
    if (pKeyInput->GetPress(DIK_LEFT))
    {
        fHorizontal += INPUT_CONVERSION;
    }
    //���_�i�J�������W�j�̉E����
    if (pKeyInput->GetPress(DIK_RIGHT))
    {
        fHorizontal -= INPUT_CONVERSION;
    }
    //���_�i�J�������W�j�̏����
    if (pKeyInput->GetPress(DIK_UP))
    {
        fVartical -= INPUT_CONVERSION;
    }
    //���_�i�J�������W�j�̉�����
    if (pKeyInput->GetPress(DIK_DOWN))
    {
        fVartical += INPUT_CONVERSION;
    }

    // �p�x�̏C��
    CLibrary::RotFix(fHorizontal);

    // �p�x�̐ݒ�
    pCamera->SetVartical(fVartical);
    pCamera->SetHorizontal(fHorizontal);

    // �J�����̈ʒu�ݒ�
    VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(fHorizontal);    // �J�����ʒuX�ݒ�
    VDest.y = PlayerPos.y + fDistance * cosf(fVartical);                        // �J�����ʒuY�ݒ�
    VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(fHorizontal);    // �J�����ʒuZ�ݒ�

    D3DXVECTOR3 posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);    //�����_�ݒ�

    //�J����POSY�̉���
    if (VDest.y <= CAMERA_MIN_HIGHT)
    {
        VDest.y = CAMERA_MIN_HIGHT;    //���E�l�ɖ߂�
    }

    //�ݒ�l�̔��f
    pCamera->GetposV() += (VDest - pCamera->GetposV())*0.1f;
    pCamera->GetposR() += (posRDest - pCamera->GetposR())*0.9f;
}

//=====================================================================
// Imgui���
//=====================================================================
void CCameraStateNormal::ShowInfo()
{
    ImGui::Begin("DebugInfo");

    if (ImGui::CollapsingHeader("CameraState"))
    {
    //    if (ImGui::TreeNode("Camera"))
        {
            ImGui::Checkbox("isMouseControl", &m_bMouseCountrol);
        //    ImGui::TreePop();
        }
    }
    ImGui::End();
}