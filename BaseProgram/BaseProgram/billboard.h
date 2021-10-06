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
	CBillboard(PRIORITY Priority = PRIORITY_EFFECT);	// �R���X�g���N�^
	~CBillboard() {}									// �f�X�g���N�^
	virtual void Draw(void);							// �`�揈��
	
private:
	void SetBlend(bool bBlend)	{ m_bBlend = bBlend; }	// ���Z����

private:
	bool m_bBlend;				// ���Z����
};

#endif