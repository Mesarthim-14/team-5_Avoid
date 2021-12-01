#ifndef _CAUTION_BOSS_BULLET_UI_H_
#define _CAUTION_BOSS_BULLET_UI_H_
//=====================================================================
//
// �{�X�̒e�̌x��UI [caution_boss_bullet_ui.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "scene2d.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CCautionBossBulletUi : public CScene2D
{
public:
    CCautionBossBulletUi(PRIORITY priority);  // �R���X�g���N�^
    ~CCautionBossBulletUi();                  // �f�X�g���N�^

    static CCautionBossBulletUi * Create();     // �C���X�^���X����
    HRESULT Init()override;                     // ����������
    void Uninit()override;                      // �I������
    void Update()override;                      // �X�V����
    void Draw()override;                        // �`�揈��

    inline void SetBulletPos(const D3DXVECTOR3& pos) { m_BulletPos = pos; } // �e�̈ʒu�擾

private:
    // private�֐�
    void Rotate();                                              // ��]
    void CalDistance();                                         // �����𑪂�
    void Blinking();                                            // �_��
    void JudgeAngle(const float& fCamera, const float& fAngle); // �p�x�̌v�Z

    bool m_bDraw;               // �`��t���O
    float m_fAngle;             // �p�x
    D3DXVECTOR3 m_BulletPos;    // �e�̈ʒu
    bool m_bBlinking;           // �_�Ńt���O
};


#endif