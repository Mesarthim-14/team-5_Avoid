#ifndef _SKINMESH_MODEL_H_
#define _SKINMESH_MODEL_H_
//=============================================================================
//
// �X�L�����b�V���p���f���N���X [skinmesh_model.h]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "xfile.h"
#include "skinmesh.h"
#include "model_info.h"

//=============================================================================
// �O���錾
//=============================================================================
class CModelInfo;
class IHighLevelAnimController;

//=============================================================================
// ���f���N���X
//=============================================================================
class CSkinmeshModel : public CScene
{
public:

    //���f�����O
    enum MODEL
    {
        MODEL_PLAYER_10 = 0,        //�X���C���P�O���̏��
        MODEL_PLAYER_50,            //�X���C���T�O���̏��
        MODEL_PLAYER_100,           //�X���C���P�O�O���̏��
        MODEL_ENEMY_KRAKEN_HEAD,    // �N���[�P��
        MODEL_MAX
    };
    CSkinmeshModel(PRIORITY Priority = PRIORITY_EFFECT);    // �R���X�g���N�^
    ~CSkinmeshModel();

    HRESULT Init();     // ����������
    void Uninit();      // �I������
    void Update();      // �X�V����
    void Draw();        // �`�揈��
    static CSkinmeshModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL modelNum);    // �C���X�^���X����
    void SetModelNumber(MODEL model);
    inline IHighLevelAnimController * GetHLcontroller()const    { return m_HLcontroller; };
    inline void SetPos(const D3DXVECTOR3 &pos)                  { m_pModelInfo->SetPos(pos); }  // ���݂̍��W���
    inline void SetRot(const D3DXVECTOR3 &rot)                  { m_pModelInfo->SetRot(rot); }  // �p�x���
    inline void IsDraw(bool bIsDraw)                            { m_bIsDraw = bIsDraw; };       // �`�悷�邩
    inline UINT MaxAction()const                                { return m_pAnimetionController->GetMaxNumAnimationSets(); }

protected:
    // Set�֐�
    inline void SetMove(const D3DXVECTOR3 &move)       { m_move = move; }              // �ړ��ʂ̐ݒ�
    inline void SetSize(const D3DXVECTOR3 &size)       { m_size = size; }              // �T�C�Y�̐ݒ�
    inline void SetTexPattern(const int &TexPattern)   { m_nTexPattern = TexPattern; } // �e�N�X�`���̃p�^�[��
    inline void SetLife(const int &nLife)              { m_nLife = nLife; }            // ���C�t�̐ݒ�
    inline void SetScale(const D3DXVECTOR3 &scale)     { m_scale = scale; }            // �g�嗦

    // Get�֐�
    inline D3DXVECTOR3 &GetMove()              { return m_move; }           // �ړ��ʂ̏��
    inline D3DXVECTOR3 GetSize()const          { return m_size; }           // �T�C�Y�̐ݒ�
    inline int GetTexPattern()const            { return m_nTexPattern; }    // �e�N�X�`��
    inline int GetLife()const                  { return m_nLife; }          // ���C�t�̐ݒ�
    inline CModelInfo* GetModelInfo()const     { return m_pModelInfo; }     // ���f���̏��

private:
    // private�֐�
    void HasPtrDelete();    // �ێ��|�C���^�̊J������
    void CreateInfoPtr();   // ���̃|�C���^����

    // �����o�ϐ�
    CModelInfo* m_pModelInfo;                           // ���f���̏��
    D3DXVECTOR3 m_move;                                 // �ړ���
    D3DXVECTOR3 m_size;                                 // �T�C�Y
    D3DXVECTOR3 m_scale;                                // �g�嗦
    bool m_bIsDraw;                                     // �`�悷�邩
    int m_nTexPattern;                                  // �e�N�X�`���̃p�^�[����
    int m_nLife;                                        // ���C�t
    ID3DXAnimationController * m_pAnimetionController;  //�A�j���[�V�����R���g���[���[
    SkinMesh::SMD3DXFRAME *m_pRootFrame;                // ���[�g�t���[��
    std::vector<SkinMesh::SMD3DXMESHCONTAINER*> m_cont; // SMD3DXMESHCONTAINER(���b�V��)�֘A�̏���ۑ��p
    std::vector<D3DXBONECOMBINATION*> m_combs;          //�{�[���R���r�l�[�V�����e�[�u���̃|�C���^�擾
    IHighLevelAnimController * m_HLcontroller;          //�n�C���x���A�j���[�V�����R���g���[���[
    static const char* m_aParam[MODEL_MAX];             //���f���p�X��
    MODEL m_ModelNum;                                   // ���f���̖��O
};
#endif 