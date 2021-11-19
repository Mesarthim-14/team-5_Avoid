#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
//=============================================================================
//
// ���\�[�X�}�l�[�W���[���� [resource_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CTexture;
class CXfile;
class CSound;

//=============================================================================
// ���\�[�X�}�l�[�W���[�N���X
//=============================================================================
class CResourceManager
{
public:
    ~CResourceManager();                        // �f�X�g���N�^

    HRESULT Init();                             // ����������
    void LoadAll();                             // �S�Ẵ��[�h����
    void UnLoadAll();                           // �S�ẴA�����[�h

    static CResourceManager *GetInstance();     // �C���X�^���X�擾�֐�

    // Get�֐�
    inline CTexture *GetTextureClass()const     { return m_pTexture; }  // �e�N�X�`���̏��
    inline CXfile *GetXfileClass()const         { return m_pXFile; }    // �e�N�X�`���̏��
    inline CSound *GetSoundClass()const         { return m_pSound; }    // �T�E���h�̏��

private:
    CResourceManager();                             // �R���X�g���N�^
    static CResourceManager *m_pResourceManager;    // ���g�̃|�C���^

    CTexture *m_pTexture;   // �e�N�X�`���̃|�C���^
    CXfile *m_pXFile;       // X�t�@�C���̃|�C���^
    CSound *m_pSound;       // �T�E���h�̃|�C���^
};

#endif