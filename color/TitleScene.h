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

private:
	virtual int Init(void);

	bool TitleDraw(void);
	
	// �摜�p�ϐ�
	int startButton;


};

