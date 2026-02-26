#include <Windows.h>

#include "Inventory.h"
#include "Item.h"

void C_INVENTORY::Init(const char* fileName)
{
	
	char path[2048]{};
	sprintf_s(path, 2048, "../Assets/%s", fileName);

	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (file == nullptr)
	{
		__debugbreak();
	}

	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* data = new char[fileSize + 1] {};
	fread(data, sizeof(char), fileSize, file);

	char* context{};
	char* token{};

	token = strtok_s(data, "\n", &context);

	while (token)
	{
		m_itemList.PushBack(new C_ITEM());

		char* oneLineContext{};
		char* part = strtok_s(token, ",", &oneLineContext);

		int id{};
		std::string name{};
		std::string type{};
		int cost{};
		int rarity{};
		
		// ID 저장
		if (part != nullptr)
		{
			id = std::atoi(part);
		}
		part = strtok_s(nullptr, ",", &oneLineContext);
		
		// Name 저장
		if (part != nullptr)
		{
			name = part;
		}
		part = strtok_s(nullptr, ",", &oneLineContext);
		
		// Type 저장
		if (part != nullptr)
		{
			type = part;
		}
		part = strtok_s(nullptr, ",", &oneLineContext);

		// Cost 저장
		if (part != nullptr)
		{
			cost = std::atoi(part);
		}
		part = strtok_s(nullptr, ",", &oneLineContext);

		// Rarity 저장
		if (part != nullptr)
		{
			rarity = std::atoi(part);
		}
		m_itemList.End()->Init(id,name,type,cost,rarity);

		token = strtok_s(nullptr, "\n", &context);
	}

	delete[] data;
	data = nullptr;

	fclose(file);
}

void C_INVENTORY::Destroy()
{
	if (m_itemList.Empty() == false)
	{
		for (int i = 0; i < m_itemList.Size(); i++)
		{
			delete m_itemList[i];
		}
		m_itemList.Clear();
	}
}

void C_INVENTORY::ShowItem()
{
	// 사용자 입력 받아서 보여질 index Update
	UpdateItemIndex();
	const C_ITEM& currentItem = *(m_itemList[m_currentIndex]);

	std::cout << 
		"Id: " << currentItem.m_id << "\t" <<
		"Name: " << currentItem.m_name << "\t" <<
		"Type: " << currentItem.m_type << "\t" <<
		"Cost: " << currentItem.m_cost << "\t" <<
		"Rarity: " << currentItem.m_rarity << "\n";
}

void C_INVENTORY::SetShowItemIndex(int index)
{

	if (index < m_itemList.Size())
	{
		m_currentIndex = index;
	}
	else
	{
		__debugbreak();
	}

}


void C_INVENTORY::UpdateItemIndex()
{
	// item이 없을 때
	if (m_itemList.Empty() == true)
	{
		return;
	}
	
	bool leftDown = (GetAsyncKeyState(VK_LEFT) & 0x8000) > 0;
	bool rightDown = (GetAsyncKeyState(VK_RIGHT) & 0x8000) > 0;


	// 왼쪽 키 눌렀을 때
	if (leftDown && m_wasKeyDown[0] == false)
	{
		
		m_currentIndex--;
		m_wasKeyDown[0] = true;
		if (m_currentIndex < 0)
		{
			m_currentIndex = m_itemList.Size() - 1;
		}
	}
	// 오른쪽 키 눌렀을 때
	else if (rightDown && m_wasKeyDown[1] == false)
	{
		m_currentIndex++;
		if (m_currentIndex >= m_itemList.Size())
		{
			m_currentIndex = 0;
		}
		m_wasKeyDown[1] = true;
	}
	
	// 키를 누르지 않으면 false
	if (leftDown == false)
	{
		m_wasKeyDown[0] = false;
	}
	if (rightDown == false)
	{
		m_wasKeyDown[1] = false;
	}

}
