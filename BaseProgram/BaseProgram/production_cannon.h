#ifndef _PRODUCTION_CANNON_H_
#define _PRODUCTION_CANNON_H_
//=======================================================================================
//
// ��C���̉��o�N���X [production_cannon.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// �O���錾
//=======================================================================================
class CPlayerStateCannon;
class CCameraStateCannon;
class CCannon;

//=======================================================================================
// �Q�[���N���X
//=======================================================================================
class CProductionCannon
{
public:
	CProductionCannon();		// �R���X�g���N�^
	~CProductionCannon();		// �f�X�g���N�^

	static CProductionCannon* Create();			// �C���X�^���X����
	HRESULT Init();								// ����������
	void Update();								// �X�V����
	inline bool GetEnd()const{ return m_bEnd; }	// �I���t���O

private:
	CPlayerStateCannon *m_pPlayerState;		// �v���C���[�̏��
	CCameraStateCannon *m_pCameraState;		// �J�����̏��
	int m_nCounter;							// �J�E���^�[
	bool m_bEnd;
};
#endif