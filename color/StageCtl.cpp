#include "DxLib.h"
#include "SceneMng.h"
#include "Enemy.h"
#include "StageCtl.h"


StageCtl::StageCtl()
{
	//bgImage = 0;
	bgImage = LoadGraphScreen(0, 0, "stage/testStage.png", true);

}

StageCtl::~StageCtl()
{

}

//void StageCtl::SetEnemy(const VECTOR2& pos, weakListObj objList)
//{
//	AddObjList()(objList, std::make_unique<Enemy>
//		(pos  - 50, lpSceneMng.GetScreenSize()));
//
//}

STAGE StageCtl::getStage(void)
{
	return selectStage;
}

void StageCtl::setStage(STAGE stage)
{
	selectStage = stage;
}

void StageCtl::Draw(void)
{
	//bgImage = LoadGraphScreen(0, 0, "stage/testStage.png", true);
	//DrawGraph(0, 0, bgImage, true);
}

//bool StageCtl::MapLoad(sharedListObj objList, bool EditMapFlag)
//{
//	return false;
//}
//
void StageCtl::FirstStage(VECTOR2 pos)
{
	bgImage = LoadGraphScreen(pos.x, pos.y, "stage/testStage.png", true);
	//bgImage = LoadGraphScreen(pos.x, pos.y, "stage/test2Long.png", true);
}

void StageCtl::SecondStage(VECTOR2 pos)
{
	bgImage = LoadGraphScreen(pos.x, pos.y, "stage/testStage2.png", true);
	//bgImage = LoadGraphScreen(pos.x, pos.y, "stage/test2Long.png", true);
}
