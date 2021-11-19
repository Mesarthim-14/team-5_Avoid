#include "main.h"
#include "skinmesh.h"
#include "animation_skinmesh.h"
#include <vector>

bool IHighLevelAnimController::SetAnimationController(ID3DXAnimationController * pAnimCont)
{
    //NULL�`�F�b�N
    if (pAnimCont)
    {
        //�R���e�i�R�s�[
        m_AnimCont = pAnimCont;
        //�T�C�Y�m��
        m_Anim.resize(pAnimCont->GetMaxNumAnimationSets());
        //�A�j���[�V�����Z�b�g�擾
        for (unsigned int size = 0; size < m_Anim.size(); size++)
        {
            pAnimCont->GetAnimationSet(size, &m_Anim[size].pAnimSet);

        }
        m_CurAnimID = 0;
        m_PreAnimID = 0;
        return true;
    }
    else
    {
        return false;
    }
}

bool IHighLevelAnimController::GetAnimationController(ID3DXAnimationController ** ppAnimCont)
{
    //NULL�`�F�b�N
    if (m_AnimCont)
    {
        ppAnimCont = &m_AnimCont;

        return true;
    }
    else
    {
        return false;
    }
}

bool IHighLevelAnimController::SetLoopTime(UINT animID, FLOAT time)
{
    // �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
    if (m_Anim.size() <= animID)
    {
        return false;
    }

    // �g���b�N�X�s�[�h���ߒl���Z�o
    FLOAT DefTime = float(m_Anim[animID].pAnimSet->GetPeriod());
    m_Anim[animID].fLoopTime = time;
    m_Anim[animID].fTrackSpeed = DefTime / time;

    return true;
}

bool IHighLevelAnimController::SetShiftTime(UINT animID, FLOAT interval)
{
    // �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
    if (m_Anim.size() <= animID)
    {
        return false;
    }

    // �V�t�g���Ԃ�o�^
    m_Anim[animID].fShiftTime = interval;

    return true;
}

bool IHighLevelAnimController::ChangeAnimation(UINT animID)
{
    // �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
    if (m_Anim.size() <= animID)
    {
        return false;
    }

    // �قȂ�A�j���[�V�����ł��邩���`�F�b�N
    if (m_CurAnimID == animID)
    {
        return false;
    }

    // ���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾
    D3DXTRACK_DESC TD;   // �g���b�N�̔\��

    m_AnimCont->GetTrackDesc(0, &TD);

    // ���̃A�j���[�V�������g���b�N1�Ɉڍs��
    // �g���b�N�̐ݒ�l���ڍs
    m_AnimCont->SetTrackAnimationSet(1, m_Anim[m_CurAnimID].pAnimSet);
    m_AnimCont->SetTrackDesc(1, &TD);

    // �V�����A�j���[�V�����Z�b�g���g���b�N0�ɐݒ�
    m_AnimCont->SetTrackAnimationSet(0, m_Anim[animID].pAnimSet);

    // �g���b�N0�̃X�s�[�h�̐ݒ�
    m_AnimCont->SetTrackSpeed(0, m_Anim[animID].fTrackSpeed);

    // �g���b�N�̍���������
    m_AnimCont->SetTrackEnable(0, true);
    m_AnimCont->SetTrackEnable(1, true);

    // �E�F�C�g���Ԃ�������
    m_Anim[animID].fCurWeightTime = 0.0f;

    // ���݂̃A�j���[�V�����ԍ���؂�ւ�
    m_PreAnimID = m_CurAnimID;
    m_CurAnimID = animID;

    return true;
}

bool IHighLevelAnimController::AdvanceTime(FLOAT time)
{
    m_Anim[m_CurAnimID].fCurWeightTime += time;

    // ���������ۂ��𔻒�
    if (m_Anim[m_CurAnimID].fCurWeightTime <= m_Anim[m_CurAnimID].fShiftTime)
    {
        // �������B�E�F�C�g���Z�o
        FLOAT Weight = m_Anim[m_CurAnimID].fCurWeightTime / m_Anim[m_CurAnimID].fShiftTime;
        // �E�F�C�g��o�^
        m_AnimCont->SetTrackWeight(0, Weight);       // ���݂̃A�j���[�V����
        m_AnimCont->SetTrackWeight(1, 1 - Weight);   // �O�̃A�j���[�V����
    }
    else
    {
        // �����I�����B�ʏ�A�j���[�V����������Track0�̃E�F�C�g���ő�l��
        m_AnimCont->SetTrackWeight(0, 1);       // ���݂̃A�j���[�V����
        m_AnimCont->SetTrackEnable(1, false);      // �O�̃A�j���[�V�����𖳌��ɂ���
    }

    // ���Ԃ��X�V
    m_AnimCont->AdvanceTime(time, NULL);

    return true;
}