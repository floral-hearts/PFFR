#define TYPE1 0
#define TYPE2 1
#define TYPE3 0

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR psCmdLine, int nCmdShow) {
    WNDCLASS wcStage;
    HWND wStage;
    MSG msg;

    wcStage.style = CS_HREDRAW | CS_VREDRAW;
    wcStage.lpfnWndProc = WndProc;
    wcStage.cbClsExtra = 0;
    wcStage.cbWndExtra = 0;
    wcStage.hInstance = hInstance;
    wcStage.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcStage.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcStage.hbrBackground = GetStockObject(NULL_BRUSH);
    wcStage.lpszMenuName = NULL;
    wcStage.lpszClassName = TEXT("pffrWndInfo");
    if(!RegisterClass(&pffrWndInfo)) {
        MessageBox(NULL, TEXT("create pffrWndInfo"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
        return 1;
    }

    wStage = CreateWindow(
        TEXT("pffrWndInfo"),
        TEXT("pffr"),
#if TYPE1
    	WS_POPUP,
#elif TYPE2
	    WS_OVERLAPPEDWINDOW & ~WS_CAPTION,
#elif TYPE3
    	(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU) & ~WS_CAPTION,
#else
		WS_OVERLAPPED | WS_SYSMENU
#endif
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

    while(GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }

    return MessageBox(NULL, TEXT("fin"), TEXT("pause"), MB_YESNO) == IDYES ? msg.wParam : 1;
}

LRESULT CALLBACK WndProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_RBUTTONUP:
        PostQuitMessage(0);
        return 0;
	}
    return DefWindowProc(hw, msg, wp, lp);
}
