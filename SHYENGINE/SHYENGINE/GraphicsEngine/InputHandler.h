#pragma once
#include <Windows.h>
#include <iostream>
#include <array>
#include <windowsx.h>

enum eKeyCode
{
    A = 'A',
    B = 'B',
    C = 'C',
    D = 'D',
    E = 'E',
    F = 'F',
    G = 'G',
    H = 'H',
    I = 'I',
    J = 'J',
    K = 'K',
    L = 'L',
    M = 'M',
    N = 'N',
    O = 'O',
    P = 'P',
    Q = 'Q',
    R = 'R',
    S = 'S',
    T = 'T',
    U = 'U',
    W = 'W',
    V = 'V',
    X = 'X',
    Y = 'Y',
    Z = 'Z',
    LMB = VK_LBUTTON,
    RMB = VK_RBUTTON,
    MMB = VK_MBUTTON
};

class InputHandler
{
public:
	static bool IsKeyDown(const int aKeyCode);
    static bool IsKeyUp(const int aKeyCode);
    static bool IsKeyPressed(const int aKeyCode);
	static POINT GetMousePosition();
	static POINT GetDeltaMousePosition();
    static short GetMouseWheelDelta();
	static bool UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam);
	static void UpdateMousePos(LPARAM lParam);
	static void UpdateInput();

private:
	static POINT myCurrentMousePos;
    static POINT myPreviousMousePos;
    static short myWheelStatus;
    static std::array<bool, 256> myCurrentState;
    static std::array<bool, 256> myPreviousState;
};

