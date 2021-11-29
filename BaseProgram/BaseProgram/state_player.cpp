//=====================================================================
//
//    �v���C���[�̏�ԊǗ��N���X [state_player.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h
//=====================================================================
#include "state_player.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "camera.h"
#include "particlepop.h"
#include "particleshrink.h"
#include "particleaura.h"
#include "gauge.h"

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerState::CPlayerState()
{
    m_fAngleSpeed = 0.6f;
    memset(m_bMove, 0, sizeof(m_bMove));
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPlayerState::~CPlayerState()
{
}

//=====================================================================
// �A�j���[�V�����ݒ�
//=====================================================================
void CPlayerState::SetAnimation(const UINT &animID, const FLOAT &time)
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }
    CSkinmeshModel* pSkinMeshModel = pPlayer->GetCurrentSkinMeshPtr();
    if (!pSkinMeshModel)
    {
        return;
    }

    pSkinMeshModel->GetHLcontroller()->ChangeAnimation(animID);
    pSkinMeshModel->GetHLcontroller()->SetLoopTime(animID, time);
}

//=====================================================================
// �L�[�{�[�h����
//=====================================================================
void CPlayerState::MoveByKeyboard(CPlayer* &pPlayer)
{
    D3DXVECTOR3 pos = pPlayer->GetPos();            // ���W
    D3DXVECTOR3 rot = pPlayer->GetRot();            // �p�x
    float fSpeed = pPlayer->GetSpeed();             // �ړ���
    float fCameraRot = D3DXToRadian(CManager::GetInstance()->GetCamera()->GetRot().y);    // �J�����̊p�x
    float fAngle = pPlayer->GetAngle();             // �A���O��
    D3DXVECTOR3 Inertia = pPlayer->GetInertia();    // ����
    D3DXVECTOR3 rotDest = pPlayer->GetRotDest();    // �ړI�̊p�x
    m_bMove[1] = m_bMove[0];
    m_bMove[0] = false;

    // �O�Ɉړ�
    if (CLibrary::KeyboardPress(DIK_W))
    {
        // �ړ��ʁE�p�x�̐ݒ�
        Inertia.x = +sinf(fAngle)*fSpeed;
        Inertia.z = -cosf(fAngle)*fSpeed;
        //�i�s�����Ɍ��������킹��
        rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
        m_bMove[0] = true;
    }

    // ���Ɉړ�
    if (CLibrary::KeyboardPress(DIK_S))
    {
        // �ړ��ʁE�p�x�̐ݒ�
        Inertia.x = -sinf((fAngle))*fSpeed;
        Inertia.z = +cosf((fAngle))*fSpeed;
        //�i�s�����Ɍ��������킹��
        rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(-180.0f);
        m_bMove[0] = true;
    }

    // ���Ɉړ�
    if (CLibrary::KeyboardPress(DIK_A))
    {
        // �ړ��ʁE�p�x�̐ݒ�
        Inertia.x = +sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
        Inertia.z = -cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;

        //�i�s�����Ɍ��������킹��
        rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
        m_bMove[0] = true;
    }

    // �E�Ɉړ�
    if (CLibrary::KeyboardPress(DIK_D))
    {
        // �ړ��ʁE�p�x�̐ݒ�
        Inertia.x = +sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
        Inertia.z = -cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
        //�i�s�����Ɍ��������킹��
        rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(-180.0f);
        m_bMove[0] = true;
    }

    //���O�Ɉړ�
    if (CLibrary::KeyboardPress(DIK_W) && CLibrary::KeyboardPress(DIK_A))
    {
        // �ړ��ʁE�p�x�̐ݒ�
        Inertia.x = +sinf((fAngle + D3DXToRadian(45.0f)))*fSpeed;
        Inertia.z = -cosf((fAngle + D3DXToRadian(45.0f)))*fSpeed;
        rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
        m_bMove[0] = true;
    }

    //�E�O�Ɉړ�
    if (CLibrary::KeyboardPress(DIK_W) && CLibrary::KeyboardPress(DIK_D))
    {
        // �ړ��ʁE�p�x�̐ݒ�
        Inertia.x = +sinf((fAngle + D3DXToRadian(-45.0f)))*fSpeed;
        Inertia.z = -cosf((fAngle + D3DXToRadian(-45.0f)))*fSpeed;
        rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
        m_bMove[0] = true;
    }

    //�����Ɉړ�
    if (CLibrary::KeyboardPress(DIK_S) && CLibrary::KeyboardPress(DIK_A))
    {
        // �ړ��ʁE�p�x�̐ݒ�
        Inertia.x = -sinf((fAngle + D3DXToRadian(-45.0f)))*fSpeed;
        Inertia.z = +cosf((fAngle + D3DXToRadian(-45.0f)))*fSpeed;
        rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
        m_bMove[0] = true;
    }

	//�E���Ɉړ�
	if (CLibrary::KeyboardPress(DIK_S) && CLibrary::KeyboardPress(DIK_D))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		Inertia.x = -sinf((fAngle + D3DXToRadian(45.0f)))*fSpeed;
		Inertia.z = +cosf((fAngle + D3DXToRadian(45.0f)))*fSpeed;
		rotDest.y = atan2f(Inertia.x, Inertia.z) + D3DXToRadian(180.0f);
		m_bMove[0] = true;
	}

    // ���W�ݒ�
    pPlayer->SetPos(pos);

    if (!m_bMove[0])
    {
        Inertia = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        if (m_bMove[1])
        {
            // �A�j���[�V�����ݒ�
            SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
        }
    }
    else
    {
        if (!m_bMove[1])
        {
            // �A�j���[�V�����ݒ�
            SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_WALK), 60);
        }
    }

    //�p�x�␳
    while (fCameraRot - fAngle > D3DXToRadian(180))
    {
        fCameraRot -= D3DXToRadian(360);
    }

    while (fCameraRot - fAngle < D3DXToRadian(-180))
    {
        fCameraRot += D3DXToRadian(360);
    }

    //�J�����̓]�����x��肿����ƒx����������
    fAngle += (fCameraRot - fAngle) * m_fAngleSpeed;
    pPlayer->SetAngle(fAngle);

    // ����
    D3DXVECTOR3 move = pPlayer->GetMove();
    move += (Inertia - move) * pPlayer->GetInertiaNum();

    pPlayer->SetMove(move);
    pPlayer->SetRotDest(rotDest);
}