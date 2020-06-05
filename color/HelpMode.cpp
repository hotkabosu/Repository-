#include "DxLib.h"
#include "SceneMng.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "GameCtl.h"
#include "HelpMode.h"


HelpMode::HelpMode()
{
	Init();
}

HelpMode::~HelpMode()
{
}

unique_Base HelpMode::Updata(unique_Base own, const GameCtl& ctl)
{
	if (50 <= changeTime)
	{
		selectFlag = false;

		// 決定したら
		if (_buttonNum == 1)
		{
			return std::make_unique<SelectScene>();
		}
		else if (_buttonNum == 2)
		{
			return std::make_unique<TitleScene>();

		}
		else if (_buttonNum == 3)
		{
			return std::make_unique<GameScene>();

		}
	}
	CheckButton(ctl);
}

void HelpMode::CheckButton(const GameCtl& ctl)
{
	//if (30 <= _helpPos.y && _helpPos.y <= 620)
	//{
	//	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W] == 1
	//		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_W] == 0)
	//	{
	//		if (31 <= _helpPos.y)
	//		{
	//			_helpPos.y -= 270;
	//		}
	//		_buttonNum -= 1;
	//	}
	//	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
	//		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
	//	{
	//		//if (nowPos.y <= selectPos.y + 271)
	//		//{
	//		//	selectPos.y += 0;
	//		//}
	//		//else
	//		//{
	//		if (_helpPos.y <= 301)
	//		{
	//			_helpPos.y += 270;
	//		}
	//		_buttonNum += 1;
	//	}
	//}

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
		if (2 <= _buttonNum)
		{
			_buttonNum -= 1;
			_helpPos.y -= 100;
		}
	}
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
	{
		// 下のステージ
		if (_buttonNum < 3)
		{
			_buttonNum += 1;
			_helpPos.y += 100;
		}
	}

	if (selectFlag == true)
	{
		changeTime++;
		// エンターを押したらchangeTime加算
		//　changeTimeが50になるまで点滅を早く　50を超えたらゲームシーンに移動		

	}


}

bool HelpMode::getHelpFlag(void)
{
	return _helpFlag;
}

void HelpMode::setHelpFlag(bool flag)
{
	_helpFlag = flag;
}

bool HelpMode::HelpDraw(void)
{
	ClsDrawScreen();
	//backImage = LoadGraphScreen(0, 0, "image/select/sBack0.png", true);
	DrawBox(_helpPos.x , _helpPos.y, _helpPos.x + 450, _helpPos.y+100, GetColor(255, 255, 255), true);

	DrawFormatString(150, 100, GetColor(255, 0, 255), "SelectStage　PushEnter");

	_helpTitle = LoadGraphScreen(SCREEN_SIZE_X / 3,50,"image/helpMode/helpTitle.png", true);
	
	// ボタン
	_button[static_cast<int>(SCENE_TYPE::SELECT)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2-100, "image/helpMode/selectButton.png", true);
	//_selectBackButton=LoadGraphScreen(_helpPos.x, _helpPos.y, "image/helpMode/selectButton.png", true);
	_button[static_cast<int>(SCENE_TYPE::TITLE)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2, "image/helpMode/titleButton.png", true);
	//_titleBackButton = LoadGraphScreen(_helpPos.x, _helpPos.y+100, "image/helpMode/titleButton.png", true);
	_button[static_cast<int>(SCENE_TYPE::GAME)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2 + 100, "image/helpMode/playButton.png", true);
	//_playBuckButton = LoadGraphScreen(_helpPos.x, _helpPos.y+200, "image/helpMode/playButton.png", true);


	DrawFormatString(SCREEN_SIZE_X - 50, 450, GetColor(255, 255, 255), "[%d]", _buttonNum);



	ScreenFlip();

	return false;
}

int HelpMode::Init(void)
{
	_helpPos = VECTOR2(SCREEN_SIZE_X / 3-20, SCREEN_SIZE_Y / 2-100);
	selectFlag = false;
	return 0;
}

