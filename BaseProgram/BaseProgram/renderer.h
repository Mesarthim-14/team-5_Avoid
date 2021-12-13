#ifndef _RENDERER_H_
#define _RENDERER_H_
//=============================================================================
//
// �����_���[���� [renderer.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CToonShader;

//=============================================================================
// �����_���[�N���X
//=============================================================================
class CRenderer
{
public:
    CRenderer();	// �R���X�g���N�^
    ~CRenderer();	// �f�X�g���N�^
    
    HRESULT Init(HWND hWnd, bool bWindow);  // ����������
    void Uninit();                          // �I������
    void Update();                          // �X�V����
    void Draw();                            // �`�揈��
    
    inline void SetDispImGuiInfo(const bool &ImGuiInfo) { m_bDispImGuiInfo = ImGuiInfo; };          // Imgui�\����\���ݒ�
    bool CheckShowImGuiInfo()const                      { return m_bDispImGuiInfo; };               // Imgui���\�����Ă邩�m�F
    
    inline LPDIRECT3DDEVICE9 GetDevice()const   { return m_pD3DDevice; }    // �f�o�C�X���
    inline CToonShader* GetToonShader()const    { return m_pToonShader; }   // �V�F�[�_���

private:
    LPDIRECT3DDEVICE9 m_pD3DDevice; // Device�I�u�W�F�N�g(�`��ɕK�v)
    LPDIRECT3D9	m_pD3D;             // Direct3D�I�u�W�F�N�g
    LPDIRECT3D9 m_pD3DInterface;    // DirectX�C���^�[�t�F�[�X
    D3DFILLMODE m_fillMode;         // ���C���[�t���[��
    bool m_bDispImGuiInfo;          //Imgui�`�悷�邩�ǂ���
    CToonShader* m_pToonShader;     // �g�D�[���V�F�[�_

};

#endif