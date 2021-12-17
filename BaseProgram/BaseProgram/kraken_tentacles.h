#ifndef _KRAKEN_TENTACLES_H_
#define _KRAKEN_TENTACLES_H_
//=============================================================================
//
// �N���[�P���̐G�� [kraken_tentacles.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"
#include "state_object.h"

//=============================================================================
// �O���錾
//=============================================================================
class CSkinmeshModel;
class CCollisionModelOBB;

//=============================================================================
// �N���X��`
//=============================================================================
class CKrakenTentacles : public CScene
{
public:
    CKrakenTentacles(PRIORITY Priority = PRIORITY_MODEL);    // �R���X�g���N�^
    ~CKrakenTentacles();                                         // �f�X�g���N�^

    static CKrakenTentacles *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);    // �C���X�^���X����
    HRESULT Init();                                                                     // ����������
    void Uninit();                                                                      // �I������
    void Update();                                                                      // �X�V����
    void Draw() {}                                                                      // �`�揈��

private:
    // private�֐�
    void CreateModel();     // ���f���̐���
    void SetTentaclesInfo(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

    // �����o�ϐ�
    CSkinmeshModel *m_pSkinmeshModel;   // �X�L�����b�V�����f���|�C���^
    D3DXVECTOR3 m_pos;                  // ���W
    D3DXVECTOR3 m_rot;                  // �p�x
};
#endif