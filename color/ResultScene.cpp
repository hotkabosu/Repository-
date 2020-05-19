#include "Dxlib.h"
#include "ResultScene.h"
#include "SceneMng.h"
#include "GameCtl.h"
#include "TitleScene.h"


ResultScene::ResultScene()
{
	Init();
}


ResultScene::~ResultScene()
{

}

unique_Base ResultScene::Updata(unique_Base own, const GameCtl& ctl)
{
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RETURN] == 1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RETURN] == 0)
	{
		return std::make_unique<TitleScene>();

	}
	Draw();
	return std::move(own);
}

bool ResultScene::Draw(void)
{
	ClsDrawScreen();
	DrawFormatString(150, 150, GetColor(255, 0, 255), "ResultSceneÅ@PushEnter");
	ScreenFlip();
	return false;
}




int ResultScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	return 0;
}
