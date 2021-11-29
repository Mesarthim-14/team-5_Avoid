#ifndef _NON_PLAYER_CHARACTER_H_
#define _NON_PLAYER_CHARACTER_H_
//=============================================================================
//
// NPC�N���X�w�b�_  [non_player_character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CSkinmeshModel;
class CKeyE;
class CNpcTextEnemy;
class CProductionNpcTalk;

//=============================================================================
// �N���X��`
//=============================================================================
class CNonPlayerCharacter : public CScene
{
public:
    CNonPlayerCharacter(PRIORITY Priority = PRIORITY_CHARACTER); // �R���X�g���N�^
    virtual ~CNonPlayerCharacter();                              // �f�X�g���N�^

    virtual HRESULT Init();             // ����������
    virtual void Uninit();              // �I������
    virtual void Update();              // �X�V����
    virtual void Draw();                // �`�揈��

    // Set�֐�
    inline void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
    inline void SetRot(const D3DXVECTOR3& pos) { m_rot = pos; }

    // Get�֐�
    inline D3DXVECTOR3 GetPos() { return m_pos; }
    inline D3DXVECTOR3 GetRot() { return m_rot; }

private:
    // private�֐�
    void CreateModel();                                                     // ���f������
    void Collision();                                                       // �����蔻��
    void Talk();                                                            // ���b
    void BebinProduction(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);   // ��Ԃ̊J�n
    void EndProduction();                                                   // ��Ԃ̏I��

    // �����o�ϐ�
    D3DXVECTOR3 m_pos;                  // ���W
    D3DXVECTOR3 m_rot;                  // �p�x
    D3DXMATRIX m_mtxWorld;              // ���[���h�}�g���b�N�X
    CSkinmeshModel* m_pSkinmeshModel;   // �X�L�����b�V�����f���|�C���^
    CKeyE* m_pKeyE;                     // E�L�[
    CNpcTextEnemy* m_pText;             // �e�L�X�g�N���X
    bool m_bDead;                       // �b���Ȃ��Ȃ�
    CProductionNpcTalk* m_pProduction;  // ���o�̃|�C���^

};
#endif
