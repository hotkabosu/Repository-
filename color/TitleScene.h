#pragma once
#include "BaseScene.h"

class GameCtl;

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	virtual unique_Base Updata(unique_Base own, const GameCtl&ctl);
	bool FadeOutScreen(int fadeStep);
	virtual int Init(void);

	bool TitleDraw(void);

private:
	
	int fadeCnt;
	bool fadeOut;
	// ‰æ‘œ—p•Ï”
	int startButton;
	int backImage;
	int bright;
	int scButton1;
	int flamCnt;
	bool selectFlag;
	SCENE_TYPE _nowScene;
	SCENE_TYPE _oldScene;
	//float _time;
	//bool changeFlag;
};

