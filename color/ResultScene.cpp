#include "Dxlib.h"
#include "SceneMng.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "GameCtl.h"
#include "ScoreMng.h"

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
		if (changeNum==1)
		{
			return std::make_unique<TitleScene>();

		}
		else if (changeNum == 2)
		{
			return std::make_unique<GameScene>();

		}
		else if (changeNum == 3)
		{
			return std::make_unique<SelectScene>();

		}

	}

	if (SCREEN_SIZE_Y / 3-5 <= resultPos.y && resultPos.y <= SCREEN_SIZE_Y)
	{
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
		{
			resultPos.y += 100;
			changeNum += 1;

		}
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_W] == 0)
		{
			resultPos.y -= 100;
			changeNum -= 1;
		}

	}


	Draw();
	return std::move(own);
}

bool ResultScene::Draw(void)
{
	ClsDrawScreen();
	DrawBox(resultPos.x, resultPos.y, resultPos.x + 400, resultPos.y + 100, GetColor(0, 255, 0), true);
	DrawFormatString(150, 150, GetColor(255, 0, 255), "ResultScene　PushEnter");

	changeScene[static_cast<int>(SCENE_TYPE::TITLE)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2, "image/result/titleButton.png", true);
	changeScene[static_cast<int>(SCENE_TYPE::GAME)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2 + 100, "image/result/reStartButton.png", true);// この位置にストーリーを見るボタン
	changeScene[static_cast<int>(SCENE_TYPE::SELECT)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2+200, "image/result/selectButton.png", true);
	
	DrawFormatString(SCREEN_SIZE_X -100, 570, GetColor(255, 255, 255), "[Score:%d]", lpScoreMng.getScore());
	//lpScoreMng.getScore();
	ScreenFlip();
	return false;
}




int ResultScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));	
	resultPos = { VECTOR2(SCREEN_SIZE_X / 3,SCREEN_SIZE_Y / 2) };
	//scene = SCENE_TYPE::RESULT;
	changeNum = 1;
	return 0;
}
