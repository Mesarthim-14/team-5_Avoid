#ifndef _NPC_TEXT_H_
#define _NPC_TEXT_H_
//=============================================================================
//
// NPC�̃e�L�X�g [npc_text.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CNpcText : public CScene
{
public:
    CNpcText(PRIORITY priority = PRIORITY_0);   // �R���X�g���N�^
    virtual ~CNpcText();                        // �f�X�g���N�^

    virtual HRESULT Init();     // ����������
    virtual void Uninit();      // �I������
    virtual void Update();      // �X�V����
    virtual void Draw() {}      // �`�揈��

private:
};
#endif