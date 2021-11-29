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
#define GET_TEXTURE_PTR        (CManager::GetInstance()->GetResourceManager()->GetTextureClass())    // �e�N�X�`���̃|�C���^
#define GET_SOUND_PTR        (CManager::GetInstance()->GetResourceManager()->GetSoundClass())    // �T�E���h�̃|�C���^
#define GET_XFILE_PTR        (CManager::GetInstance()->GetResourceManager()->GetXfileClass())    // X�t�@�C���̃|�C���^
#define GET_RENDERER_DEVICE    (CManager::GetInstance()->GetRenderer()->GetDevice())                // �f�o�C�X�擾

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
class CGauge;

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
        MODE_TYPE_TITLE,            // �^�C�g�����[�h
        MODE_TYPE_GAME,             // �Q�[�����[�h
        MODE_TYPE_PLAYER_EDITOR,    // �v���C���[�̃G�f�B�^
        MODE_TYPE_MAX,
    };

    ~CManager();    // �f�X�g���N�^

    HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow); // ����������
    void Uninit();                                              // �I������
    void Update();                                              // �X�V����
    void Draw();                                                // �`�揈��

    // Set�֐�
    void SetMode(const MODE_TYPE &mode);    // ���[�h�̐ݒ�

    // Get�֐�
    static CManager* GetInstance();                                                                 // �C���X�^���X���
    CModeBase *GetModePtr();                                                                        // �Q�[���̏��
    CGame* GetGame()const;                                                                          // �Q�[�����
    CPlayer* GetPlayer()const;                                                                      // �v���C���[�̎擾
    inline MODE_TYPE GetMode()const                         { return m_mode; }                      // ���[�h�̏��
    inline CRenderer *GetRenderer()const                    { return m_pRenderer.get(); }           // �����_���[���
    inline CInputKeyboard *GetKeyboard()const               { return m_pInput.get(); }              // �L�[�{�[�h���
    inline CMouse *GetMouse()const                          { return m_pInputMouse.get(); }         // �}�E�X���
    inline CFade *GetFade()const                            { return m_pFade.get(); }               // �t�F�[�h���
    inline CInputJoypad *GetJoypad()const                   { return m_pJoypad.get(); }             // �W���C�p�b�h�R���g���[���̏��
    inline CScene *GetScene()const                          { return m_pScene.get(); }              // �V�[�����
    inline CResourceManager *GetResourceManager()const      { return m_pResourceManager.get(); }    // ���\�[�X�}�l�[�W���̃|�C���^
    inline CCamera *GetCamera()const                        { return m_pCamera.get(); }             // �J�����̃|�C���^
    inline CLight *GetLight()const                          { return m_pLight.get(); }              // ���C�g�̃|�C���^
    inline CPause *GetPause()const                          { return m_pPause; }                    // �|�[�Y�̎擾����
    inline CGauge *GetGauge()const                          { return m_pGauge; }                    // �Q�[�W�̎擾����
    inline static void SetActivePause(const bool &bPause)   { m_bPause = bPause; }                  // �|�[�Y�̃Z�b�g
    inline static bool GetActivePause()                     { return m_bPause; }                    // �t�F�[�h�̎擾����

private:
    // private�֐�
    void LoadAll();                                        // �S�Ẵ��[�h����
    void UnLoadAll();                                    // �S�ẴA�����[�h����

    // �����o�ϐ�
    unique_ptr<CRenderer> m_pRenderer;                  // �����_���[�N���X�̃|�C���^
    unique_ptr<CInputKeyboard> m_pInput;                // �C���v�b�g�N���X�̃|�C���^
    unique_ptr<CMouse> m_pInputMouse;                   // �}�E�X�C���v�b�g�N���X�̃|�C���^
    unique_ptr<CFade> m_pFade;                          // �t�F�[�h�N���X�̃|�C���^
    unique_ptr<CInputJoypad> m_pJoypad;                 // �W���C�p�b�h�R���g���[���̃|�C���^
    unique_ptr<CScene> m_pScene;                        // �V�[���̃|�C���^
    unique_ptr<CResourceManager> m_pResourceManager;    // ���\�[�X�}�l�[�W���̃|�C���^
    unique_ptr<CModeBase> m_pModeBase;                  // ���[�h�̃|�C���^
    unique_ptr<CCamera> m_pCamera;                      // �J�����̃|�C���^
    unique_ptr<CLight> m_pLight;                        // ���C�g�̃|�C���^
    MODE_TYPE m_mode;                                   // ���[�h
    CPause *m_pPause;                                   // �|�[�Y
    CGauge *m_pGauge;                                   // �Q�[�W

    // �V���O���g��
    CManager();                     // �R���X�g���N�^
    static CManager* m_pManager;    // ���g�̃|�C���^

    static bool m_bPause;           // �|�[�Y�t���O
};

#endif