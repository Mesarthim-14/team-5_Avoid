//=====================================================================
//
// �~���J�����ʏ��ԊǗ��N���X [state_camera_descent.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_camera_descent.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "keyboard.h"
#include "renderer.h"
#include "kraken.h"
#include "state_kraken_normal.h"
#include "state_camera_normal.h"
#include "state_player_normal.h"
#include "camera_game.h"
#include "boss_hp.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define PLAYER_HEIGHT           (0.0f)                  // �����_�̍���
#define CAMERA_MIN_HIGHT        (2.0f)                  // �J�����̍Œፂ�x
#define STOP_LIMIT              (180)                   // �I���̎���

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CCameraStateDescent::CCameraStateDescent()
{
    m_nCount = 0;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CCameraStateDescent::~CCameraStateDescent()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CCameraStateDescent * CCameraStateDescent::Create()
{
    // �������m��
    CCameraStateDescent *pState = new CCameraStateDescent;
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
void CCameraStateDescent::Init()
{

}

//=====================================================================
// �X�V����
//=====================================================================
void CCameraStateDescent::Update()
{
    CCameraGame* pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();  // �J����
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();                    // �v���C���[
    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();         // �N���[�P��

    if (!pCamera || !pPlayer || !pKraken)
    {
        return;
    }

    D3DXVECTOR3 PlayerPos = pPlayer->GetPos();    //�v���C���[�ʒu
    D3DXVECTOR3 PlayerRot = pPlayer->GetRot();    //�v���C���[�ʒu

    // �J�������W
    float fDistance = pCamera->GetDistance();
    float fVartical = pCamera->GetVartical();
    float fHorizontal = pCamera->GetHorizontal();   // �J�����̊p�x

    //�L�[�{�[�h�N���X���̎擾
    CInputKeyboard *pKeyInput = CManager::GetInstance()->GetKeyboard();
    D3DXVECTOR3 VDest = ZeroVector3;
    // �p�x�̏C��
    CLibrary::RotFix(fHorizontal);

    // �p�x�̐ݒ�
    pCamera->SetVartical(fVartical);
    pCamera->SetHorizontal(fHorizontal);

    // �J�����̈ʒu�ݒ�
    VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(PlayerRot.y);    // �J�����ʒuX�ݒ�
    VDest.y = PlayerPos.y + fDistance * cosf(fVartical);                        // �J�����ʒuY�ݒ�
    VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(PlayerRot.y);    // �J�����ʒuZ�ݒ�

    D3DXVECTOR3 posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);    //�����_�ݒ�

    //�ݒ�l�̔��f
    pCamera->GetposV() += (VDest - pCamera->GetposV())*0.1f;
    pCamera->GetposR() += (posRDest - pCamera->GetposR())*0.1f;

    m_nCount++;
    if (m_nCount >= STOP_LIMIT)
    {
        pPlayer->ChangeState(CPlayerStateNormal::Create());
        pCamera->ChangeState(CCameraStateNormal::Create());
        pKraken->ChangeState(CKrakenStateNormal::Create());
        CGame *pGame = CManager::GetInstance()->GetGame();
        if (pGame)
        {
            pGame->CreateUi();
            CBossHp* pUi = pKraken->GetHpUi();
            if (pUi)
            {
                pUi->SetDraw(true);
            }
        }
    }
}