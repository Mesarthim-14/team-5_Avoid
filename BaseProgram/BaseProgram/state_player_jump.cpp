//=====================================================================
//
//    �W�����v��ԊǗ��N���X [state_player_jump.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player_jump.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "state_player_normal.h"
#include "gauge.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define CHARGEJUMP_MAX      (100)   // �^���J�E���g�ő�
#define HIGHJUMP_CONSUME    (1)     // ���߃W�����v�������̃��C�t������

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateJump::CPlayerStateJump()
{
    m_fJumpTimeCount = 0.0f;
    m_bJumpCheck = false;
    m_nChargeJumpCount = 0;
    m_bIsReadyChargeJump = false;
    m_fJumpValue = 40.0f;
    m_fDushJumpValue = 1.0f;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPlayerStateJump::~CPlayerStateJump()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CPlayerStateJump * CPlayerStateJump::Create()
{
    // �������m��
    CPlayerStateJump *pStateJump = new CPlayerStateJump;
    if (pStateJump)
    {
        // ����������
        pStateJump->Init();
        return pStateJump;
    }
    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CPlayerStateJump::Init()
{
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_JUMP), 60);
}

//=====================================================================
// �X�V����
//=====================================================================
void CPlayerStateJump::Update()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    // �W�����v����
    JumpProcess(pPlayer);

    // ���n���̏���
    if (pPlayer->GetLanding() && m_bJumpCheck)
    {
        pPlayer->ChangeState(CPlayerStateNormal::Create());
    }
}

//=====================================================================
// ���C�t�̌��Z
//=====================================================================
void CPlayerStateJump::SubLife(CPlayer* &pPlayer)
{
    // Hp����
    pPlayer->SubLife(HIGHJUMP_CONSUME);
    CGauge::SetDown((float)HIGHJUMP_CONSUME);
    CGauge::SetHitDown(true);
}

//=====================================================================
// �W�����v���̏���
//=====================================================================
void CPlayerStateJump::JumpProcess(CPlayer* &pPlayer)
{
    // �L�[�{�[�h�ړ�����
    MoveByKeyboard(pPlayer);
    D3DXVECTOR3 move = pPlayer->GetMove();

    if (CLibrary::KeyboardPress(DIK_SPACE))
    {
        m_nChargeJumpCount++;

        //�G�t�F�N�g����
        if (m_nChargeJumpCount >= CHARGEJUMP_MAX)
        {
            m_bIsReadyChargeJump = true;
            pPlayer->SetLanding(false);
        }
    }

    if (CLibrary::KeyboardPress(DIK_SPACE) && m_bIsReadyChargeJump)//���ߏ�Ԃŗ�������
    {
        m_bJumpCheck = true;
        move.y += m_fJumpValue * 3;
        move.x += move.x * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
        move.z += move.z * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
        //    pPlayer->SetState(CPlayer::STATE_JUMP);
        m_nChargeJumpCount = 0;
        m_bIsReadyChargeJump = false;

        // ���C�t�̌��Z
        SubLife(pPlayer);
    }

    else if (CLibrary::KeyboardRelease(DIK_SPACE))//�ʏ�W�����v
    {
        m_bJumpCheck = true;
        move.y += m_fJumpValue;
        m_nChargeJumpCount = 0;
        pPlayer->SetLanding(false);
    }

    // �ړ��ʂ̐ݒ�
    pPlayer->SetMove(move);
}