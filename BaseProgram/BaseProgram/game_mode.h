#ifndef _GAME_MODE_H_
#define _GAME_MODE_H_
//=======================================================================================
//
// �Q�[�����[�h�N���X [game_mode.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// �Q�[���N���X
//=======================================================================================
class CGameMode
{
public:

	// �Q�[���̃��[�h
	enum GAME_MODE
	{
		GAME_MOVE_NONE = -1,	// �����l
		GAME_MOVE_NORMAL,		// �ʏ���
		GAME_MOVE_CANNON,		// ��C��ł��Ă���
		GAME_MOVE_MAX			// �ő�l
	};

	CGameMode();		// �R���X�g���N�^
	~CGameMode();		// �f�X�g���N�^

	static CGameMode* Create();												// �C���X�^���X����
	HRESULT Init();															// ����������
	void Update();															// �X�V����
	void SetMode(const GAME_MODE &GameMode) { m_GameMode = GameMode; }	// �Q�[�����[�h�̐ݒ�
	inline GAME_MODE GetMode()const			{ return m_GameMode; }		// �Q�[�����[�h�̏��
	
private:
	void NormalUpdate();
	void CannonUpdate();

	GAME_MODE m_GameMode;			// �Q�[�����[�h

	typedef void (CGameMode::*UPDATE_FUNC)();
	vector<UPDATE_FUNC> m_UpdateMode = 
	{ &CGameMode::NormalUpdate, &CGameMode::CannonUpdate};
};
#endif