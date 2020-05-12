#include "DxLib.h"
#include "GameCtl.h"

GameCtl::GameCtl()
{
}

GameCtl::~GameCtl()
{
}

const KEY_ARRAY & GameCtl::GetCtl(KEY_TYPE type) const
{
	if (type == KEY_TYPE_OLD)
	{
		return dataOld;	
	}
	return data;
}

bool GameCtl::UpdateKey(void)
{
	dataOld = data;				
	GetHitKeyStateAll(&data[0]);
	return true;
}
