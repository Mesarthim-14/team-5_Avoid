#ifndef _GAME_H_
#define _GAME_H_
//=======================================================================================
//
// �Q�[���N���X [game.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// �O���錾
//=======================================================================================
class CPlayer;
class CGimmickFactory;
class CKraken;
class CNpcFactory;

//=======================================================================================
// �Q�[���N���X
//=======================================================================================
class CGame : public CModeBase
{
public:
    CGame();        // �R���X�g���N�^
    ~CGame();        // �f�X�g���N�^

    HRESULT Init();     // ����������
    void Uninit();      // �I������
    void Update();      // �X�V����
    void Draw();        // �`�揈��
    inline static float GetGravity()                    { return m_fGravity; };         // �d��
    inline CGimmickFactory* GetGimmickFactory()const    { return m_pGimmickFactory; }   // �M�~�b�N�̏��
    inline CKraken* GetKraken()const                    { return m_pKraken; }           // �N���[�P��
    inline void GameEnd()                               { m_bGameEnd = true; }          // �Q�[���I���t���O
    inline CNpcFactory* GetNpcFactory()const            { return m_pNpcFactory; }       // NPC�t�@�N�g���[

private:
    // private�֐�
    void CreatePlayer();        // �v���C���[�̐����֐�
    void CreateEnemy();         // �G�̐���
    void CreateNPC();           // NPC
    void CreateMap();           // �}�b�v�̐���
    void ShowInfo();            // ���\��
    void JudgeDeadKraken();     // �N���[�P�������񂾂��𔻒�

    // �����o�ϐ�
    CPlayer *m_pPlayer;                 // �v���C���[�̃|�C���^
    CKraken *m_pKraken;                 // �N���[�P���̃|�C���^
    bool m_bGameEnd;                    // �Q�[���̃G���h�t���O
    LPD3DXFONT m_pFont;                 // �f�o�b�N�p�t�H���g
    static float m_fGravity;            // �d��
    CGimmickFactory *m_pGimmickFactory; // �M�~�b�N����
    CNpcFactory* m_pNpcFactory;         // NPC�����N���X�|�C���^
};
#endif