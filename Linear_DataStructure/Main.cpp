#include <iostream>
#include <Windows.h>
#include "Inventory.h"

int main()
{
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

	float targetFrameRate{30.0f};
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
			inventory.ShowItem();

			previousTime = currentTime;
		}
		

		if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) > 0)
		{
			break;
		}
	}

	inventory.Destroy();
}