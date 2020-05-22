#include "Dxlib.h"	// DxLibﾗｲﾌﾞﾗﾘを使用する
#include "SceneMng.h"
#include "GameCtl.h"
#include "TitleScene.h"
#include"SelectScene.h"
#include "GameScene.h"

SceneMng::SceneMng()	// ｺﾝｽﾄﾗｸﾀ
{
	SysInit();
}

SceneMng::~SceneMng()	// ﾃﾞｽﾄﾗｸﾀ
{
}

void SceneMng::Run(void) 
{
								// 一番最初に呼ばれる画面
	activeScene = std::make_unique<SelectScene>();	// 初期化

	//ImageMng::GetInstance().GetID("ｷｬﾗ", "image/char.png", { 30, 32 }, { 10,10 });	// キャラ画像

	// ---------- ｹﾞｰﾑﾙｰﾌﾟ 
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)	// 両方DxLibの命令
	{
		gameCtl->UpdateKey();

		activeScene = activeScene->Updata(std::move(activeScene), *gameCtl);
	}
}

VECTOR2 SceneMng::GetScreenSize(void)
{
	return VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

bool SceneMng::SetDrawOffset(VECTOR2 vec)
{
	drawOffset = vec;
	return true;
}

const VECTOR2& SceneMng::GetDrawOffset(void)
{
	return drawOffset;
}


bool SceneMng::DelObjList(std::list<Obj*>::iterator itr)
{
	delete (*itr);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);					// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("Color");
	if (DxLib_Init() == -1) return false;	// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);			// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画
	gameCtl = std::make_unique<GameCtl>();
	return true;
}

