#ifndef _SCENE_H_
#define _SCENE_H_
//=============================================================================
//
// �I�u�W�F�N�g�Ǘ��N���X [scene.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �V�[���N���X
//=============================================================================
class CScene
{
public:
    //=========================================================================
    //�`��̗D�揇�ʂ̗񋓌^
    //=========================================================================
    enum PRIORITY
    {
        PRIORITY_0 = 0,
        PRIORITY_1,
        PRIORITY_TEST_MODEL,    // �e�X�g���f��
        PRIORITY_MODEL,         // ���f��
        PRIORITY_CHARACTER,     // �L�����N�^�[
        PRIORITY_COLLISION,     //�����蔻��
        PRIORITY_EFFECT,        // �G�t�F�N�g
        PRIORITY_SHADOW,        // �e
        PRIORITY_UI,            // UI
        PRIORITY_FADE,          // FADE
        PRIORITY_MAX            // �D�揇�ʂ̍ő吔
    };

    CScene(PRIORITY Priority);      // �R���X�g���N�^
    virtual ~CScene();              // �f�X�g���N�^
    static void ReleaseAll();       // �S�ẴI�u�W�F�N�g�������[�X
    static void UpdateAll();        // �S�ẴI�u�W�F�N�g���X�V
    static void DrawAll();          // �S�ẴI�u�W�F�N�g��`��

    virtual HRESULT Init() = 0;     // ����������
    virtual void Uninit() = 0;      // �I������
    virtual void Update() = 0;      // �X�V����
    virtual void Draw() = 0;        // �`�揈��

    CScene *GetNext();                          // ���̏����󂯎��
    static CScene *GetTop(const int &nCount);   // �V�[���̏��󂯎��
    static void SetPause(const bool &Pause);    // �|�[�Y�̏��

protected:
    void Release(); // �I�u�W�F�N�g���J��

private:
    // private�֐�
    void DeathRelease();    // ���S�t���O�̃����[�X

    // �����o�ϐ�
    static CScene *m_pTop[PRIORITY_MAX];    // �擪�̃I�u�W�F�N�g�ւ̃|�C���^
    static CScene *m_pCur[PRIORITY_MAX];    // ���݂̃I�u�W�F�N�g�ւ̃|�C���^
    CScene *m_pPrev;                        // �O�̃I�u�W�F�N�g�ւ̃|�C���^
    CScene *m_pNext;                        // ���̃I�u�W�F�N�g�ւ̃|�C���^
    PRIORITY m_Priority;                    // �`��̗D�揇��
    bool m_bDeath;                          // ���S�t���O
    bool m_bLate;                           // �`���x�点�鏈��
    static bool m_bPause;                   // �|�[�Y�̏��
};

#endif