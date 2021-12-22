#ifndef _SWIRL_SCAFFOLD_H_
#define _SWIRL_SCAFFOLD_H_
//=============================================================================
//
// �Q�̑���N���X [swirl_scaffold.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene.h"

//=========================================================================
// �O���錾
//=========================================================================
class CSwirlScaffoldObject;

//=========================================================================
// �N���X��`
//=========================================================================
class CSwirlScaffold : public CScene
{
public:

    CSwirlScaffold(PRIORITY = PRIORITY_MAP); // �R���X�g���N�^
    ~CSwirlScaffold();                              // �f�X�g���N�^

    static CSwirlScaffold *Create(const D3DXVECTOR3 &pos);  // �C���X�^���X����
    HRESULT Init();                                         // ����������
    void Uninit();                                          // �I������
    void Update();                                          // �X�V����
    void Draw();                                            // �`�揈��

private:
    enum
    {
        MAX_OBJECT = 2,    // �o���I�u�W�F�N�g�̍ő吔
    };

    // private�֐�
    void RotateObject();                        // ��]
    void CreateObject();  // �I�u�W�F�N�g�̐���

    // �����o�ϐ�
    CSwirlScaffoldObject* m_pObject[MAX_OBJECT];
    D3DXVECTOR3 m_pos;
    float m_fAngle;
};

#endif