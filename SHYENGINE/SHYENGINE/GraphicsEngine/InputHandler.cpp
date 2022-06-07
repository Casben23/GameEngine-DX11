#include "GraphicsEngine.pch.h"
#include "InputHandler.h"

POINT InputHandler::myCurrentMousePos;
POINT InputHandler::myPreviousMousePos;
short InputHandler::myWheelStatus;
std::array<bool, 256> InputHandler::myCurrentState;
std::array<bool, 256> InputHandler::myPreviousState;
bool InputHandler::IsKeyDown(const int aKeyCode)
{
    bool isDown = false;
    if (myCurrentState[aKeyCode] == true && myPreviousState[aKeyCode] == false)
    {
        isDown = true;
    }

    return isDown;
}

bool InputHandler::IsKeyUp(const int aKeyCode)
{
    bool isUp = false;
    if (myCurrentState[aKeyCode] == false && myPreviousState[aKeyCode] == true)
    {
        isUp = true;
    }

    return isUp;
}

bool InputHandler::IsKeyPressed(const int aKeyCode)
{
    bool isDown = false;
    if (myCurrentState[aKeyCode] == true)
    {
        isDown = true;
    }

    return isDown;
}

POINT InputHandler::GetMousePosition()
{
    return myCurrentMousePos;
}

POINT InputHandler::GetDeltaMousePosition()
{
    POINT vector;
    vector.x = myCurrentMousePos.x - myPreviousMousePos.x;
    vector.y = myCurrentMousePos.y - myPreviousMousePos.y;
    return vector;
}

short InputHandler::GetMouseWheelDelta()
{
    return myWheelStatus;
}

bool InputHandler::UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam)
{
    bool messageHandler = false;
    switch (message)
    {
        case WM_KEYDOWN:
            messageHandler = true;
            myCurrentState[wParam] = true;
            myPreviousState[wParam] = (lParam & 0x40000000);
            break;
        case WM_KEYUP:
            messageHandler = true;
            myCurrentState[wParam] = false;
            myPreviousState[wParam] = (lParam & 0x40000000);
            break;
        case WM_LBUTTONDOWN:
            messageHandler = true;
            myCurrentState[VK_LBUTTON] = true;
            myPreviousState[VK_LBUTTON] = false;
            break;
        case WM_LBUTTONUP:
            messageHandler = true;
            myCurrentState[VK_LBUTTON] = false;
            myPreviousState[VK_LBUTTON] = true;
            break;
        case WM_RBUTTONUP:
            messageHandler = true;
            myCurrentState[VK_RBUTTON] = false;
            myPreviousState[VK_RBUTTON] = true;
            break;
        case WM_RBUTTONDOWN:
            messageHandler = true;
            myCurrentState[VK_RBUTTON] = true;
            myPreviousState[VK_RBUTTON] = false;
            break;
        case WM_MBUTTONUP:
            messageHandler = true;
            myCurrentState[VK_MBUTTON] = false;
            myPreviousState[VK_MBUTTON] = true;
            break;
        case WM_MBUTTONDOWN:
            messageHandler = true;
            myCurrentState[VK_MBUTTON] = true;
            myPreviousState[VK_MBUTTON] = false;
            break;
        case WM_MOUSEWHEEL:
            messageHandler = true;
            myWheelStatus = GET_WHEEL_DELTA_WPARAM(wParam);
            break;
        case WM_MOUSEMOVE:
            UpdateMousePos(lParam);
            break;
        default:
            break;
    }
    return messageHandler;
}

void InputHandler::UpdateMousePos(LPARAM lParam)
{
    myCurrentMousePos.x = GET_X_LPARAM(lParam);
    myCurrentMousePos.y = GET_Y_LPARAM(lParam);
}

void InputHandler::UpdateInput()
{
    for (int i = 0; i < myPreviousState.size(); i++)
    {
        myPreviousState[i] = myCurrentState[i];
    }
    myPreviousMousePos.x = myCurrentMousePos.x;
    myPreviousMousePos.y = myCurrentMousePos.y;

}
