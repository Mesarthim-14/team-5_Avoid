#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// �e�N�X�`���̊Ǘ��w�b�_�[ [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
//�N���X�錾
//=============================================================================
class CTexture
{
public:
    // �e�N�X�`���̎��
    enum TEXTURE_TYPE_NUM
    {
        TEXTURE_TYPE_NUM_NONE = -1,         // �����l
        TEXTURE_TYPE_NUM_NORMAL,            // �ʏ�e�N�X�`��
        TEXTURE_TYPE_NUM_SEPARATE,          // �����e�N�X�`��
        TEXTURE_TYPE_NUM_VOLUME,            // �{�����[���e�N�X�`��
        TEXTURE_TYPE_NUM_CUBE,              // �L���[�u�e�N�X�`��
        TEXTURE_TYPE_NUM_MAX                // �ő�l
    };

    // �e�N�X�`���̔ԍ��̗񋓌^
    enum TEXTURE_TYPE
    {
        TEXTURE_NUM_NONE = -1,              // �����l �g���Ƃ�-1�ɂ��Ă�������
        TEXTURE_NUM_TEST,                   // �e�X�g�e�N�X�`��
        TEXTURE_NUM_PARTICLE,               // �p�[�e�B�N���e�N�X�`��
        TEXTURE_NUM_GAUGE,                  
        TEXTURE_NUM_GAUGEBAR,               
        TEXTURE_NUM_E_KEY,                  // E�L�[
        TEXTURE_NUM_MESSAGE_BACK,           // ���b�Z�[�W�w�i
        TEXTURE_NUM_MAX                     
    };

    // �A�j���[�V�������s���e�N�X�`���̗񋓌^
    enum SEPARATE_TEX_TYPE
    {
        SEPARATE_TEX_NONE = -1,     // �����l �g���Ƃ�-1�ɂ��Ă�������
        SEPARATE_TEX_TEST,          // �e�X�g�A�j���[�V����
        SEPARATE_TEX_MAX            // �ő�l
    };

    // �A�j���[�V�������s���e�N�X�`���̍\���̏��
    struct SEPARATE_TEX_INFO
    {
        LPDIRECT3DTEXTURE9 pSeparateTexture;    // �����e�N�X�`���ւ̃|�C���^
        SEPARATE_TEX_TYPE type;                 // �e�N�X�`���̎��
        INT_VERTEX_2D m_TexInfo;                // �e�N�X�`���̕������A����
        bool bLoop;                             // ���[�v���邩
    };

    // �{�����[���e�N�X�`���̗񋓌^
    enum VOLUME_TEX_TYPE
    {
        VOLUME_TEX_NONE = 0,    // �����l �g���Ƃ�-1�ɂ��Ă�������
        VOLUME_TEX_MAX          // �ő�l
    };

    // �L���[�u�e�N�X�`���̗񋓌^
    enum CUBE_TEX_TYPE
    {
        CUBE_TEX_NONE = 0,      // �����l �g���Ƃ�-1�ɂ��Ă�������
        CUBE_TEX_MAX            // �ő�l
    };

    CTexture();     // �R���X�g���N�^
    ~CTexture();    // �f�X�g���N�^

    static CTexture *Create();  // �C���X�^���X����
    void LoadAll();             // �S�Ẵ��[�h
    void UnLoadAll();           // �S�ẴA�����[�h

    LPDIRECT3DTEXTURE9 GetTexture(const TEXTURE_TYPE &Tex_Type);                    // �e�N�X�`���̏��
    LPDIRECT3DTEXTURE9 GetSeparateTexture(const SEPARATE_TEX_TYPE &SepaTex_Type);   // �����e�N�X�`�����
    INT_VERTEX_2D GetSparateTexInfo(const SEPARATE_TEX_TYPE &SepaTex_Type);         // �����e�N�X�`���@UV�̖����擾
    bool GetSparateTexLoop(const SEPARATE_TEX_TYPE &SepaTex_Type);                  // ���[�v���邩
    LPDIRECT3DVOLUMETEXTURE9 GetVolumeTexture(const VOLUME_TEX_TYPE &Tex_Type);     // �{�����[���e�N�X�`���̏��
    LPDIRECT3DCUBETEXTURE9 GetCubeTexture(const CUBE_TEX_TYPE &Tex_Type);           // �L���[�u�e�N�X�`���̏��

private:
    // private�֐�
    HRESULT SetTextureName();   // �e�N�X�`�����̐ݒ�

    // �ʏ�e�N�X�`��
    HRESULT NormalTexLoad();    // �e�N�X�`�����[�h
    void NormalTexUnLoad();     // �e�N�X�`���A�����[�h
    // �����e�N�X�`��
    HRESULT SeparateTexLoad();  // �����e�N�X�`�����[�h
    void SeparateTexUnLoad();   // �����e�N�X�`���A�����[�h
    // �{�����[���e�N�X�`��
    HRESULT VolumeTexLoad();    // �{�����[���e�N�X�`�����[�h
    void VolumeTexUnLoad();     // �{�����[���e�N�X�`���A�����[�h
    // �L���[�u�e�N�X�`��
    HRESULT CubeTexLoad();      // �L���[�u�e�N�X�`�����[�h
    void CubeTexUnLoad();       // �L���[�u�e�N�X�`���A�����[�h

    // �����o�ϐ�
    LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];            // �e�N�X�`���̃|�C���^
    SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
    {
        nullptr, CTexture::SEPARATE_TEX_TEST, {8, 10}, true,
    };
    LPDIRECT3DVOLUMETEXTURE9 m_pVolumeTexture[VOLUME_TEX_MAX];  // �{�����[���e�N�X�`��
    LPDIRECT3DCUBETEXTURE9 m_pCubeTexture[CUBE_TEX_MAX];        // �L���[�u�e�N�X�`��
    vector<string> m_aTexFileName[TEXTURE_TYPE_NUM_MAX];        // �e�N�X�`���̖��O
};
#endif
