#include "DxLib.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "SceneMng.h"
#include "GameCtl.h"
#include "TitleScene.h"

GameScene::GameScene()
{
	Init();

}


GameScene::~GameScene()
{
}

unique_Base GameScene::Updata(unique_Base own, const GameCtl& ctl)
{
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_G])
	{
		return std::make_unique<TitleScene>();
	}

	// DÇâüÇµÇΩÇÁâEà⁄ìÆ
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_D])
	{
		boxPos+=x;
	}
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_A])
	{
		boxPos -= x;
	}
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W])
	{
		boxPos += x;
	}
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S])
	{
		boxPos -= x;
	}

	DrawBox(boxPos, boxposy, boxPos+150, boxposy + 100, GetColor(255, 0, 255), false);

	GameDraw();
	return std::move(own);
}


bool GameScene::GameDraw(void)
{
	ClsDrawScreen();
	DrawBox(boxPos, 550, boxPos+150, 550-150, GetColor(255, 255, 0), TRUE);
	DrawLine(0, 700-150, 1200, 700-150, GetColor(255, 255, 0), TRUE);// Ç±ÇÃê¸ÇÊÇËâ∫Ç…ÇgÇoÇ‚ÉQÅ[ÉW


	DrawFormatString(150, 150, GetColor(255, 255, 0), "GameScene");
	ScreenFlip();
	return false;
}



int GameScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));

	boxposy = SCREEN_SIZE_Y / 2 + 100;
	boxPos = 0;
	x = 10;

	return 0;
}
