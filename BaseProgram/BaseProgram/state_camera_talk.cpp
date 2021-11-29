//=====================================================================
//
//�@��b�J�����ʏ��ԊǗ��N���X [state_camera_talk.h]
//�@Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_camera_talk.h"
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
#define DISTANCE        (2000.0f)               // ����
#define HEIGHT          (500.0f)                // ����
#define SHIFT_ANGLE     (D3DXToRadian(30.0f))   // ���炷�p�x
#define ANGLE_POS       (800.0f)                // ���_�̍���

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CCameraStateTalk::CCameraStateTalk()
{
    m_pos = ZeroVector3;
    m_rot = ZeroVector3;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CCameraStateTalk::~CCameraStateTalk()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CCameraStateTalk * CCameraStateTalk::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // �������m��
    CCameraStateTalk *pState = new CCameraStateTalk;
    if (pState)
    {
        // ����������
        pState->m_pos = pos;
        pState->m_rot = rot;
        pState->Init();
        return pState;
    }

    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CCameraStateTalk::Init()
{

}

//=====================================================================
// �X�V����
//=====================================================================
void CCameraStateTalk::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    // ��C�֒Ǐ]
    TrackingTalker(pCamera);
}

//=====================================================================
// ��C�̌���
//=====================================================================
void CCameraStateTalk::TrackingTalker(CCamera* &pCamera)
{
    float fDistance = DISTANCE;
    float fVartical = pCamera->GetVartical();
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = ZeroVector3;
    float rotY = m_rot.y-D3DXToRadian(90.0f);

    // �J�����̈ʒu�ݒ�
    VDest.x = m_pos.x + fDistance * sinf(fVartical) * -sinf(rotY - SHIFT_ANGLE); // �J�����ʒuX�ݒ�
    VDest.y = m_pos.y /*+ CANNON_HEIGHT*/ + ANGLE_POS * cosf(fVartical);            // �J�����ʒuY�ݒ�
    VDest.z = m_pos.z + fDistance * sinf(fVartical) * -cosf(rotY - SHIFT_ANGLE); // �J�����ʒuZ�ݒ�

    posRDest = D3DXVECTOR3(m_pos.x, m_pos.y + HEIGHT, m_pos.z);              // �����_�ݒ�

    //�ݒ�l�̔��f
    pCamera->GetposV() += (VDest - pCamera->GetposV())*0.1f;
    pCamera->GetposR() += (posRDest - pCamera->GetposR())*0.9f;
}