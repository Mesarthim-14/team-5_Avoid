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
    CGauge(PRIORITY priority);
    ~CGauge();
    //========================
    // �����o�֐�
    //========================
    static CGauge * Create();
    HRESULT Init();
    void Uninit();
    void Update();
    void Draw();

    inline void SetDown(const float &down)    { m_fSave = down; }       //�ǂꂾ���㉺���邩��ݒ�
    inline void SetHitDown(const bool &hit)   { m_bHitDown = hit; }     //��������������Ă���
    inline void SetHitUp(const bool &hit)     { m_bHitUp = hit; }       //�グ����������Ă���
    float GetHP()                             { return m_fSave; }       //�ǂꂾ���㉺���邩�̏��������Ă���

private:
    void SetVertexGauge();  // �Q�[�W���Z����
    void SetDownUp();       // �e�X�g���鏈��

    //========================
    // �����o�ϐ�
    //========================
    float m_fDown;              // ����
    float m_fUp;                // ������
    float m_fSave;       // ����ʂ��m��
    float m_fHP;         // HP
    bool m_bHitDown;     // �q�b�g��������
    bool m_bHitUp;       // �q�b�g���オ��
};

#endif // !_GAUGE_H_