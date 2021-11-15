#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GET_TEXTURE_PTR		(CManager::GetInstance()->GetResourceManager()->GetTextureClass())	// �e�N�X�`���̃|�C���^
#define GET_SOUND_PTR		(CManager::GetInstance()->GetResourceManager()->GetSoundClass())	// �T�E���h�̃|�C���^
#define GET_XFILE_PTR		(CManager::GetInstance()->GetResourceManager()->GetXfileClass())	// X�t�@�C���̃|�C���^
#define GET_RENDERER_DEVICE	(CManager::GetInstance()->GetRenderer()->GetDevice())				// �f�o�C�X�擾

//=============================================================================
//�O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CMouse;
class CFade;
class CInputJoypad;
class CScene;
class CResourceManager;
class CGame;
class CModeBase;
class CLight;
class CCamera;
class CPlayer;
class CPause;

//=============================================================================
//�}�l�[�W���[�N���X
//=============================================================================
class CManager
{
public:
	//=========================================================================
	//�񋓌^��`
	//=========================================================================
	enum MODE_TYPE
	{
		MODE_TYPE_NONE = 0,
		MODE_TYPE_TITLE,			// �^�C�g�����[�h
		MODE_TYPE_GAME,				// �Q�[�����[�h
		MODE_TYPE_PLAYER_EDITOR,	// �v���C���[�̃G�f�B�^
		MODE_TYPE_MAX,
	};


	~CManager();	// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	// Set�֐�

	void SetMode(MODE_TYPE mode);							// ���[�h�̐ݒ�

	// Get�֐�

	MODE_TYPE GetMode(void);															// ���[�h�̏��
	CModeBase *GetModePtr(void);														// �Q�[���̏��
	CRenderer *GetRenderer(void)				{ return m_pRenderer.get(); }			// �����_���[���
	CInputKeyboard *GetKeyboard(void)			{ return m_pInput.get(); }				// �L�[�{�[�h���
	CMouse *GetMouse(void)						{ return m_pInputMouse.get(); }			// �}�E�X���
	CFade *GetFade(void)						{ return m_pFade.get(); }				// �t�F�[�h���
	CInputJoypad *GetJoypad(void)				{ return m_pJoypad.get(); }				// �W���C�p�b�h�R���g���[���̏��
	CScene *GetScene(void)						{ return m_pScene.get(); }				// �V�[�����
	CResourceManager *GetResourceManager(void)	{ return m_pResourceManager.get(); }	// ���\�[�X�}�l�[�W���̃|�C���^
	CCamera *GetCamera(void)					{ return m_pCamera.get(); }				// �J�����̃|�C���^
	CLight *GetLight(void)						{ return m_pLight.get(); }				// ���C�g�̃|�C���^
	CPlayer *GetPlayer(void);															// �v���C���[�̎擾
	CPause *GetPause(void) { return m_pPause; }					// �|�[�Y�̎擾����
	static void SetActivePause(bool bPause) { m_bPause = bPause; }					// �|�[�Y�̃Z�b�g
	static bool GetActivePause(void) { return m_bPause; }					// �t�F�[�h�̎擾����

	static CManager* GetInstance();		// �C���X�^���X���

private:
	// private�֐�
	void LoadAll(void);										// �S�Ẵ��[�h����
	void UnLoadAll(void);									// �S�ẴA�����[�h����

	// �����o�ϐ�
	unique_ptr<CRenderer> m_pRenderer;					// �����_���[�N���X�̃|�C���^
	unique_ptr<CInputKeyboard> m_pInput;				// �C���v�b�g�N���X�̃|�C���^
	unique_ptr<CMouse> m_pInputMouse;					// �}�E�X�C���v�b�g�N���X�̃|�C���^
	unique_ptr<CFade> m_pFade;							// �t�F�[�h�N���X�̃|�C���^
	unique_ptr<CInputJoypad> m_pJoypad;					// �W���C�p�b�h�R���g���[���̃|�C���^
	unique_ptr<CScene> m_pScene;						// �V�[���̃|�C���^
	unique_ptr<CResourceManager> m_pResourceManager;	// ���\�[�X�}�l�[�W���̃|�C���^
	unique_ptr<CModeBase> m_pModeBase;					// ���[�h�̃|�C���^
	unique_ptr<CCamera> m_pCamera;						// �J�����̃|�C���^
	unique_ptr<CLight> m_pLight;						// ���C�g�̃|�C���^
	MODE_TYPE m_mode;									// ���[�h
	CPause *m_pPause;									// �|�[�Y
	// �V���O���g��
	CManager();		// �R���X�g���N�^
	static CManager* m_pManager;

	static bool m_bPause;									// �|�[�Y�t���O
};

#endif