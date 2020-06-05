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
	virtual int Init(void);

	bool TitleDraw(void);

private:
	int _titleBGM;
	int _titleSE;
	
	// �摜�p�ϐ�
	int push;
	int startButton;
	int backImage;
	int bright;
	int scButton1;
	int flamCnt;
	bool selectFlag;
	SCENE_TYPE _nowScene;
	SCENE_TYPE _oldScene;
	int _time;
	//bool changeFlag;
};

