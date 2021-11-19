//=============================================================================
//
// マウスの処理 [mouse.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "mouse.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CMouse::CMouse()
{
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CMouse::~CMouse()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
    CInput::Init(hInstance, hWnd);
    if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
    {
        return E_FAIL;
    }

    m_pDevice->SetDataFormat(&c_dfDIMouse2);    //ﾏｳｽ用のﾃﾞｰﾀ・ﾌｫｰﾏｯﾄ設定
    m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

    DIPROPDWORD diprop;
    diprop.diph.dwSize = sizeof(diprop);
    diprop.diph.dwHeaderSize = sizeof(diprop.diph);
    diprop.diph.dwObj = 0;
    diprop.diph.dwHow = DIPH_DEVICE;
    diprop.dwData = DIPROPAXISMODE_REL;    // 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）
    m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

    m_pDevice->Acquire();
    return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CMouse::Uninit(void)
{
    //入力デバイス開放
    if (m_pDevice != NULL)
    {
        //キーボードのアクセス権開放
        m_pDevice->Unacquire();
        m_pDevice = NULL;
    }
    CInput::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CMouse::Update(void)
{
    for (int nCount = 0; nCount < 4; nCount++)
    {
        m_State.rgbButtons[nCount] = 0;
    }
    m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_State);

    m_pDevice->Acquire();
}

//=============================================================================
//マウスボタンの状態取得
//=============================================================================
bool CMouse::GetKeyPress(int Mouse)
{
    return (m_State.rgbButtons[Mouse] & 0x80) ? true : false;
}
//=============================================================================
//マウス押された処理
//=============================================================================
bool CMouse::GetButtonTrigger(int nkey)
{
    //前のフレームと今のフレームが違うならtrue;
    static bool prevState[sizeof(m_State.rgbButtons) / sizeof(m_State.rgbButtons[0])];
    bool current = GetKeyPress(nkey);
    bool ret = current && !prevState[nkey];
    prevState[nkey] = current;
    return ret;
}
