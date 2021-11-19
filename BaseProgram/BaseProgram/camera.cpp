//=============================================================================
//
// �J�����̏��� [camera.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "motion.h"
#include "library.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
    //�e�����o�ϐ��̃N���A
    m_posV = ZeroVector3;
    m_posVDest = ZeroVector3;
    m_posR = ZeroVector3;
    m_posRDest = ZeroVector3;
    m_posU = ZeroVector3;
    m_rot = ZeroVector3;
    m_fDistance = 0.0f;
    m_fMove = 0.0f;
    m_fHorizontal = 0.0f;
    m_fVartical = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init()
{

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit()
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update()
{

}

//=============================================================================
//�J�����N���X�̃Z�b�g����
//=============================================================================
void CCamera::SetCamera()
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //�r���[�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxView);

    //�r���[�}�g���b�N�X�̍쐬
    D3DXMatrixLookAtLH(&m_mtxView,
        &m_posV,
        &m_posR,
        &m_posU);

    //�r���[�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

    //�v���W�F�N�V�����}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxProjection);

    //�v���W�F�N�V�����}�g���b�N�X�̍쐬
    D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
        D3DXToRadian(45.0f),
        (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
        10.0f,
        500000.0f);

    //�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_PROJECTION,
        &m_mtxProjection);
}

//=============================================================================
// imgui�̐ݒ�
//=============================================================================
void CCamera::ShowInfo()
{
    ImGui::Begin("DebugInfo");

    if (ImGui::CollapsingHeader("CameraInfo"))
    {
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
        
        if (ImGui::TreeNode("Camera"))
        {
            ImGui::SliderFloat("Horizontal", &m_fHorizontal, D3DXToRadian(-180), D3DXToRadian(180));
            ImGui::TreePop();
        }
    }

    ImGui::End();
}