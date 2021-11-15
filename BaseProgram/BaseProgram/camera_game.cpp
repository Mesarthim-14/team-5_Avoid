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
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "motion.h"
#include "library.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GAME_CAMERA_DEFAULT_F��		(D3DXToRadian(55.0f))	// �J�����̃�Default�l
#define GAME_CAMERA_DEFAULT_H��		(D3DXToRadian(0.0f))	// �J�����p�x��
#define PLAYER_HEIGHT				(0.0f)					// �����_�̍���
#define GAME_CAMERA_DISTANCE		(2500.0f)				// ����
#define CAMERA_MIN_HIGHT			(2.0f)					// �J�����̍Œፂ�x
#define INPUT_CONVERSION			(D3DXToRadian(1.0f))	// �X�e�B�b�N���͕ω���

#define CAMERA_DISTANCE			(2000.0f)//�v���C���[�ƃJ�����̋���
#define PLAYER_CAMERA_HEIGHT	(300.0f) //�v���C���[�̍���

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCameraGame * CCameraGame::Create(void)
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
// �R���X�g���N�^
//=============================================================================
CCameraGame::CCameraGame()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCameraGame::~CCameraGame()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCameraGame::Init(void)
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

	return S_OK;
}

//=============================================================================
// �ʏ��Ԃ̍X�V����
//=============================================================================
void CCameraGame::NomalUpdate(void)
{
	// �v���C���[
	CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();

	// �v���C���[���g���Ă�����
	if (pPlayer)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();	//�v���C���[�ʒu
		D3DXVECTOR3 PlayerRot = pPlayer->GetPos();	//�v���C���[�ʒu

		// �L�[�{�[�h�N���X���̎擾
		CInputKeyboard *pKeyInput = CManager::GetInstance()->GetKeyboard();

		// �J�������W
		D3DXVECTOR3 VDest = ZeroVector3;
		D3DXVECTOR3 posRDest = GetposRDest();
		float fDistance = GetDistance();
		float fVartical = GetVartical();
		float fHorizontal = GetHorizontal();							// �J�����̊p�x

		// �Ǐ]
		//Tracking(fDistance, fVartical, fHorizontal, PlayerPos, PlayerRot);

		// �L�[�{�[�h�X�V
		KeyBoardMove(fDistance, fVartical, fHorizontal, PlayerPos);
	}
}

//=============================================================================
// �}�E�X�̎��̍X�V����
// Author Hayashikawa Sarina
//=============================================================================
void CCameraGame::MouseUpdate(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h�X�V
	// �v���C���[
	CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
	D3DXVECTOR3 fRotateCenter; //�J������]�̒��S

	POINT point;
	GetCursorPos(&point);
	D3DXVECTOR3 CameraRot = CManager::GetInstance()->GetCamera()->GetRot();
	//if (CManager::GetIsActiveWindow() == true)//�E�B���h�E���A�N�e�B�u�Ȃ�J�[�\���Z�b�g
	//{
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

	Setrot(CameraRot);

	if (pPlayer != NULL)
	{
		//�J������]�̒��S���v���C���[�̈ʒu�ɂ���i������Ɂj
		fRotateCenter = pPlayer->GetPos() + D3DXVECTOR3(0.0f, PLAYER_CAMERA_HEIGHT, 0.0f);
	}
	
	//�J�������n�ʂ��ђʂ��Ă��܂��ꍇ�n�ʂɔ��킹��悤��
	if (fRotateCenter.y + sinf(D3DXToRadian(GetRot().x)) * CAMERA_DISTANCE > 0)
	{
		SetposV(fRotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-GetRot().y)) * cosf(D3DXToRadian(GetRot().x)) * CAMERA_DISTANCE, sinf(D3DXToRadian(GetRot().x)) * CAMERA_DISTANCE, cosf(D3DXToRadian(-GetRot().y)) * cosf(D3DXToRadian(GetRot().x)) * CAMERA_DISTANCE));
	}
	else
	{
		SetposV(fRotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-GetRot().y)) * cosf(D3DXToRadian(GetRot().x))* CAMERA_DISTANCE, -fRotateCenter.y + 1, cosf(D3DXToRadian(-GetRot().y)) * cosf(D3DXToRadian(GetRot().x))* CAMERA_DISTANCE));
	}

	//�����_�𒆐S�ɂ��킹��
	SetposR(fRotateCenter);
}

//=============================================================================
// �Ǐ]����
//=============================================================================
void CCameraGame::Tracking(const float &fDistance, float &fVartical,
	float &fHorizontal, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerRot)
{
	D3DXVECTOR3 VDest = ZeroVector3;
	D3DXVECTOR3 posRDest = ZeroVector3;

	// �J�����̈ʒu�ݒ�
	VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(PlayerRot.y);	// �J�����ʒuX�ݒ�
	VDest.y = PlayerPos.y + PLAYER_HEIGHT + fDistance * cosf(fVartical);		// �J�����ʒuY�ݒ�
	VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(PlayerRot.y);	// �J�����ʒuZ�ݒ�

	posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);	//�����_�ݒ�

	//�J����POSY�̉���
	if (VDest.y <= CAMERA_MIN_HIGHT)
	{
		VDest.y = CAMERA_MIN_HIGHT;	//���E�l�ɖ߂�
	}

	//�ݒ�l�̔��f
	GetposV() += (VDest - GetposV())*0.1f;
	GetposR() += (posRDest - GetposR())*0.9f;

}

//=============================================================================
// �L�[�{�[�h�̍X�V
//=============================================================================
void CCameraGame::KeyBoardMove(const float &fDistance, float &fVartical,
	float &fHorizontal, D3DXVECTOR3 PlayerPos)
{
	// �v���C���[
	CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();

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
	SetVartical(fVartical);
	SetHorizontal(fHorizontal);

	// �J�����̈ʒu�ݒ�
	VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// �J�����ʒuX�ݒ�
	VDest.y = PlayerPos.y + fDistance * cosf(fVartical);						// �J�����ʒuY�ݒ�
	VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(fHorizontal);	// �J�����ʒuZ�ݒ�
	
	D3DXVECTOR3 posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);	//�����_�ݒ�

	//�J����POSY�̉���
	if (VDest.y <= CAMERA_MIN_HIGHT)
	{
		VDest.y = CAMERA_MIN_HIGHT;	//���E�l�ɖ߂�
	}

	//�ݒ�l�̔��f
	GetposV() += (VDest - GetposV())*0.1f;
	GetposR() += (posRDest - GetposR())*0.9f;
}