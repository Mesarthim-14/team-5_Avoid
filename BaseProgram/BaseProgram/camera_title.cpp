//=============================================================================
//
// �^�C�g���J�����̏��� [camera_title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera_title.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLE_CAMERA_DISTANCE		(3000.0f)				// ����
#define TITLE_CAMERA_DEFAULT_F��	(D3DXToRadian(89.0f))	// �J�����p�x�c
#define TITLE_CAMERA_DEFAULT_H��	(D3DXToRadian(95.0f))	// �J�����p�x��
#define CAMERA_HEIGHT				(600.0f)				// �����_�̍���

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCameraTitle * CCameraTitle::Create(void)
{
	// �������m��
	CCameraTitle *pCamera = new CCameraTitle;

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
CCameraTitle::CCameraTitle()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCameraTitle::~CCameraTitle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCameraTitle::Init(void)
{
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, CAMERA_HEIGHT, 0.0f);
	D3DXVECTOR3 posV = ZeroVector3;
	float fDistance = TITLE_CAMERA_DISTANCE;
	float fVartical = TITLE_CAMERA_DEFAULT_F��;
	float fHorizontal = TITLE_CAMERA_DEFAULT_H��;

	SetDistance(fDistance);
	SetVartical(fVartical);
	SetHorizontal(fHorizontal);					// �����l�G�̂ق�������
	GetposR() = posR;
	GetposU() = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������x�N�g��

	posV.x = posR.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// �J�����ʒuX
	posV.y = posR.z + fDistance * cosf(fVartical);						// �J�����ʒuY
	posV.z = posR.y + fDistance * sinf(fVartical) * cosf(fHorizontal);	// �J�����ʒuZ

	GetposV() = posV;

	return S_OK;
}

//=============================================================================
// �ʏ��Ԃ̍X�V����
//=============================================================================
void CCameraTitle::NomalUpdate(void)
{

}

void CCameraTitle::MouseUpdate(void)
{
}
