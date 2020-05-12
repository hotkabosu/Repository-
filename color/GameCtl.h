#pragma once
#include <array>

using KEY_ARRAY = std::array<char, 256>;

enum KEY_TYPE
{
	KEY_TYPE_NOW,
	KEY_TYPE_OLD,
	KEY_TYPE_MAX,
};

class GameCtl
{
public:
	GameCtl();
	~GameCtl();
	const KEY_ARRAY &GetCtl(KEY_TYPE type) const;
	bool UpdateKey(void);	
private:
	KEY_ARRAY data;	
	KEY_ARRAY dataOld;	

};

