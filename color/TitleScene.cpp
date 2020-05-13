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
		//
		//if (!FadeOutScreen(5))
		//{
			return std::make_unique<SelectScene>();
		//}

	}

	// ストーリーを見るかゲームを始めるか選べれるように
	//if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
	//	&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
	//{
	//	DrawBox(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2+100, SCREEN_SIZE_X / 3 + 400, SCREEN_SIZE_Y / 2 + 200, GetColor(255, 0, 255), false);

	//}


	TitleDraw();
	return std::move(own);
}

bool TitleScene::FadeOutScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		return false;
	}
}



bool TitleScene::TitleDraw(void)
{
	ClsDrawScreen();

	DrawFormatString(150, 150, GetColor(255, 0, 255), "TitleScene");
	backImage = LoadGraphScreen(0, 0, "image/title/tBack0.png", true);
	startButton= LoadGraphScreen(SCREEN_SIZE_X/3, SCREEN_SIZE_Y / 2, "image/title/tStartButton0.png", true);
	

	//DrawBox(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2, SCREEN_SIZE_X / 3+400, SCREEN_SIZE_Y / 2+100, GetColor(255, 0, 255), false);


	//SetDrawBright(255, 255, 255);// 色を変える
	//// 輝度を徐々に下げていって暗くする
	//
	
	// ストーリーチェックボタン
	//scButton = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2+100, "image/title/scButton1.png", true);// この位置にストーリーを見るボタン
	
	
	DrawFormatString(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2-20, GetColor(0, 0, 0), "PushEnterKey");

	ScreenFlip();
	return false;
}

int TitleScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));

	bright = 255;
	fadeCnt = 0;

	return 0;
}
