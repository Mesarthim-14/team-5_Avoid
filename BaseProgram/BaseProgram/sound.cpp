//================================================
//
// �T�E���h���� [sound.h]
// Author : Konishi Yuuto
//
//================================================

//================================================
// �C���N���[�h
//================================================
#include "sound.h"

//====================================================
//�ÓI�����o�ϐ��錾
//====================================================
CSound::PARAM CSound::m_aParam[SOUND_LABEL_MAX] =
{
    { "data/Sound/BGM/01_Title.wav", SOUND_LOOP_ON },           // �^�C�g�� 
    { "data/Sound/BGM/02_Play.wav", SOUND_LOOP_ON },            // �Q�[�� 
    { "data/Sound/BGM/03_Result.wav", SOUND_LOOP_ON },          // ���U���g 
    { "data/Sound/BGM/04_Boss.wav", SOUND_LOOP_ON },            // �{�X 
    { "data/Sound/SE/01_Select.wav", SOUND_LOOP_OFF },         // �I�� 
    { "data/Sound/SE/02_Announcement.wav", SOUND_LOOP_OFF },   // ���ʔ��\ 
    { "data/Sound/SE/03_Text.wav", SOUND_LOOP_OFF },           // �e�L�X�g�i�� 
    { "data/Sound/SE/04_Jump.wav", SOUND_LOOP_OFF },           // �W�����v 
    { "data/Sound/SE/05_Superjump.wav", SOUND_LOOP_OFF },      // �X�[�p�[�W�����v
    { "data/Sound/SE/06_Diving.wav", SOUND_LOOP_OFF },         // ���  
    { "data/Sound/SE/07_Cannonhit.wav", SOUND_LOOP_OFF },      // ��C 
    { "data/Sound/SE/08_Caveat.wav", SOUND_LOOP_OFF },         // �x���� 
    { "data/Sound/SE/09_Walk1.wav", SOUND_LOOP_OFF },          // ���� 
    { "data/Sound/SE/10_Checkpoint.wav", SOUND_LOOP_OFF },     // �`�F�b�N�|�C���g
    { "data/Sound/SE/11_Enemynoticed.wav", SOUND_LOOP_OFF },   // �G�ɋC�Â��ꂽ  
    { "data/Sound/SE/12_Cannonfiring.wav", SOUND_LOOP_OFF },   // ��C���� 
    { "data/Sound/SE/13_Playerdamage.wav", SOUND_LOOP_OFF },   // �_���[�W 
    { "data/Sound/SE/14_Bossscream.wav", SOUND_LOOP_OFF },     // ���� 
    { "data/Sound/SE/15_Waterfell2.wav", SOUND_LOOP_OFF },      // ���� 
    { "data/Sound/SE/16_Recovery.wav", SOUND_LOOP_OFF },       // �q�[�� 
    { "data/Sound/SE/17_Jumpcharge.wav", SOUND_LOOP_OFF },     // �W�����v�`���[�W
    { "data/Sound/SE/18_Bulletvomiting.wav", SOUND_LOOP_OFF }, // ����  
    { "data/Sound/SE/19_Marlindamage.wav", SOUND_LOOP_OFF },   // �������_���[�W 
};

//================================================
//�R���X�g���N�^
//================================================
CSound::CSound()
{
    m_pXAudio2 = nullptr;                                   // XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
    m_pMasteringVoice = nullptr;                            // �}�X�^�[�{�C�X
    memset(m_apSourceVoice, 0, sizeof(m_apSourceVoice));    // �\�[�X�{�C�X
    memset(m_apDataAudio, 0, sizeof(m_apDataAudio));        // �I�[�f�B�I�f�[�^
    memset(m_aSizeAudio, 0, sizeof(m_aSizeAudio));
}

//================================================
//�f�X�g���N�^
//================================================
CSound::~CSound()
{

}

//================================================
// �C���X�^���X����
//================================================
CSound * CSound::Create()
{
    // �������m��
    CSound *pSound = new CSound;
    if (pSound)
    {
        // ����������
        pSound->Init();
    }

    return pSound;
}

//================================================
//����������
//================================================
HRESULT CSound::Init()
{
    HRESULT hr;

    // COM���C�u�����̏�����
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    // XAudio2�I�u�W�F�N�g�̍쐬
    hr = XAudio2Create(&m_pXAudio2, 0);
    if (FAILED(hr))
    {
        // COM���C�u�����̏I������
        CoUninitialize();

        return E_FAIL;
    }

    // �}�X�^�[�{�C�X�̐���
    hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
    if (FAILED(hr))
    {
        if (m_pXAudio2)
        {
            // XAudio2�I�u�W�F�N�g�̊J��
            m_pXAudio2->Release();
            m_pXAudio2 = nullptr;
        }

        // COM���C�u�����̏I������
        CoUninitialize();

        return E_FAIL;
    }

    // �T�E���h�f�[�^�̏�����
    for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
    {
        HANDLE hFile;
        DWORD dwChunkSize = 0;
        DWORD dwChunkPosition = 0;
        DWORD dwFiletype;
        WAVEFORMATEXTENSIBLE wfx;
        XAUDIO2_BUFFER buffer;

        // �o�b�t�@�̃N���A
        memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
        memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

        // �T�E���h�f�[�^�t�@�C���̐���
        hFile = CreateFile(m_aParam[nCntSound].m_pFilename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }
        if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        {// �t�@�C���|�C���^��擪�Ɉړ�
            return HRESULT_FROM_WIN32(GetLastError());
        }

        // WAVE�t�@�C���̃`�F�b�N
        hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }
        hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }
        if (dwFiletype != 'EVAW')
        {
            return S_FALSE;
        }

        // �t�H�[�}�b�g�`�F�b�N
        hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }
        hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }

        // �I�[�f�B�I�f�[�^�ǂݍ���
        hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }
        m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
        hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }

        // �\�[�X�{�C�X�̐���
        hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));
        if (FAILED(hr))
        {
            return S_FALSE;
        }

        // �o�b�t�@�̒l�ݒ�
        memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
        buffer.AudioBytes = m_aSizeAudio[nCntSound];
        buffer.pAudioData = m_apDataAudio[nCntSound];
        buffer.Flags = XAUDIO2_END_OF_STREAM;
        buffer.LoopCount = m_aParam[nCntSound].isLoop;

        // �I�[�f�B�I�o�b�t�@�̓o�^
        m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

        // �I�[�f�B�I�o�b�t�@�̓o�^
        m_apSourceVoice[nCntSound]->SetVolume(0.2f);
        //m_apSourceVoice[nCntSound]->SetVolume(0.01f);

        // �t�@�C�����N���[�Y
        CloseHandle(hFile);
    }

    return S_OK;
}

//================================================
//�I������
//================================================
void CSound::Uninit()
{
    // �ꎞ��~
    for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
    {
        if (m_apSourceVoice[nCntSound])
        {
            // �ꎞ��~
            m_apSourceVoice[nCntSound]->Stop(0);

            // �\�[�X�{�C�X�̔j��
            m_apSourceVoice[nCntSound]->DestroyVoice();
            m_apSourceVoice[nCntSound] = nullptr;

            // �I�[�f�B�I�f�[�^�̊J��
            free(m_apDataAudio[nCntSound]);
            m_apDataAudio[nCntSound] = nullptr;
        }
    }

    // �}�X�^�[�{�C�X�̔j��
    m_pMasteringVoice->DestroyVoice();
    m_pMasteringVoice = nullptr;

    if (m_pXAudio2)
    {
        // XAudio2�I�u�W�F�N�g�̊J��
        m_pXAudio2->Release();
        m_pXAudio2 = nullptr;
    }

    // COM���C�u�����̏I������
    CoUninitialize();
}

//================================================
//�Z�O�����g�Đ�(�Đ����Ȃ��~)
//================================================
HRESULT CSound::Play(const SOUND_LABEL &label)
{
    XAUDIO2_VOICE_STATE xa2state;
    XAUDIO2_BUFFER buffer;

    // �o�b�t�@�̒l�ݒ�
    memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
    buffer.AudioBytes = m_aSizeAudio[label];
    buffer.pAudioData = m_apDataAudio[label];
    buffer.Flags = XAUDIO2_END_OF_STREAM;
    buffer.LoopCount = m_aParam[label].isLoop;

    // ��Ԏ擾
    m_apSourceVoice[label]->GetState(&xa2state);
    if (xa2state.BuffersQueued != 0)
    {// �Đ���
     // �ꎞ��~
        m_apSourceVoice[label]->Stop(0);

        // �I�[�f�B�I�o�b�t�@�̍폜
        m_apSourceVoice[label]->FlushSourceBuffers();
    }

    // �I�[�f�B�I�o�b�t�@�̓o�^
    m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

    // �Đ�
    m_apSourceVoice[label]->Start(0);

    return S_OK;
}

//================================================
//�Z�O�����g��~(���x���w��)
//================================================
void CSound::Stop(const SOUND_LABEL &label)
{
    XAUDIO2_VOICE_STATE xa2state;

    // ��Ԏ擾
    m_apSourceVoice[label]->GetState(&xa2state);
    if (xa2state.BuffersQueued != 0)
    {// �Đ���
     // �ꎞ��~
        m_apSourceVoice[label]->Stop(0);

        // �I�[�f�B�I�o�b�t�@�̍폜
        m_apSourceVoice[label]->FlushSourceBuffers();
    }
}
//=============================================================================
// �Z�O�����g��~(�S��)
//=============================================================================
void CSound::StopAll()
{
    // �ꎞ��~
    for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
    {
        if (m_apSourceVoice[nCntSound])
        {
            // �ꎞ��~
            m_apSourceVoice[nCntSound]->Stop(0);
        }
    }
}

//================================================
// �`�����N�̃`�F�b�N
//================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
    HRESULT hr = S_OK;
    DWORD dwRead;
    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD dwBytesRead = 0;
    DWORD dwOffset = 0;

    if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {// �t�@�C���|�C���^��擪�Ɉړ�
        return HRESULT_FROM_WIN32(GetLastError());
    }

    while (hr == S_OK)
    {
        if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, nullptr) == 0)
        {// �`�����N�̓ǂݍ���
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, nullptr) == 0)
        {// �`�����N�f�[�^�̓ǂݍ���
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        switch (dwChunkType)
        {
        case 'FFIR':
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, nullptr) == 0)
            {// �t�@�C���^�C�v�̓ǂݍ���
                hr = HRESULT_FROM_WIN32(GetLastError());
            }
            break;

        default:
            if (SetFilePointer(hFile, dwChunkDataSize, nullptr, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
            {// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
                return HRESULT_FROM_WIN32(GetLastError());
            }
        }

        dwOffset += sizeof(DWORD) * 2;
        if (dwChunkType == format)
        {
            *pChunkSize = dwChunkDataSize;
            *pChunkDataPosition = dwOffset;

            return S_OK;
        }

        dwOffset += dwChunkDataSize;
        if (dwBytesRead >= dwRIFFDataSize)
        {
            return S_FALSE;
        }
    }

    return S_OK;
}

//================================================
// �`�����N�f�[�^�̓ǂݍ���
//================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
    DWORD dwRead;

    if (SetFilePointer(hFile, dwBufferoffset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {// �t�@�C���|�C���^���w��ʒu�܂ňړ�
        return HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, nullptr) == 0)
    {// �f�[�^�̓ǂݍ���
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}