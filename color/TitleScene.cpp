#include "Dxlib.h"
#include "GameCtl.h"
#include "SceneMng.h"
#include "TitleScene.h"
#include "SelectScene.h"


TitleScene::TitleScene()
{
	Init();

}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Updata(unique_Base own, const GameCtl& ctl)
{
	// Enterキーで移動
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_T])
	{
		return std::make_unique<SelectScene>();
	}

	TitleDraw();
	return std::move(own);
}


bool TitleScene::TitleDraw(void)
{
	ClsDrawScreen();

	DrawFormatString(150, 150, GetColor(255, 0, 255), "TitleScene");

	startButton= LoadGraphScreen(SCREEN_SIZE_X/3, SCREEN_SIZE_Y / 2, "image/title/tStartButton1.png", true);
	startButton = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2+100, "image/title/tStartButton1.png", true);// この位置にストーリーを見るボタン
	DrawFormatString(0, 600, GetColor(255, 0, 255), "PushT");

	ScreenFlip();
	return false;
}


int TitleScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));



	return 0;
}
