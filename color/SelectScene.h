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
	bool FadeInScreen(int fadeStep);


private:

	virtual int Init(void);	

	bool SelectDraw(void);

	int fadeCnt;
	bool fadeOut;

	int backImage;

};

