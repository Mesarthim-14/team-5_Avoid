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
#include "plane_jump.h"
#include "plane_jumpreservoir.h"
#include "mouse.h"
#include "state_player_avoid.h"
#include "sound.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define CHARGEJUMP_MAX      (100)   // �^���J�E���g�ő�
#define PARTICLE_STRAT      (30)    // ���߃G�t�F�N�g�����J�n�܂ł̎���
#define HIGHJUMP_CONSUME    (20)    // ���߃W�����v�������̃��C�t������
#define SOUND_INTER         (60)    // ���̊Ԋu

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateJump::CPlayerStateJump()
{
    m_fJumpTimeCount = 0.0f;
    m_bJumpCheck = false;
    m_nChargeJumpCount = 0;
    m_bIsReadyChargeJump = false;
    m_fJumpValue = 30.0f;
    m_fDushJumpValue = 1.0f;
    m_bJumpEffect = true;
    m_nCntEffect = 0;
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
    //// �A�j���[�V�����ݒ�
    //SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_JUMP), 60);

    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        // ��Ԃ̐ݒ�
        pPlayer->SetState(CPlayer::JUMP);
    }
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

    // ���n���̏���
    if (pPlayer->GetLanding() && m_bJumpCheck)
    {
        pPlayer->ChangeState(CPlayerStateNormal::Create());
        return;
    }

    // �W�����v����
    JumpProcess(pPlayer);

    // �W�����v����
    Avoidance(pPlayer);

    if (m_bJumpCheck)
    { // �W�����v���n�߂Ă���Ƃ�
        // �W�����v���Ԃ��J�E���g
        m_fJumpTimeCount++;
    }
}

//=====================================================================
// ���C�t�̌��Z
//=====================================================================
void CPlayerStateJump::SubLife(CPlayer* &pPlayer)
{
    CGauge * pGauge = CManager::GetInstance()->GetGame()->GetGauge();

    // Hp����
    pPlayer->SubLife(HIGHJUMP_CONSUME);
    pGauge->SetDown((float)HIGHJUMP_CONSUME);
    pGauge->SetHitDown(true);
}

//=====================================================================
// �W�����v���̏���
//=====================================================================
void CPlayerStateJump::JumpProcess(CPlayer* &pPlayer)
{
    // �L�[�{�[�h�ړ�����
    MoveByKeyboard(pPlayer);
    D3DXVECTOR3 move = pPlayer->GetMove();
    D3DXVECTOR3 pos = pPlayer->GetPos();

    if (CLibrary::KeyboardPress(DIK_SPACE) && !m_bJumpCheck)
    {
        m_nChargeJumpCount++;

		// �A�j���[�V�����ݒ�
		SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_TAME), CHARGEJUMP_MAX, false);

        // �G�t�F�N�g�̔�������
        if (m_nChargeJumpCount >= PARTICLE_STRAT && m_nChargeJumpCount <= CHARGEJUMP_MAX && m_bJumpEffect)
        {
            m_bJumpEffect = false;
            CPlaneJumpReservoir::Create(pos);
        }
        if (!m_bJumpEffect)
        {
            JumpEffect();
        }

        if (m_nChargeJumpCount > CHARGEJUMP_MAX)
        {
            // �A�j���[�V�����ݒ�
            SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_TAME_END), 60);
        }

        // ���̍Đ�
        if (m_nChargeJumpCount % SOUND_INTER == 0)
        {
            CLibrary::SetSound(CSound::SOUND_SE_JUMP_CHARGE);
        }
    }

    if (CLibrary::KeyboardRelease(DIK_SPACE) && !m_bJumpCheck)//�ʏ�W�����v
    {
        //�G�t�F�N�g����
        if (m_nChargeJumpCount >= CHARGEJUMP_MAX)
        {
            m_bIsReadyChargeJump = true;
            pPlayer->SetLanding(false);

            CPlaneJump::Create(D3DXVECTOR3(pos.x, pos.y, pos.z));
            m_bJumpCheck = true;
            move.y += m_fJumpValue * 3;
            move.x += move.x * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
            move.z += move.z * (m_fDushJumpValue * sinf(move.y / m_fJumpValue));
            //    pPlayer->SetState(CPlayer::STATE_JUMP);
            m_nChargeJumpCount = 0;
            m_bIsReadyChargeJump = false;

            // ���C�t�̌��Z
            SubLife(pPlayer);

            CLibrary::SetSound(CSound::SOUND_SE_SUPER_JUMP);
        }
        else
        {
            m_bJumpCheck = true;
            move.y += m_fJumpValue;
            m_nChargeJumpCount = 0;
            CLibrary::SetSound(CSound::SOUND_SE_JUMP);
        }
        pPlayer->SetLanding(false);
    }
    // �ړ��ʂ̐ݒ�
    pPlayer->SetMove(move);
}

//=====================================================================
// �������
//=====================================================================
void CPlayerStateJump::Avoidance(CPlayer* &pPlayer)
{
    CMouse *pMouse = CManager::GetInstance()->GetMouse();   // �}�E�X
    if (pMouse->GetButtonTrigger(CMouse::MOUSE_LEFT))//���
    {
        if (pPlayer->GetSlimeState() != CPlayer::SLIME_LITTLESIZE)
        {
            pPlayer->ChangeState(CPlayerStateAvoid::Create());
        }
    }
}

//=====================================================================
// �G�t�F�N�g����
//=====================================================================
void CPlayerStateJump::JumpEffect()
{
    m_nCntEffect++;
    if (m_nCntEffect >= 20)
    {
        m_bJumpEffect = true;
        m_nCntEffect = 0;
    }
}
