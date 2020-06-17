#include "DxLib.h"
#include "SceneMng.h"
#include "StageCtl.h"


StageCtl::StageCtl()
{
	bgImage = LoadGraphScreen(0, 0, "stage/testStage.png", true);

}

StageCtl::~StageCtl()
{

}

STAGE StageCtl::getStage(void)
{
	return selectStage;
}

void StageCtl::setStage(STAGE stage)
{
	selectStage = stage;
}


void StageCtl::FirstStage(VECTOR2 pos)
{
	bgImage = LoadGraphScreen(pos.x, pos.y, "stage/testStage.png", true);
}

void StageCtl::SecondStage(VECTOR2 pos)
{
	bgImage = LoadGraphScreen(pos.x, pos.y, "stage/testStage2.png", true);
}
