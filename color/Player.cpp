//#include "Player.h"
//#include "DxLib.h"
////#include "GameCtl.h"
////
////
//Player::Player(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
//{
//	keyIdTbl = {
//		KEY_INPUT_NUMPAD2,	// ��
//			 KEY_INPUT_NUMPAD4,	// ��
//			 KEY_INPUT_NUMPAD6,	// �E
//			 KEY_INPUT_NUMPAD8,	// ��
//	};
//
//	// �v���C���[
//	_pos = VECTOR2{ 0,550 };
//	_pAtackRange = 150;
//
//	init("image/frends.png", VECTOR2(150, 75), VECTOR2(1, 2), setUpPos);
//	initAnim();
//	//DrawBox(31, 31, 60, 60, GetColor(255, 0, 255), TRUE);
//	//if (_atackFlag == true)
//	//{
//	//	DrawBox(_pPosX + _pAtackRange, 550 - 75, _pPosX + _pAtackRange + 75, 550 - 150, GetColor(0, 255, 0), false);// �U���͈�
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
////
////
////bool Player::initAnim(void)
////{
////	AddAnim("�ړ�", 0, 0, 2, 5, true);
////	return true;
////}
////
////bool Player::CheckObjType(OBJ_TYPE type)
////{
////	return (type = OBJ_TYPE_PLAYER);	// �w�肵���^�Ɠ������ǂ�������
////}
////
////void Player::SetMove(const GameCtl& ctl, weakListObj objList)
////{
////	// �ϐ��ɕۑ��@�擾���ͷ����̕Ԃ�l ��ð���
////	auto& keyTbl = ctl.GetCtl(KEY_TYPE_NOW);
////	auto& keyTblOld = ctl.GetCtl(KEY_TYPE_OLD);
////	SetAnim("�ړ�");// D����������E�ړ�
////	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_D])
////	{
////		_pPosX += 5;
////	}
////	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_A])
////	{
////		_pPosX -= 5;
////	}
////	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_K])
////	{
////		_atackFlag = true;
////	}
////
////}
//
//bool Player::PlayerDraw(void)
//{
//	ClsDrawScreen();
//	_player = LoadGraph("image/player/pTest.png");
//	//_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pTest.png", true);// ���摜
//	SetDrawBright(0, 255, 0);
//	LoadGraphScreen(_pos.x, _pos.y - 150, "image/player/pTest.png", true);// ���摜
//	DeleteGraph(_player);
//
//	ScreenFlip();
//	return false;
//
//}
