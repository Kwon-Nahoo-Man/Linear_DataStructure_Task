#pragma once

#include "Vector.h"


class C_ITEM;
class C_INVENTORY
{

public:
	C_INVENTORY() = default;
	~C_INVENTORY() = default;

	C_INVENTORY(const C_INVENTORY&) = delete;
	const C_INVENTORY& operator=(const C_INVENTORY&) = delete;

	void Init(const char* fileName = "asset.csv");
	void Destroy();

	void ShowItem();
	void SetShowItemIndex(int index);

	
private:
	// ShowItem 하기 전 계속 Index를 사용자 입력 확인해서 Update 할거임
	void UpdateItemIndex();

private:
	// 보여질 index
	int m_currentIndex{};

	// item list
	C_VECTOR<C_ITEM*> m_itemList;

	// 오른쪽, 왼쪽 키 눌렸는지 저장값
	bool m_wasKeyDown[2]{};


};
