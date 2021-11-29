#ifndef _NPC_SENTENCE_ENEMY1_H_
#define _NPC_SENTENCE_ENEMY1_H_
//=============================================================================
//
// NPC�̕���(�G�l�~�[1) [npc_sentence_enemy1.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "billboard.h"

class CPolygon;
//=============================================================================
// �N���X��`
//=============================================================================
class CNpcSentenceEnemy1 : public CBillboard
{
public:
    CNpcSentenceEnemy1();    // �R���X�g���N�^
    ~CNpcSentenceEnemy1();   // �f�X�g���N�^

    static CNpcSentenceEnemy1* Create();    // �C���X�^���X����
    HRESULT Init();                         // ����������
    void Uninit();                          // �I������
    void Update();                          // �X�V����
    void Draw();                            // �`��

private:
    //�@���}�b�v
    LPDIRECT3DTEXTURE9 m_pTexture;
    LPDIRECT3DSURFACE9 m_pSurface;
    vector<CPolygon*> m_pPolygon;
};
#endif
