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
void StageCtl::FirstStage(void)
{
	bgImage = LoadGraphScreen(0, 0, "stage/testStage.png", true);
}

void StageCtl::SecondStage(void)
{
	bgImage = LoadGraphScreen(0, 0, "stage/testStage2.png", true);
}
