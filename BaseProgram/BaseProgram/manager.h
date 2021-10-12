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
#define GET_TEXTURE_PTR		(CManager::GetResourceManager()->GetTextureClass())	// �e�N�X�`���̃|�C���^
#define GET_SOUND_PTR		(CManager::GetResourceManager()->GetSoundClass())	// �T�E���h�̃|�C���^
#define GET_XFILE_PTR		(CManager::GetResourceManager()->GetXfileClass())	// X�t�@�C���̃|�C���^
#define GET_RENDERER_DEVICE	(CManager::GetRenderer()->GetDevice())				// �f�o�C�X�擾

//=============================================================================
//�O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CFade;
class CInputJoypad;
class CScene;
class CResourceManager;
class CGame;
class CModeBase;
class CLight;
class CCamera;
class CPlayer;

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

	CManager();		// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	// Set�֐�
	static void SetMode(MODE_TYPE mode);							// ���[�h�̐ݒ�

	// Get�֐�
	static MODE_TYPE GetMode(void);																// ���[�h�̏��
	static CModeBase *GetModePtr(void);															// �Q�[���̏��
	static CRenderer *GetRenderer(void)					{ return m_pRenderer.get(); }			// �����_���[���
	static CInputKeyboard *GetKeyboard(void)			{ return m_pInput.get(); }				// �L�[�{�[�h���
	static CFade *GetFade(void)							{ return m_pFade.get(); }				// �t�F�[�h���
	static CInputJoypad *GetJoypad(void)				{ return m_pJoypad.get(); }				// �W���C�p�b�h�R���g���[���̏��
	static CScene *GetScene(void)						{ return m_pScene.get(); }				// �V�[�����
	static CResourceManager *GetResourceManager(void)	{ return m_pResourceManager.get(); }	// ���\�[�X�}�l�[�W���̃|�C���^
	static CCamera *GetCamera(void)						{ return m_pCamera.get(); }				// �J�����̃|�C���^
	static CLight *GetLight(void)						{ return m_pLight.get(); }				// ���C�g�̃|�C���^
	static CPlayer *GetPlayer(void);															// �v���C���[�̎擾

private:
	// private�֐�
	void LoadAll(void);										// �S�Ẵ��[�h����
	void UnLoadAll(void);									// �S�ẴA�����[�h����

	// �����o�ϐ�
	static unique_ptr<CRenderer> m_pRenderer;				// �����_���[�N���X�̃|�C���^
	static unique_ptr<CInputKeyboard> m_pInput;				// �C���v�b�g�N���X�̃|�C���^
	static unique_ptr<CFade> m_pFade;						// �t�F�[�h�N���X�̃|�C���^
	static unique_ptr<CInputJoypad> m_pJoypad;				// �W���C�p�b�h�R���g���[���̃|�C���^
	static unique_ptr<CScene> m_pScene;						// �V�[���̃|�C���^
	static unique_ptr<CResourceManager> m_pResourceManager;	// ���\�[�X�}�l�[�W���̃|�C���^
	static unique_ptr<CModeBase> m_pModeBase;				// ���[�h�̃|�C���^
	static unique_ptr<CCamera> m_pCamera;					// �J�����̃|�C���^
	static unique_ptr<CLight> m_pLight;						// ���C�g�̃|�C���^
	static MODE_TYPE m_mode;								// ���[�h
};

#endif