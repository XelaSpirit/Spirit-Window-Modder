#include <iostream>
#include <string>
#include <Windows.h>

#define WORKERW_MESSAGE 0x052C

HWND win = NULL;
std::wstring winName;

BOOL CALLBACK enumWindowsProc(_In_ HWND hwnd, _In_ LPARAM lparam) {
	LPWSTR name = new WCHAR[winName.length() + 1];
	GetWindowText(hwnd, name, (int)winName.size() + 1);

	if (name == winName) {
		win = hwnd;
		return false;
	}
	else {
		return true;
	}
}

int main() {
	std::wcout << "Enter name of window to modify: ";
	std::getline(std::wcin, winName);

	bool suc = EnumWindows(enumWindowsProc, NULL);

	if (win != NULL) {
		std::cout << "Enter new window position: ";
		std::string X, Y;
		std::cin >> X >> Y;

		int x, y;
		x = std::stoi(X);
		y = std::stoi(Y);

		std::cout << "Enter new window size: ";
		std::string W, H;
		std::cin >> W >> H;

		int w, h;
		w = std::stoi(W);
		h = std::stoi(H);

		std::cout << "Moving window to " << x << ", " << y << " with size " << w << "x" << h << std::endl;

		SetWindowPos(win, HWND_BOTTOM, x, y, w, h, SWP_NOACTIVATE);
	}
	else {
		std::cout << "Window Not found" << std::endl;
	}

	while (true) {}

	return 0;
}