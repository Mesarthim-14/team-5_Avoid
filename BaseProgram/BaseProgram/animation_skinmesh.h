#ifndef IKD_AnimController_H
#define IKD_AnimController_H

#include <d3dx9.h>
#include <vector>

class IHighLevelAnimController
{
public:
    struct HLANIMATION_DESC
    {
        UINT uiAnimID;                 // �A�j���[�V����ID
        ID3DXAnimationSet *pAnimSet;   // �A�j���[�V�����Z�b�g
        FLOAT fLoopTime;               // 1���[�v�̎���
        FLOAT fTrackSpeed;             // �g���b�N�X�s�[�h���ߒl
        FLOAT fShiftTime;              // �V�t�g����ɂ����鎞��
        FLOAT fCurWeightTime;          // ���݂̃E�F�C�g����
    };
    // �A�j���[�V�����R���g���[����ݒ�
    bool SetAnimationController(ID3DXAnimationController *pAnimCont);
    // �A�j���[�V�����R���g���[�����擾
    bool GetAnimationController(ID3DXAnimationController **ppAnimCont);
    // ���[�v���Ԃ�ݒ�
    bool SetLoopTime(UINT animID, FLOAT time);
    // ����J�n�ɂ����鎞�Ԃ�ݒ�
    bool SetShiftTime(UINT animID, FLOAT interval);
    // �A�j���[�V������؂�ւ�
    bool ChangeAnimation(UINT animID);
    // �A�j���[�V�������X�V
    bool AdvanceTime(FLOAT time);

private:
    std::vector<HLANIMATION_DESC> m_Anim;//�A�j���[�V�����f�[�^�ۑ��p
    UINT m_CurAnimID;//���݂̃A�j���[�V����
    UINT m_PreAnimID;//�O��A�j���[�V����
    ID3DXAnimationController * m_AnimCont;//�A�j���[�V�����R���g���[���[
};
#endif