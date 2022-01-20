#ifndef _CONTROL_UI_H_
#define _CONTROL_UI_H_
//=============================================================================
//
// �����UI�N���X [control_ui.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene2d.h"

//=========================================================================
// �O���錾
//=========================================================================

//=========================================================================
// �N���X��`
//=========================================================================
class CControlUi : public CScene2D
{
public:
    CControlUi(PRIORITY = PRIORITY_0); // �R���X�g���N�^
    ~CControlUi();                     // �f�X�g���N�^

    static CControlUi *Create();   // �C���X�^���X����
    HRESULT Init();             // ����������
    void Uninit();              // ����������
    void Update();              // �X�V����
    void Draw();                // �`��
    void SwitchTexture(const bool& bFlag);       // �e�N�X�`���̕ύX
    inline void SetDraw(const bool& bFlag) { m_bDraw = bFlag; }      // �`��̐ݒ�

private:
    bool m_bDraw;
    bool m_bTex;
};

#endif