#include "Dxlib.h"
#include "SceneMng.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "GameCtl.h"
#include "StageCtl.h"


SelectScene::SelectScene()
{
	Init();
}


SelectScene::~SelectScene()
{

}

unique_Base SelectScene::Updata(unique_Base own, const GameCtl& ctl)
{
	// EnterKeyで決定
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RETURN] == 1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RETURN] == 0)
	{
		// ステージ決定
		selectFlag = true;
	}

	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W] == 1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_W] == 0)
	{
		// 上のステージ
		if (2 <= _stageNum)
		{
			_stageNum -= 1;
			selectPos.y -= 270;
		}
	}
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
	{
		// 下のステージ
		if (_stageNum < 2)
		{
			_stageNum += 1;
			selectPos.y += 270;
		}
	}


	if (selectFlag == true)
	{
		PlaySoundMem(_selectSE, DX_PLAYTYPE_NORMAL, false);
		ChangeVolumeSoundMem(155, _selectBGM);
		changeTime++;


		if (50 <= changeTime)
		{
			DeleteSoundMem(_selectSE);
			DeleteSoundMem(_selectBGM);
			selectFlag = false;
			return std::make_unique<GameScene>();
		}

	}

	// 決定したら
	if (_stageNum == 1)
	{
		selectStage = STAGE::FIRST;
	}
	else if (_stageNum == 2)
	{
		selectStage = STAGE::SECOND;

	}

	SelectDraw();
	flamCnt++;
	lpStageCtl.setStage(selectStage);
	return std::move(own);
}

bool SelectScene::SelectDraw(void)
{
	PlaySoundMem(_selectBGM, DX_PLAYTYPE_LOOP, false);
	ClsDrawScreen();
	backImage = LoadGraphScreen(0, 0, "image/selectBack.png", true);
	DrawFormatString(150, 100, GetColor(255, 0, 255), "SelectStage　PushEnter");
	if (selectFlag == false)
	{
		if ((flamCnt / 30) % 2 == 0)
		{
			DrawBox(selectPos.x, selectPos.y, selectPos.x+540, selectPos.y + 270, GetColor(0, 255, 0), true);
		}
	}
	else
	{
		// ステージが決まった
		if ((flamCnt / 5) % 2 == 0)
		{

			DrawBox(selectPos.x, selectPos.y, selectPos.x+540, selectPos.y+270, GetColor(0, 255,100), true);
		}

	}
	_stage[static_cast<int>(STAGE::FIRST)] = LoadGraphScreen(100, 50, "image/select/testStage.png", true);
	_stage[static_cast<int>(STAGE::SECOND)] = LoadGraphScreen(100, 320, "image/select/testStage2.png", true);

	DrawFormatString(SCREEN_SIZE_X - 50, 450, GetColor(255, 255, 255), "[%d]", _stageNum);
	DrawFormatString(SCREEN_SIZE_X - 200, 570, GetColor(0, 0, 0), "Ｗキー：↑\n");
	DrawFormatString(SCREEN_SIZE_X - 200, 600, GetColor(0, 0, 0), "Ｓキー：↓\n");
	DrawFormatString(SCREEN_SIZE_X - 200, 630, GetColor(0, 0, 0), "Ｅｎｔｅｒキー：決定\n");


	ScreenFlip();

	return false;
}


int SelectScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	_selectBGM = LoadSoundMem("BGM/selectBGM.mp3");
	_selectSE = LoadSoundMem("BGM/titleSE.mp3");
	selectPos = { VECTOR2(80,30) };
	nowPos.y = selectPos.y;
	changeTime = 0;
	_stageNum = 1;
	selectFlag = false;
	return 0;
}
