#include <windows.h>
#include <math.h>
#include <stdint.h>
#include <crtdbg.h>

#define W 800
#define H 600

double seconds = 0;

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_vec3f
{
	double		x;
	double		y;
	double		z;
}				t_vec3f;

t_vec2 proj_vertex(t_vec3f v)
{
	v = (t_vec3f){
		v.x * cos(seconds) - v.y * sin(seconds),
		v.x * sin(seconds) + v.y * cos(seconds),
		v.z,
	};
	v = (t_vec3f){
		v.x * cos(seconds) - v.z * sin(seconds),
		v.y,
		v.x * sin(seconds) + v.z * cos(seconds),
	};
	v.y += sin(seconds);
	v.x += cos(seconds);
	v.z += 10;
	v.x /= v.z;
	v.y /= v.z;
	v.x = v.x * W + W / 2;
	v.y = -v.y * W + H / 2;
	return ((t_vec2){(int)v.x, (int)v.y});
}

void putpixel(uint32_t* pixels, int x, int y)
{
	if (x >= 0 && x < W && y >= 0 && y < H)
		pixels[y * W + x] = 0xffffff;
}

void draw_line(uint32_t* pixels, t_vec2 v1, t_vec2 v2)
{
	int dx = v2.x - v1.x;
	int dy = v2.y - v1.y;
	int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
	double x_inc = dx / (double)steps;
	double y_inc = dy / (double)steps;
	double x = v1.x;
	double y = v1.y;
	for (int i = 0; i < steps; i++) {
		putpixel(pixels, (int)x, (int)y);
		x += x_inc;
		y += y_inc;
	}
}

void draw(uint32_t* pixels)
{
	t_vec2 v[8];

	v[0] = proj_vertex((t_vec3f){ -1, -1, -1});
	v[1] = proj_vertex((t_vec3f){ -1,  1, -1});
	v[2] = proj_vertex((t_vec3f){  1,  1, -1});
	v[3] = proj_vertex((t_vec3f){  1, -1, -1});
	v[4] = proj_vertex((t_vec3f){ -1, -1,  1});
	v[5] = proj_vertex((t_vec3f){ -1,  1,  1});
	v[6] = proj_vertex((t_vec3f){  1,  1,  1});
	v[7] = proj_vertex((t_vec3f){  1, -1,  1});
	memset(pixels, 0, W * H * sizeof(uint32_t));
	for (int i = 0; i < 4; i++) {
		draw_line(pixels, v[i], v[(i + 1) % 4]);
		draw_line(pixels, v[i + 4], v[((i + 1) % 4) + 4]);
		draw_line(pixels, v[i], v[i + 4]);
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmap;
	static BITMAPINFO bmi;
	static uint32_t* pixels;
	static HDC hdcMem;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (uMsg)
	{
	case WM_CREATE:
		bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
		bmi.bmiHeader.biWidth = W;
		bmi.bmiHeader.biHeight = -H;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		hBitmap = CreateDIBSection(0, &bmi, DIB_RGB_COLORS, &pixels, 0, 0);
		hdcMem = CreateCompatibleDC(NULL);
		if (!hBitmap)
			exit(1);
		SelectObject(hdcMem, hBitmap);
		return 0;

	case WM_PAINT:
		draw(pixels);
		hdc = BeginPaint(hwnd, &ps);
		BitBlt(hdc, 0, 0, W, H, hdcMem, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hwnd);
		return 0;

	case WM_DESTROY:
		DeleteDC(hdcMem);
		DeleteObject(hBitmap);
		timeEndPeriod(1);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

double get_seconds_elapsed(LARGE_INTEGER start, LARGE_INTEGER end)
{
	static double inv_frequency;

	if (!inv_frequency)
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		inv_frequency = 1.0 / (double)frequency.QuadPart;
	}
	return ((double)(end.QuadPart - start.QuadPart) * inv_frequency);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	WNDCLASS wc;
	RECT rect;
	DWORD dwStyle;
	HWND hwnd;

	wc = (WNDCLASS){0};
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindowProc,
	wc.hInstance = hInstance,
	wc.lpszClassName = "MyWindowClass",
	RegisterClass(&wc);
	rect = (RECT){0, 0, W, H};
	dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	AdjustWindowRect(&rect, dwStyle, FALSE);
	if (!(hwnd = CreateWindowEx(
		0, wc.lpszClassName, "My window", dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, hInstance, NULL)))
		return 1;
	ShowWindow(hwnd, nCmdShow);

	MSG msg;
	LARGE_INTEGER last_counter, end_counter;
	double seconds_elapsed, target_seconds_per_frame;
	BOOL sleep_is_granular;

	target_seconds_per_frame = 1.0 / 60.0;
	QueryPerformanceCounter(&last_counter);
	sleep_is_granular = (timeBeginPeriod(1) == TIMERR_NOERROR);
	while (TRUE)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return 0;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		InvalidateRect(hwnd, 0, 0);
		UpdateWindow(hwnd);
		QueryPerformanceCounter(&end_counter);
		seconds_elapsed = get_seconds_elapsed(last_counter, end_counter);
		double sleep_margin = 0.001;
		if (seconds_elapsed < (target_seconds_per_frame - sleep_margin))
			if (sleep_is_granular)
				Sleep((DWORD)(((target_seconds_per_frame - sleep_margin) -
					seconds_elapsed) * 1000));
		while (seconds_elapsed < target_seconds_per_frame)
		{
			QueryPerformanceCounter(&end_counter);
			seconds_elapsed = get_seconds_elapsed(last_counter, end_counter);
		}
		_RPTN(0, "ms/frame: %f\n", seconds_elapsed * 1000);
		seconds += target_seconds_per_frame;
		last_counter = end_counter;
	}
	return 0;
}
