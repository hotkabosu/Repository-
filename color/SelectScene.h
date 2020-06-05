#pragma once
#include "BaseScene.h"
#include "VECTOR2.h"
#include "StageCtl.h"

class GameCtl;

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	virtual unique_Base Updata(unique_Base own, const GameCtl&ctl);
//	STAGE StageLoad(STAGE getStage, VECTOR2 pos, std::string f_name,bool flag);
	//bool StageLoad1(void);
	//bool StageLoad2(void);


private:

	virtual int Init(void);	

	bool SelectDraw(void);

	int flamCnt;

	int _selectBGM;
	int _selectSE;
	int backImage;
	int _stage[2];
	int _stageNum;
	int stage1;
	int stage2;
	int moji1;
	int moji2;

	VECTOR2 selectPos;// 80 160
	VECTOR2 nowPos;
	int changeTime;
	bool selectFlag;// true選択した　false選択してない　
	bool decided;
	STAGE selectStage;
};

