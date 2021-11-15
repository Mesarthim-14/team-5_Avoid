#ifndef _GAME_H_
#define _GAME_H_
//=======================================================================================
//
// �Q�[���N���X [game.h]
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
class CPlayer;
class CGimmickFactory;
class CGameMode;

//=======================================================================================
// �Q�[���N���X
//=======================================================================================
class CGame : public CModeBase
{
public:
	CGame();		// �R���X�g���N�^
	~CGame();		// �f�X�g���N�^

	HRESULT Init();																// ����������
	void Uninit();																// �I������
	void Update();																// �X�V����
	void Draw();																// �`�揈��
	static float GetGravity()					{ return m_fGravity; };			//�d��
	CGimmickFactory* GetGimmickFactory()		{ return m_pGimmickFactory; }	// �M�~�b�N�̏��
	CGameMode* GetGameMode()					{ return m_pGameMode; }

private:
	// private�֐�
	void CreatePlayer();				// �v���C���[�̐����֐�
	void CreateEnemy();					// �G�̐���
	void CreateMap();					// �}�b�v�̐���
	void ShowInfo();					//���\��
	void CreateMode();					// �Q�[�����[�h�N���X����

	// �����o�ϐ�
	CPlayer *m_pPlayer;						// �v���C���[�̃|�C���^
	bool m_bGameEnd;						// �Q�[���̃G���h�t���O
	LPD3DXFONT m_pFont;						// �f�o�b�N�p�t�H���g
	static float m_fGravity;				// �d��
	CGimmickFactory *m_pGimmickFactory;		// �M�~�b�N����
	CGameMode *m_pGameMode;					// �Q�[�����[�h
};
#endif