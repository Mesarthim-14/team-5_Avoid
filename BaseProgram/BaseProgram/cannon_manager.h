#ifndef _CANNON_MANAGER_H_
#define _CANNON_MANAGER_H_
//=============================================================================
//
// ��C�Ǘ��N���X [cannon_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "main.h"

//=========================================================================
// �O���錾
//=========================================================================
class CCannon;
class CKeyE;

//=========================================================================
// �N���X��`
//=========================================================================
class CCannonManager
{
public:
	CCannonManager();		// �R���X�g���N�^
	~CCannonManager();		// �f�X�g���N�^

	static CCannonManager *Create();						// �C���X�^���X����
	HRESULT Init();											// ����������
	void Uninit();											// �I������
	void Update();											// �X�V����
	inline int GetAttackNum()const { return m_nAttackNum; }	// �`�F�b�N�|�C���g�̒l

private:
	// private�֐�
	void CreateCannon();			// ���̐���
	void CreateUi();				// Ui����
	void CannonCollision();			// ���ꂼ��̑�C�̓����蔻��
	void InputJudge();				// �{�^���̔���
	void CreateBullet();			// ��C�̒e����
	void ChangeGameMode();			// ���[�h�`�F���W
	vector<CCannon*> m_apCannon;	// ��C�̃|�C���^
	int m_nAttackNum;				// �U��������
	CKeyE *m_pKeyE;					// E�L�[��UI�|�C���^
	int m_nTargetCannon;			// �ΏۂƂȂ��C�̔ԍ�
};

#endif