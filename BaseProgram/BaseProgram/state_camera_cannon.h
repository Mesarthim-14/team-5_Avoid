#ifndef _STATE_CAMERA_CANNON_H_
#define _STATE_CAMERA_CANNON_H_
//=====================================================================
//
//    ��C���J������ԊǗ��N���X [state_camera_cannon.h]
//    Author : Konishi Yuuto
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
class CCameraStateCannon : public CCameraState
{
public:
    CCameraStateCannon();                   // �R���X�g���N�^
    ~CCameraStateCannon();                  // �f�X�g���N�^
    static CCameraStateCannon* Create();    // �C���X�^���X����

    void Init();            // ����������
    void Update()override;  // �X�V����

private:
    void TrackingCannon(CCamera* &pCamera);    // ��C�̕��֌���
};
#endif