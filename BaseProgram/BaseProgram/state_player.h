#ifndef _STATE_PLAYER_H_
#define _STATE_PLAYER_H_
//=====================================================================
//
//    ��ԊǗ��N���X [state_player.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state.h"

//=====================================================================
// �O���錾
//=====================================================================
class CPlayer;

//=====================================================================
// �N���X��`
//=====================================================================
class CPlayerState : public CState
{
public:
    CPlayerState();     // �R���X�g���N�^
    ~CPlayerState();    // �f�X�g���N�^

protected:
    virtual void SetAnimation(const UINT &animID, const FLOAT &time);               // �A�j���[�V�����ݒ�
    virtual void SetAnimation(const UINT &animID, const FLOAT &time, bool bLoop);   // �A�j���[�V�����ݒ�
    void MoveByKeyboard(CPlayer* &pPlayer);                                         // ���͏���

    // �t���O��Ԃ���
    function<bool(const int&, CPlayerState*)> CounterFunc = [](const int &nLimit, CPlayerState* pState)
    {
        if (nLimit <= pState->m_nCounter++)
        {
            return true;
        }
        return false;
    };

private:
    void SoundUpdate();     // ���̍X�V

    float m_fAngleSpeed;    // �ڕW�����܂Ō������X�s�[�h 
    int m_nCounter;         // �J�E���^
    bool m_bMove[2];        // �ړ��̃t���O
    bool m_Effect;
};
#endif