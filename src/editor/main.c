#define TYPE1 0
#define TYPE2 1
#define TYPE3 0

#include <windows.h>

DWORD escDownTime = 0;

HWND HWInitialize(WNDPROC lpfnWndProc, HANDLE hInstance, LPCTSTR lpszClassName);
LRESULT CALLBACK ExitProc(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR psCmdLine, int nCmdShow) {
    WNDCLASS wcStage;
    HWND wStage;
	WNDCLASS wcExitButton;
	HWND wExitButton;
    MSG msg;

	wcStage = HWInitialize(ExitProc, hInstance, "wcStage");
    if(!RegisterClass(&wcStage)) {
        MessageBox(NULL, TEXT("create pffrWndInfo"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
        return 1;
    }
    wStage = CreateWindow(
        TEXT("wcStage"),
        TEXT("Stage"),
    	WS_POPUP,
//	    WS_OVERLAPPEDWINDOW & ~WS_CAPTION,
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU) & ~WS_CAPTION,
//        WS_OVERLAPPED | WS_SYSMENU,
        100, 100, 200, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if(!wStage) {
        MessageBox(NULL, TEXT("create pffrWndInfo"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
        return 1;
    }

	wcExitButton = HWInitialize(ExitProc, hInstance, "wcExitButton");
    if(!RegisterClass(&wcExitButton)) {
        MessageBox(NULL, TEXT("create wcExitButton"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
        return 1;
    }
	wExitButton = CreateWindow(
		TEXT("wcExitButton"),
		TEXT("ExitButton"),
		
	)

    ShowWindow(wStage, SW_SHOW);

    while(GetMessage(&msg, NULL, 0, 0)) {
	    TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wPara;
}

HWND HWInitialize(WNDPROC lpfnWndProc, HANDLE hInstance, LPCTSTR lpszClassName) {
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = lpfnWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = lpszClassName;
	return wc;
}

LRESULT CALLBACK ExitProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
    if(msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
	}
	if(msg == WM_KEYDOWN) {
		escDownTime = GetTickCount();
	} else if(msg == WM_CHAR && wp == 0x1b && (GetTickCount() - escDownTime) >= 3) {
		PostQuitMessage(0);
		return 0;
	}
    return DefWindowProc(hw, msg, wp, lp);
}
