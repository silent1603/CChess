#include "base.h"
#include "imgui.h"
#include "glad/glad.h"
#include "imgui_impl_opengl3.h"
#if OS_WINDOWS
#include "glad/glad_wgl.h"
#include "imgui_impl_win32.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        return 0;
    }
    case WM_CLOSE:
    {
        PostQuitMessage(0);
        return 0;
    }

    default:
        break;
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    //Setup Window
    WNDCLASSEX windowClass;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.hInstance = hInst;
    windowClass.lpfnWndProc = WndProc;
    windowClass.style = CS_VREDRAW | CS_HREDRAW;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;

    return 0;
}

#endif