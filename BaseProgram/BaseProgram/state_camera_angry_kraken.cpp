//=====================================================================
//
// �N���[�P���{�艉�o�J���� [state_camera_angry_kraken.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_camera_angry_kraken.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "keyboard.h"
#include "renderer.h"
#include "kraken.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define KRAKEN_HEIGHT   (800.0f)    // �N���[�P���̍���
#define DISTANCE        (8000.0f)   // ����
#define ANGLE_POS       (1200.0f)   // ���_�̍���

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CCameraStateAngryKraken::CCameraStateAngryKraken()
{

}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CCameraStateAngryKraken::~CCameraStateAngryKraken()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CCameraStateAngryKraken * CCameraStateAngryKraken::Create()
{
    // �������m��
    CCameraStateAngryKraken *pStateNormal = new CCameraStateAngryKraken;
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
void CCameraStateAngryKraken::Init()
{

}

//=====================================================================
// �X�V����
//=====================================================================
void CCameraStateAngryKraken::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    // �N���[�P��������
    ViewKraken(pCamera);
}

//=====================================================================
// �N���[�P�������鏈��
//=====================================================================
void CCameraStateAngryKraken::ViewKraken(CCamera* &pCamera)
{
    // �|�C���^�擾
    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    if (!pKraken)
    {
        return;
    }

    // �J�������W
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = pCamera->GetposRDest();  // �ړI�̊p�x
    D3DXVECTOR3 pos = pKraken->GetPos();            // �ʒu
    D3DXVECTOR3 rot = pKraken->GetRot();            // �p�x
    float fDistance = DISTANCE;                     // ����
    float fVartical = pCamera->GetVartical();       // �p�x
    float fHorizontal = pCamera->GetHorizontal();   // �p�x

    posRDest = D3DXVECTOR3(pos.x, pos.y + KRAKEN_HEIGHT, pos.z);    //�����_�ݒ�

    // �J�����̈ʒu�ݒ�
    VDest.x = pos.x + fDistance * sinf(fVartical) * sinf(rot.y + fHorizontal);  // �J�����ʒuX�ݒ�
    VDest.y = pos.y + ANGLE_POS * cosf(fVartical);                              // �J�����ʒuY�ݒ�
    VDest.z = pos.z + fDistance * sinf(fVartical) * cosf(rot.y + fHorizontal);  // �J�����ʒuZ�ݒ�

    //�ݒ�l�̔��f
    pCamera->GetposV() += (VDest - pCamera->GetposV());
    pCamera->GetposR() += (posRDest - pCamera->GetposR());

}
