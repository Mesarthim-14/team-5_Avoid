//=============================================================================
//
// É}ÉEÉXÇÃèàóù [mouse.h]
// Author : ó—êÏé—óúâƒ
//
//=============================================================================

#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_
#include "input.h"
#include "main.h"

class CMouse : public CInput
{
public:
    CMouse();
    ~CMouse();

    typedef enum
    {
        MOUSE_LEFT = 0,
        MOUSE_RIGHT,
        MOUSE_CENTER,
        MOUSE_MAX
    } MOUSE;

    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit(void);
    void Update(void);

    bool GetKeyPress(int nkey);
    bool GetButtonTrigger(int nkey);

private:
    DIMOUSESTATE2 m_State;
};

#endif
