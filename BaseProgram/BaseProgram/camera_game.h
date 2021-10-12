#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
//=============================================================================
//
// �Q�[���J�����N���X�w�b�_�[ [camera_game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"

//=============================================================================
// �J�����N���X
//=============================================================================
class CCameraGame : public CCamera
{
public:
	CCameraGame();					// �R���X�g���N�^
	~CCameraGame();					// �f�X�g���N�^

	HRESULT Init(void);					// ����������
	static CCameraGame*Create(void);	// �N���G�C�g

private:
	// private�֐�
	void NomalUpdate(void) override;
	void Tracking(const float &fDistance, float &fVartical,
		float &fHorizontal, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerRot);	// �Ǐ]
	void KeyBoardMove(const float &fDistance, float &fVartical,
		float &fHorizontal, D3DXVECTOR3 PlayerPos);											// �L�[�{�[�h�̓���
};
#endif 