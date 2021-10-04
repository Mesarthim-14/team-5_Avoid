#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter
{
public:
	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum PARTS_NUM
	{
		PARTS_NUM_NONE = -1,
		PARTS_NUM_WAIST,			// [0]��
		PARTS_NUM_MAX				// ���[�V�����ő吔
	};

	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// �A�C�h�����[�V����
		MOTION_MAX					// ���[�V�����ő吔
	};

	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);			// �R���X�g���N�^
	~CPlayer();													// �f�X�g���N�^

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �N���G�C�g

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	void UpdateState(void);										// �v���C���[�̏��
	void PlayerControl(void);									// �v���C���[�̐���
	void RotFix(void);											// �p�x�̍X�V����
	void Move(void);											// �ړ�����

private:
	D3DXVECTOR3 m_rotDest;							// ��](�ڕW�l)
	bool m_bMove;									// �ړ��̃t���O
};
#endif