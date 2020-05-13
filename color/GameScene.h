#pragma once
#include "BaseScene.h"

class GameCtl;

class GameScene:
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	virtual unique_Base Updata(unique_Base own, const GameCtl& ctl);
private:
	virtual int Init(void);
	bool GameDraw(void);

	float boxPos;
	float boxposy;
	float x;
};
