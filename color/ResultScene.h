#pragma once
#include "BaseScene.h"
#include "SceneMng.h"
#include "VECTOR2.h"

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

	int backImage;
	int reTitleButton;
	int reStartButton;
	int reSelectButton;
	VECTOR2 resultPos;// 80 160


	int changeScene[3];
	int changeNum;
	SCENE_TYPE scene;

	int _resultBGM;
	int _resultSE;
	int _cursorSE;
};

