#include "Item.h"

void C_ITEM::Init(int id, const std::string& name, const std::string& type, int cost, int rarity)
{
	m_id = id;
	m_name = name;
	m_type = type;
	m_cost = cost;
	m_rarity = rarity;
}
