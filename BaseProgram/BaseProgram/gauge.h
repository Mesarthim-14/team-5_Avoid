#ifndef _GAUGE_H_
#define _GAUGE_H_
//=====================================================================
//
//    �Q�[�W����[gauge.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "scene2d.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CGauge : public CScene2D
{
public:
    CGauge();
    ~CGauge();
    //========================
    // �����o�֐�
    //========================
    static CGauge * Create();
    HRESULT Init();
    void Uninit();
    void Update();
    void Draw();

    static void SetDown(const float &down)    { m_fSave = down; }       //�ǂꂾ���㉺���邩��ݒ�
    static void SetHitDown(const bool &hit)   { m_bHitDown = hit; }     //��������������Ă���
    static void SetHitUp(const bool &hit)     { m_bHitUp = hit; }       //�グ����������Ă���
    float GetHP()                             { return m_fSave; }       //�ǂꂾ���㉺���邩�̏��������Ă���

private:
    void SetVertexGauge();  // �Q�[�W���Z����
    void SetDownUp();       // �e�X�g���鏈��

    //========================
    // �����o�ϐ�
    //========================
    float m_fDown;              // ����
    float m_fUp;                // ������
    static float m_fSave;       // ����ʂ��m��
    static float m_fHP;         // HP
    static bool m_bHitDown;     // �q�b�g��������
    static bool m_bHitUp;       // �q�b�g���オ��
};


#endif // !_GAUGE_H_