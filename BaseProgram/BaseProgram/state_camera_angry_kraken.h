#ifndef _STATE_CAMERA_ANGRY_KRAKEN_H_
#define _STATE_CAMERA_ANGRY_KRAKEN_H_
//=====================================================================
//
// �N���[�P���{�艉�o�J���� [state_camera_angry_kraken.h]
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
class CCameraStateAngryKraken : public CCameraState
{
public:
    CCameraStateAngryKraken();                  // �R���X�g���N�^
    ~CCameraStateAngryKraken();                 // �f�X�g���N�^
    static CCameraStateAngryKraken* Create();   // �C���X�^���X����

    void Init();            // ����������
    void Update()override;  // �X�V����
private:
    void ViewKraken(CCamera* &pCamera); // �N���[�P�������鏈��
};
#endif