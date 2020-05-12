#pragma once
#include "BaseScene.h"

class GameCtl;

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	virtual unique_Base Updata(unique_Base own, const GameCtl&ctl);


private:

	virtual int Init(void);	

	bool SelectDraw(void);

};

