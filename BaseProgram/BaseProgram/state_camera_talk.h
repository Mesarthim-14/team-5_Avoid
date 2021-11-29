#ifndef _STATE_CAMERA_TALK_H_
#define _STATE_CAMERA_TALK_H_
//=====================================================================
//
// ��b�J������ԊǗ��N���X [state_camera_talk.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_camera.h"

//=====================================================================
// �O���錾
//=====================================================================
class CCamera;

//=====================================================================
// �N���X��`
//=====================================================================
class CCameraStateTalk : public CCameraState
{
public:
    CCameraStateTalk();                 // �R���X�g���N�^
    ~CCameraStateTalk();                // �f�X�g���N�^

    static CCameraStateTalk* Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);    // �C���X�^���X����
    void Init();            // ����������
    void Update()override;  // �X�V����

private:
    void TrackingTalker(CCamera* &pCamera); // ��C�̕��֌���

    // �����o�ϐ�
    D3DXVECTOR3 m_pos;  // ���W
    D3DXVECTOR3 m_rot;  // �p�x

};
#endif