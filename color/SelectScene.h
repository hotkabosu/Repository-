#pragma once
#include "BaseScene.h"
#include "VECTOR2.h"

enum class STAGE {
	FIRST,
	SECOND,
	MAX
};

class GameCtl;

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	virtual unique_Base Updata(unique_Base own, const GameCtl&ctl);
	bool FadeInScreen(int fadeStep);
	//STAGE StageLoad(STAGE getStage, VECTOR2 pos, std::string f_name,bool flag);

private:

	virtual int Init(void);	

	bool SelectDraw(void);

	int fadeCnt;
	bool fadeOut;
	int flamCnt;

	int backImage;
	int stage1;
	int stage2;
	VECTOR2 selectPos;// 80 160
	VECTOR2 nowPos;
	int changeTime;
	bool selectFlag;// true選択した　false選択してない　
};

