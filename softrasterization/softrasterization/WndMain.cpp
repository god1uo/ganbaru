#include <Windows.h>
#include "Canvas.h"
#include "Model.h"

static HWND hWnd = nullptr;
static HDC hDC = nullptr;
static HDC hMem = nullptr;
Canvas* canvas = nullptr;
Model* model = nullptr;
int WindowWidth = 800;
int WindowHeight = 800;


Point v2p(const vec3& v) {
	return { (float)v[0],(float)v[1],(float)v[2]};
}

LRESULT CALLBACK WindowProc(HWND hWnd, unsigned int uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}

void Render() {

	canvas->ClearScreenBuffer();
	for (int i = 0; i < model->nfaces(); ++i) {
		canvas->DrawTriangle(v2p(model->vert(i, 0)), v2p(model->vert(i, 1)), v2p(model->vert(i, 2)));
	}

	BitBlt(hDC, 0, 0, WindowWidth, WindowHeight, hMem, 0, 0, SRCCOPY);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prehinstance, PSTR cmdLine, int nCmdShow) {

	WNDCLASSEX wcex = { 0 };//初始化窗口数据
	wcex.cbSize = sizeof WNDCLASSEX;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hIcon = nullptr;
	wcex.hIconSm = nullptr;
	wcex.lpszClassName = L"MySoftRaterization";
	wcex.lpszMenuName = nullptr;
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WindowProc;
	if (!RegisterClassEx(&wcex)) {
		MessageBox(nullptr, L"Regist Wrong!!!", L"Tip", 0);
		return -1;
	}
	RECT Rect = { 0,0,WindowWidth,WindowHeight };
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);
	int Width = Rect.right - Rect.left;
	int Height = Rect.bottom - Rect.top;

	hWnd = CreateWindowEx(0, L"MySoftRaterization", L"MySoftRaterization", WS_OVERLAPPEDWINDOW, (GetSystemMetrics(SM_CXSCREEN) - Width) / 2, (GetSystemMetrics(SM_CYSCREEN) - Height) / 2, Width, Height, nullptr, nullptr, hinstance, nullptr);
	if (nullptr == hWnd) {
		MessageBox(nullptr, L"Regist Wrong!!!", L"Tip", 0);
		return -1;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	void* bmpBuffer = nullptr;
	hDC = GetDC(hWnd);
	hMem = CreateCompatibleDC(hDC);

	BITMAPINFO bmpInfo;//创建位图
	auto& Header = bmpInfo.bmiHeader;
	Header.biSize = sizeof BITMAPINFO;
	Header.biWidth = Width;
	Header.biHeight = Height;
	Header.biPlanes = 1;
	Header.biBitCount = 32;
	Header.biCompression = BI_RGB;
	Header.biSizeImage = 0;
	Header.biXPelsPerMeter = 0;
	Header.biYPelsPerMeter = 0;
	Header.biClrUsed = 0;
	Header.biClrImportant = 0;
	HBITMAP hBmp = CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, (void**)&bmpBuffer, 0, 0);
	SelectObject(hMem, hBmp);
	memset(bmpBuffer, 0, Width * Height * 4);
	canvas = new Canvas(Width, Height, (Color*)bmpBuffer);

	MSG msg = { 0 };

	model = new Model("D:/ganbaru/car/Car.obj");



	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			Render();
		}
	}
	delete canvas;
	delete model;
	return 0;
}