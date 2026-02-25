#pragma once

#include <string>

class C_ITEM

{
	friend class C_INVENTORY;
public:

	C_ITEM() = default;
	~C_ITEM() = default;

	// C_ITEM을 사용하기 전 Init으로 값 할당
	void Init(int id, std::string name, std::string type, int cost, int rarity);

public:

	C_ITEM(const C_ITEM&) = delete;
	const C_ITEM& operator=(const C_ITEM&) = delete;

private:
	int m_id{};
	int m_cost{};
	int m_rarity{};

	std::string m_name{};
	std::string m_type{};

};
