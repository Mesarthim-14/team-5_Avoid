//=============================================================================
//
// �Q�[���J�����̏��� [camera_game.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera_game.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "game.h"
#include "library.h"
#include "state_camera_normal.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GAME_CAMERA_DEFAULT_F�� (D3DXToRadian(55.0f))   // �J�����̃�Default�l
#define GAME_CAMERA_DEFAULT_H�� (D3DXToRadian(0.0f))    // �J�����p�x��
#define PLAYER_HEIGHT           (0.0f)                  // �����_�̍���
#define GAME_CAMERA_DISTANCE    (2500.0f)               // ����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCameraGame::CCameraGame()
{
    m_pCurrentState = nullptr;
    m_pNextState = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCameraGame::~CCameraGame()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCameraGame * CCameraGame::Create()
{
    // �������m��
    CCameraGame *pCamera = new CCameraGame;
    
    if (pCamera)
    {
        // ����������
        pCamera->Init();
        return pCamera;
    }
    
    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCameraGame::Init()
{
    D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, PLAYER_HEIGHT, 0.0f);
    D3DXVECTOR3 posV = ZeroVector3;
    float fDistance = GAME_CAMERA_DISTANCE;
    float fVartical = GAME_CAMERA_DEFAULT_F��;
    float fHorizontal = GAME_CAMERA_DEFAULT_H��;

    SetDistance(fDistance);
    SetVartical(fVartical);
    SetHorizontal(fHorizontal);					// �����l�G�̂ق�������
    GetposR() = posR;
    GetposU() = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������x�N�g��
    
    posV.x = posR.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// �J�����ʒuX
    posV.y = posR.z + fDistance * cosf(fVartical);						// �J�����ʒuY
    posV.z = posR.y + fDistance * sinf(fVartical) * cosf(fHorizontal);	// �J�����ʒuZ
    
    GetposV() = posV;
    
    // ����������
    CCamera::Init();
    
    if (!m_pCurrentState)
    {
    	// �C���X�^���X����
    	m_pCurrentState = CCameraStateNormal::Create();
    }
    
    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CCameraGame::Update()
{
	StateUpdate();
}

//=============================================================================
// ��ԍX�V����
//=============================================================================
void CCameraGame::StateUpdate()
{
    // ����ւ�
    if (m_pNextState)
    {
        if (m_pCurrentState)
        {
            delete m_pCurrentState;
            m_pCurrentState = nullptr;
        }
        
        m_pCurrentState = m_pNextState;
        m_pNextState = nullptr;
    }
    
    if (m_pCurrentState)
    {
        m_pCurrentState->Update();
    }
}

//=============================================================================
// ��Ԃ̕ύX
//=============================================================================
void CCameraGame::ChangeState(CState* pState)
{
    m_pNextState = pState;
}