#ifndef _CAMERA_TITLE_H_
#define _CAMERA_TITLE_H_
//=============================================================================
//
// �^�C�g���̃J�����N���X�w�b�_�[ [camera_title.h]
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
class CCameraTitle : public CCamera
{
public:
	CCameraTitle();			// �R���X�g���N�^
	~CCameraTitle();		// �f�X�g���N�^

	HRESULT Init(void);					// ����������
	static CCameraTitle*Create(void);	// �N���G�C�g

private:
	void NomalUpdate(void) override;
	void MouseUpdate(void) override;
};
#endif 