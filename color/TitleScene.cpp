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
		//	if (49 <= _time)
		//	{
		//		changeFlag = true;
		//	}
		//if (changeFlag == true)
		//{
		//_oldScene = SCENE_TYPE_TITLE;
			//changeFlag = false;
		//}
	}
	if (selectFlag == true)
	{
		PlaySoundMem(_titleSE, DX_PLAYTYPE_LOOP, false);
		ChangeVolumeSoundMem(155, _titleBGM);
		_time++;
		if (50 <= _time)
		{
			DeleteSoundMem(_titleSE);
			DeleteSoundMem(_titleBGM);
			selectFlag = false;
			return std::make_unique<SelectScene>();

		}
	}

	//DrawFormatString(50, 50, 0xff0000, "%f", _time);
	//
	// ストーリーを見るかゲームを始めるか選べれるように
	//if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
	//	&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
	//{
	//	startButton = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2, "image/title/tsButton0.png", true);
	//}
	//if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S])
	//{
	//	if ((flamCnt / 20) % 2 == 0)
	//	{
	//		scButton1;
	//	}
	//}


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
	
	// ストーリーチェックボタン
	scButton1 = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2+100, "image/title/scButton1.png", true);// この位置にストーリーを見るボタン
	
	//DrawFormatString(50, 50, 0xff0000, "%d", _time);
	push = LoadGraphScreen(SCREEN_SIZE_X / 3+50, SCREEN_SIZE_Y / 2 - 25, "image/push.png", true);

	//DrawFormatString(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2-20, GetColor(0, 0, 0), "PushEnterKey");

	ScreenFlip();
	return false;
}

int TitleScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	_titleBGM= LoadSoundMem("BGM/titleBGM.mp3");
	_titleSE = LoadSoundMem("BGM/titleSE.mp3");
	bright = 255;
	//fadeCnt = 0;
	flamCnt = 0;
	//_nowScene = SCENE_TYPE_TITLE;
	selectFlag = false;
	_time = 0;
	//changeFlag = false;
	return 0;
}
