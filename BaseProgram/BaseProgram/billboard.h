#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=====================================================
//
// �r���{�[�h�N���X�w�b�_�[ [billboard.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "scene3D.h"

//=====================================================
// �r���{�[�h�N���X
//=====================================================
class CBillboard : public CScene3D
{
public:
    explicit CBillboard(PRIORITY Priority = PRIORITY_EFFECT);   // �R���X�g���N�^
    virtual ~CBillboard() {}                                    // �f�X�g���N�^
    virtual void Draw();                                        // �`�揈��


private:
    bool m_bBlend;                // ���Z����
};

#endif