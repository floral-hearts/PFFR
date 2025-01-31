#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR psCmdLine, int nCmdShow) {
    WNDCLASS pffrWndInfo;
    HWND pffrWnd;
    MSG msg;

    pffrWndInfo.style = CS_HREDRAW | CS_VREDRAW;
    pffrWndInfo.lpfnWndProc = DefWindowProc;
    pffrWndInfo.cbClsExtra = 0;
    pffrWndInfo.cbWndExtra = 0;
    pffrWndInfo.hInstance = hInstance;
    pffrWndInfo.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    pffrWndInfo.hCursor = LoadCursor(NULL, IDC_ARROW);
    pffrWndInfo.hbrBackground = GetStockObject(NULL_BRUSH);
    pffrWndInfo.lpszClassName = TEXT("pffrWndInfo");
    if(!RegisterClass(&pffrWndInfo)) {
        MessageBox(NULL, TEXT("create pffrWndInfo"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
        return 1;
    }

    pffrWnd = CreateWindowEx(
        WS_EX_TOOLWINDOW,
        TEXT("pffrWndInfo"),
        TEXT("pffr"),
        WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
        100, 100, 200, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if(!pffrWnd) {
        MessageBox(NULL, TEXT("create pffrWndInfo"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
        return 1;
    }
    ShowWindow(pffrWnd, SW_SHOW);

    while(1) {
        GetMessage(&msg, pffrWnd, 0, 0);
        if(msg.message == WM_LBUTTONUP) break;
        DispatchMessage(&msg);
    }

    return MessageBox(NULL, TEXT("fin"), TEXT("pause"), MB_YESNO) == IDYES ? 0 : 1;
}
