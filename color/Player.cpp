#include "Player.h"
#include "DxLib.h"
#include "GameCtl.h"

Player::Player(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{

	// プレイヤー
	_speed = 5;
	_pAtackRange = 150;

	init("image/player/bPlayer.png", VECTOR2(150, 150), VECTOR2(5, 4), setUpPos);
	initAnim();
	//DrawBox(31, 31, 60, 60, GetColor(255, 0, 255), TRUE);
	//if (_atackFlag == true)
	//{
	//	DrawBox(_pPosX + _pAtackRange, 550 - 75, _pPosX + _pAtackRange + 75, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
	//	_atackFlag = false;
	//}

}

Player::Player()
{
}

Player::~Player()
{
}
//
//
bool Player::initAnim(void)
{
	//AddAnim("停止", 0, 0, 2, 6, true);
	//AddAnim("移動", 0, 2, 2, 8, true);
	AddAnim("停止", 0, 0, 1, 6, true);
	AddAnim("移動", 0, 2, 2, 8, true);
	//AddAnim("死亡", 4, 0, 4, 8, false);		// y,x,コマ数,?	falseじゃないと死んで復活する(アニメーションのループ)
	return true;
}

void Player::SetMove(const GameCtl& ctl, weakListObj objList)
{
	// 変数に保存　取得情報はｷｰ情報の返り値 ｷｰﾃｰﾌﾞﾙ
	auto& keyTbl = ctl.GetCtl(KEY_TYPE_NOW);
	auto& keyTblOld = ctl.GetCtl(KEY_TYPE_OLD);

	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RCONTROL] == 1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RCONTROL] == 0)
	{
		ChangeColor();
		_colorNum += 1;
	}

	// Dを押したら右移動
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_D])
	{
		_nowPos.x += 5;
		//frendPos += 5;
		_moveFlag = true;
		dir = DIR_RIGHT;
	}
	else
	{
		_moveFlag = false;

	}
	// 左に移動
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_A])
	{
		if (0 <= _nowPos.x)
		{
			_nowPos.x -= 5;
			//frendPos -= 5;
		}
		else
		{
			_nowPos.x += 1;

		}
		dir = DIR_LEFT;
	}
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W] == 1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_W] == 0)
	{
		_jumpFlag = true;
		_oldPos.y = _nowPos.y; // ジャンプする前の座標を保存

	}
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S])
	{
		_underFlag = true;

	}
	else
	{
		_underFlag = false;
	}
	// 攻撃
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_K])
	{
		_atackFlag = true;

	}
	// 遠距離攻撃		
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_L] == 1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_L] == 0)
	{
		_shotFlag = true;
	}


	SetAnim("移動");	// ここになったら移動したということ 上の移動内のｱﾆﾒｰｼｮﾝがいらなくなる

}

void Player ::ChangeColor(void)
{
	//trianglePosY += 50;
	//if (680 <= trianglePosY)
	//{
	//	//　一番下まで来たら座標を戻してcolorを赤（一番上）に戻す
	//	trianglePosY = 570;
	//	_colorNum = 0;

	//}

	if (_colorNum == 0)
	{
		_color = COLOR_TYPE::RED;
	}
	else if (_colorNum == 1)
	{
		_color = COLOR_TYPE::BLUE;
	}
	else if (_colorNum == 2)
	{
		_color = COLOR_TYPE::GREEN;
	}

}

//bool Player::PlayerDraw(void)
//{
//	ClsDrawScreen();
//	_player = LoadGraph("image/player/pTest.png");
//	//_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pTest.png", true);// 仮画像
//	SetDrawBright(0, 255, 0);
//	LoadGraphScreen(_pos.x, _pos.y - 150, "image/player/pTest.png", true);// 仮画像
//	DeleteGraph(_player);
//
//	ScreenFlip();
//	return false;
//
//}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return (type = OBJ_TYPE_PLAYER);	// 指定した型と同じかどうか見る
}

