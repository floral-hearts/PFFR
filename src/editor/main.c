#include <windows.h>
#include <stdio.h>
#include <string.h>

DWORD stageH = 400;
DWORD stageV = 200;

LRESULT CALLBACK ExitProc(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ExitButtonProc(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR psCmdLine, int nCmdShow) {
    WNDCLASS wcStage;
    HWND wStage;
    WNDCLASS wcExitButton;
    HWND wExitButton;
    MSG msg;

    wcStage.style = CS_HREDRAW | CS_VREDRAW;
    wcStage.lpfnWndProc = ExitProc;
    wcStage.cbClsExtra = 0;
    wcStage.cbWndExtra = 0;
    wcStage.hInstance = hInstance;
    wcStage.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcStage.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcStage.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcStage.lpszMenuName = NULL;
    wcStage.lpszClassName = TEXT("wcStage");
    if(!RegisterClass(&wcStage)) {
        MessageBox(NULL, TEXT("create pffrWndInfo"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
        return 1;
    }
    wStage = CreateWindow(
        TEXT("wcStage"),
        TEXT("Stage"),
        WS_POPUP | WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, stageH, stageV,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if(!wStage) {
        MessageBox(NULL, TEXT("create pffrWndInfo"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
        return 1;
    }

    wcExitButton.style = CS_HREDRAW | CS_VREDRAW;
    wcExitButton.lpfnWndProc = ExitButtonProc;
    wcExitButton.cbClsExtra = 0;
    wcExitButton.cbWndExtra = 0;
    wcExitButton.hInstance = hInstance;
    wcExitButton.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcExitButton.hCursor = LoadCursor(NULL, IDC_NO);
    wcExitButton.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcExitButton.lpszMenuName = NULL;
    wcExitButton.lpszClassName = TEXT("wcExitButton");
    if(!RegisterClass(&wcExitButton)) {
        MessageBox(NULL, TEXT("create wcExitButton"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
        return 1;
    }
    wExitButton = CreateWindow(
        TEXT("wcExitButton"),
        TEXT("ExitButton"),
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        stageH / 10 * 9, 0, stageH, stageV / 10,
        wStage,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(wStage, SW_SHOW);

    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK ExitProc(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam) {
    if(msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    if(msg == WM_CHAR && wParam == 0x1b) {
        if(MessageBox(NULL, TEXT("destroy this window"), TEXT(""), MB_YESNO) == IDYES) {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hw, msg, wParam, lParam);
}

LRESULT CALLBACK ExitButtonProc(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam) {
    if(msg == WM_LBUTTONUP) {
        PostQuitMessage(0);
        return 0;
    }
}
