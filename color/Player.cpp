//#include "DxLib.h"
//#include "Player.h"
//#include "GameCtl.h"
//
//
//Player::Player(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
//{
//	// プレイヤー
//	_pPosY = 550;
//	_pPosX = 0;
//	_pAtackRange = 150;
//	init("image/bomberman.png", VECTOR2(20, 32), VECTOR2(5, 4), setUpPos);
//	//DrawBox(31, 31, 60, 60, GetColor(255, 0, 255), TRUE);
//	//if (_atackFlag == true)
//	//{
//	//	DrawBox(_pPosX + _pAtackRange, 550 - 75, _pPosX + _pAtackRange + 75, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
//	//	_atackFlag = false;
//	//}
//
//}
//
//Player::Player()
//{
//}
//
//Player::~Player()
//{
//}
//
//bool Player::PlayerDraw(void)
//{
//	return false;
//}
//
//void Player::SetMove(const GameCtl& ctl, weakListObj objList)
//{
//	// Dを押したら右移動
//	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_D])
//	{
//		_pPosX += 5;
//	}
//	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_A])
//	{
//		_pPosX -= 5;
//	}
//	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_K])
//	{
//		_atackFlag = true;
//	}
//
//}
