#pragma once
#include "BaseScene.h"

class GameCtl;

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	virtual unique_Base Updata(unique_Base own, const GameCtl& ctl);
	bool Draw(void);

private:

	virtual int Init(void);


};

