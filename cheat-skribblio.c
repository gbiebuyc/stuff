//
//  Compile: gcc main.c -lgdi32
//

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

HANDLE image;
BITMAP image_info;
HDC hdcMem;
RECT desktop_rect;
uint32_t colors[] = {0xFFF, 0xC1C1C1, 0xEF130B, 0xFF7100, 0xFFE400, 0x00CC00, 0x00B2FF, 0x231FD3, 0xA300BA, 0xD37CAA, 0xA0522D, 0x000, 0x4C4C4C, 0x740B07, 0xC23800, 0xE8A200, 0x005510, 0x00569E, 0x0E0865, 0x550069, 0xA75574, 0x63300D};
#define ARRAYSIZE(a) (sizeof(a) / sizeof(*(a)))
#define R(col) ((col>>0) & 0xff)
#define G(col) ((col>>8) & 0xff)
#define B(col) ((col>>16) & 0xff)
#define BTN_WIDTH_PIXELS 24
#define FIRST_BTN_SCREEN_X 585
#define FIRST_BTN_SCREEN_Y 935
#define RESULT_WIDTH 80
#define RESULT_PX_SPACING 8
#define RESULT_TOP 300
#define RESULT_LEFT 480

int get_matching_color(uint32_t color) {
	int best = 0;
	double best_dist = INFINITY;

	for (int i=0; i<ARRAYSIZE(colors); i++) {
		double dist =
			pow(B(color)-R(colors[i]), 2) +
			pow(G(color)-G(colors[i]), 2) +
			pow(R(color)-B(colors[i]), 2);
		if (dist < best_dist) {
			best_dist = dist;
			best = i;
		}
	}
	return best;
}

int get_btn_x(int i) {
	return (FIRST_BTN_SCREEN_X + (BTN_WIDTH_PIXELS *( i % 11 )));
}

int get_btn_y(int i) {
	return (FIRST_BTN_SCREEN_Y + (BTN_WIDTH_PIXELS *( i / 11)));
}

void simulate_click(int x, int y) {
	INPUT inputs[3];
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    inputs[0].mi.dx = x * 65536 / desktop_rect.right;
    inputs[0].mi.dy = y * 65536 / desktop_rect.bottom;

    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    inputs[2].type = INPUT_MOUSE;
    inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }
}

void simulate_keypress(int vKey) {
	INPUT inputs[2];
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = vKey;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = vKey;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }
}

int main() {
	OpenClipboard(NULL);
	image = GetClipboardData(CF_BITMAP);
	GetObject(image, sizeof(BITMAP), &image_info);
	printf("img size: %d, %d\n", image_info.bmWidth, image_info.bmHeight);
	if (!image_info.bmWidth || !image_info.bmHeight)
		exit(puts("bad image"));
	hdcMem = CreateCompatibleDC(NULL);
	SelectObject(hdcMem, image);
	GetClientRect(GetDesktopWindow(), &desktop_rect);
	Sleep(2000);
	double dist_px = (double)image_info.bmWidth / RESULT_WIDTH;
	int result_height = (double)image_info.bmHeight / dist_px;
	uint32_t *converted = malloc(RESULT_WIDTH * result_height * sizeof(int));
	uint64_t *color_count = calloc(ARRAYSIZE(colors), sizeof(uint64_t));

	// printf("%08X\n", GetPixel(hdcMem, 608, 228));
	// printf("%08X\n", colors[get_matching_color(GetPixel(hdcMem, 608, 228))]);
	// printf("%08X\n", CLR_INVALID );
	// goto exit;

	for (int y=0; y<result_height; y++) {
		for (int x=0; x<RESULT_WIDTH; x++) {
			int i_color = get_matching_color(GetPixel(hdcMem, x*dist_px, y*dist_px));
			converted[y*RESULT_WIDTH + x] = i_color;
			color_count[i_color]++;
		}
	}

	uint64_t max_count = 0;
	int most_prevalent_color;
	for (int i=0; i<ARRAYSIZE(colors); i++) {
		if (color_count[i] > max_count) {
			max_count = color_count[i];
			most_prevalent_color = i;
		}
	}

	simulate_click(get_btn_x(most_prevalent_color), get_btn_y(most_prevalent_color));
	simulate_keypress('F');
	simulate_click(RESULT_LEFT, RESULT_TOP);
	simulate_keypress('B');

	for (int y=0; y<result_height; y++) {
		for (int x=0; x<RESULT_WIDTH; x++) {
			if (GetAsyncKeyState(VK_SPACE))
				goto exit;
			int btn = get_matching_color(GetPixel(hdcMem, x*dist_px, y*dist_px));
			if (btn == most_prevalent_color)
				continue;
			simulate_click(get_btn_x(btn), get_btn_y(btn));
			simulate_click(RESULT_LEFT + x*RESULT_PX_SPACING,
					RESULT_TOP + y*RESULT_PX_SPACING);
			Sleep(10);
		}
	}

exit:
	DeleteDC(hdcMem);
	CloseClipboard();
}
