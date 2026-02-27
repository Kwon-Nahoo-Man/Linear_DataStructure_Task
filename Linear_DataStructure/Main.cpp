#include <iostream>
#include <Windows.h>
#include "Inventory.h"

int main()
{
	CONSOLE_CURSOR_INFO info{};
	info.dwSize = 1;
	info.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	// inventory 선언
	C_INVENTORY inventory{};
	inventory.Init();
	inventory.SetShowItemIndex(0);

	// frame 보정을 위한 것
	LARGE_INTEGER frequency{};
	QueryPerformanceFrequency(&frequency);
	
	LONGLONG previousTime{};
	LONGLONG currentTime{};

	LARGE_INTEGER time{};
	QueryPerformanceCounter(&time);

	currentTime = time.QuadPart;
	previousTime = currentTime;

	float targetFrameRate{60.0f};
	float oneFrameTime = 1.0f / targetFrameRate;

	while (true)
	{
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		float deltaTime{};
		deltaTime = static_cast<float>(currentTime - previousTime);
		deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

		if (deltaTime >= oneFrameTime)
		{
			system("cls");
			std::cout << "Press ESC to escape.\n";
			std::cout << "=============================\n";
			inventory.ShowItem();

			previousTime = currentTime;
		}
		

		if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) > 0)
		{
			break;
		}
	}

	info.dwSize = 1;
	info.bVisible = TRUE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);


	inventory.Destroy();
}