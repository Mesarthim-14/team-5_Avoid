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
	CPlayer *pPlayer = CManager::GetPlayer();

	// �v���C���[���g���Ă�����
	if (pPlayer)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();	//�v���C���[�ʒu
		D3DXVECTOR3 PlayerRot = pPlayer->GetPos();	//�v���C���[�ʒu

		// �L�[�{�[�h�N���X���̎擾
		CInputKeyboard *pKeyInput = CManager::GetKeyboard();

		// �J�������W
		D3DXVECTOR3 VDest = ZeroVector3;
		D3DXVECTOR3 posRDest = GetposRDest();
		float fDistance = GetDistance();
		float fVartical = GetVartical();
		float fHorizontal = GetHorizontal();							// �J�����̊p�x

		// �Ǐ]
		//	Tracking(fDistance, fVartical, fHorizontal, PlayerPos, PlayerRot);

		// �L�[�{�[�h�X�V
		KeyBoardMove(fDistance, fVartical, fHorizontal, PlayerPos);
	}
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
	CPlayer *pPlayer = CManager::GetPlayer();

	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();
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