#ifndef _SOUND_H_
#define _SOUND_H_
//================================================
//
// �T�E���h���� [sound.h]
// Author : Konishi Yuuto
//
//================================================

//================================================
// �C���N���[�h
//================================================
#include "main.h"
#include "xaudio2.h"

//================================================
// �N���X�錾
//================================================
class CSound
{
public:
    enum SOUND_LABEL
    {
        SOUND_BGM_NONE = -1,            // �����l
        SOUND_BGM_TITLE,                // �^�C�g��
        SOUND_BGM_GAME,                 // �Q�[��
        SOUND_BGM_RESULT,               // ���U���g
        SOUND_BGM_BOSS,                 // �{�X
        SOUND_SE_SELECT,                // �I��
        SOUND_SE_ANNOUNCEMENT,          // ���ʔ��\
        SOUND_SE_TEXT,                  // �e�L�X�g�i��
        SOUND_SE_JUMP,                  // �W�����v
        SOUND_SE_SUPER_JUMP,            // �X�[�p�[�W�����v
        SOUND_SE_AVOID,                 // ���
        SOUND_SE_HIT_CANNON,            // ��C
        SOUND_SE_CAVEAT,                // �x����
        SOUND_SE_WALK,                  // ����
        SOUND_SE_CHECKPOINT,            // �`�F�b�N�|�C���g
        SOUND_SE_ENEMY_NOTICED,         // �G�ɋC�Â��ꂽ
        SOUND_SE_CANNON_FIRING,         // ��C����
        SOUND_SE_DAMAGE,                // �_���[�W
        SOUND_SE_SCREAM,                // ����
        SOUND_SE_WATER_FELL,            // ����
        SOUND_SE_HEEL,                  // �q�[��
        SOUND_SE_JUMP_CHARGE,           // �W�����v�`���[�W
        SOUND_SE_KRAKEN_BULLET_MITING,  // ����
        SOUND_SE_MARLIN_DAMAGE,         // �������_���[�W
        SOUND_LABEL_MAX,
    };

    enum SOUND_LOOP
    {
        SOUND_LOOP_ON = -1,             //���[�v����
        SOUND_LOOP_OFF,                 //���[�v���Ȃ�
    };

    CSound();   // �R���X�g���N�^
    ~CSound();  // �f�X�g���N�^

    static CSound *Create();                // �C���X�^���X����
    HRESULT Init();                         // ����������
    void Uninit();                          // �I������
    HRESULT Play(const SOUND_LABEL &label); // �T�E���h�Đ�
    void Stop(const SOUND_LABEL &label);    // �T�E���h�X�g�b�v
    void StopAll();                         // �S�ẴT�E���h���~

private:
    struct PARAM
    {
        char *m_pFilename;  // �t�@�C����
        SOUND_LOOP isLoop;  // ���[�v���邩�ǂ���
    };

    HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
    HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
    IXAudio2 *m_pXAudio2 = nullptr;                                                                    // XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
    IXAudio2MasteringVoice *m_pMasteringVoice = nullptr;                                               // �}�X�^�[�{�C�X
    IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};                                     // �\�[�X�{�C�X
    BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};                                                      // �I�[�f�B�I�f�[�^
    DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};                                                       // �I�[�f�B�I�f�[�^�T�C�Y

    // �e���f�ނ̃p�����[�^
    static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif