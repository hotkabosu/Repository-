#include "Dxlib.h"
#include "SelectScene.h"
#include "SceneMng.h"
#include "GameCtl.h"
#include "TitleScene.h"
#include "GameScene.h"

SelectScene::SelectScene()
{
	Init();
}


SelectScene::~SelectScene()
{

}

unique_Base SelectScene::Updata(unique_Base own, const GameCtl & ctl)
{
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_H])
	{
		return std::make_unique<GameScene>();

	}
	SelectDraw();
	return std::move(own);
}

bool SelectScene::SelectDraw(void)
{
	ClsDrawScreen();
	DrawBox(31, 31, 60, 60, GetColor(255, 0, 255), TRUE);
	DrawFormatString(150, 150, GetColor(255, 0, 255),"pushH");

	ScreenFlip();

	return false;
}


int SelectScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	return 0;
}
