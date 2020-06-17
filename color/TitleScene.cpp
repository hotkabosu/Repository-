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
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RETURN]==1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RETURN] == 0)
	{
		selectFlag = true;
	}
	if (selectFlag == true)
	{
		PlaySoundMem(_titleSE, DX_PLAYTYPE_NORMAL, false);
		ChangeVolumeSoundMem(155, _titleBGM);
		_time++;
		if (40 <= _time)
		{
			DeleteSoundMem(_titleSE);
			DeleteSoundMem(_titleBGM);
			selectFlag = false;
			return std::make_unique<SelectScene>();

		}
	}

	flamCnt++;
	TitleDraw();
	return std::move(own);
}


bool TitleScene::TitleDraw(void)
{
	PlaySoundMem(_titleBGM, DX_PLAYTYPE_LOOP, false);
	ClsDrawScreen();

	DrawFormatString(150, 150, GetColor(255, 0, 255), "TitleScene");
	backImage = LoadGraphScreen(0, 0, "image/title/Back.png", true);
	// 点滅
	if (selectFlag == false)
	{
		if ((flamCnt / 10) % 2 == 0)
		{
			startButton = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2, "image/title/tsButton1.png", true);
		}
	}
	else
	{
		if ((flamCnt / 5) % 2 == 0)
		{
			// 決定　点滅を早くする
			startButton = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2, "image/title/tsButton1.png", true);
		}
	}
	push = LoadGraphScreen(SCREEN_SIZE_X / 3+50, SCREEN_SIZE_Y / 2 - 25, "image/title/push.png", true);

	ScreenFlip();
	return false;
}

int TitleScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	_titleBGM= LoadSoundMem("BGM/titleBGM.mp3");
	_titleSE = LoadSoundMem("BGM/titleSE.mp3");
	bright = 255;
	flamCnt = 0;
	selectFlag = false;
	_time = 0;
	return 0;
}
