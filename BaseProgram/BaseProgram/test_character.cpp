//=============================================================================
// �e�X�g[test_character.cpp]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "test_character.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "game.h"

//=============================================================================
// �}�N����`
// Author : Konishi Yuuto
//=============================================================================
#define PLAYER_SPEED			(10.0f)									// �v���C���[�̈ړ���
#define PLAYER_ROT_SPEED		(0.1f)									// �L�����N�^�[�̉�]���鑬�x
#define SIZE					(D3DXVECTOR3 (1200.0f,1000.0f,1200.0f))	// �T�C�Y

//=============================================================================
// ���������֐�
// Author : Konishi Yuuto
//=============================================================================
CTestCharacter * CTestCharacter::Create(void)
{
	CTestCharacter *pPlayer = new CTestCharacter;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ����������
		pPlayer->SetCharacterInfo(ZeroVector3, ZeroVector3);
		pPlayer->Init();
	}

	// CTestCharacter��Ԃ�
	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CTestCharacter::CTestCharacter(PRIORITY Priority) : CCharacter(Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
}

//=============================================================================
// �f�X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CTestCharacter::~CTestCharacter()
{
}

//=============================================================================
// �����������֐�
// Author : Konishi Yuuto
//=============================================================================
HRESULT CTestCharacter::Init(void)
{
	// CXfile�擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		SetUseShadow();									// �e�̎g�p
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_TEST);	// ���f���̐���
		SetShadowRotCalculation();						// �e�̌���
	}

	// ����������
	CCharacter::Init();

	// ������
	m_rotDest = GetRot();	// ����
	SetSize(SIZE);			// �T�C�Y�ݒ�
	SetSpeed(PLAYER_SPEED);	// �X�s�[�h�ݒ�

	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Uninit(void)
{
	CCharacter::Uninit();
}

//=============================================================================
// �X�V�֐������֐�
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Update(void)
{
	// �X�V
	CCharacter::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �Â��ʒu�ݒ�
	SetPosOld(pos);

	// ��ԍX�V
	UpdateState();
}

//=============================================================================
// �`�揈���֐�
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Draw(void)
{
	// �`��
	CCharacter::Draw();
}

//=============================================================================
// ��ԍX�V
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::UpdateState(void)
{

}

//=============================================================================
// �ړ�����
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Move(void)
{

}