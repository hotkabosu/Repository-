#pragma once
#include <memory>
#include <array>
#include "VECTOR2.h"
#include "color.h"
#include "Obj.h"

using DIR_TBL_ARRAY = std::array<int, DIR_MAX>;
#define lpPlayer Player::GetInstance()

class Player:
	public Obj

{
public:
	Player(VECTOR2 setUpPos, VECTOR2 drawOffset);

	Player();
	~Player();

	void ChangeColor(void);

private:
	bool initAnim(void);
	bool CheckObjType(OBJ_TYPE type);

	void SetMove(const GameCtl& ctl, weakListObj objList);
	DIR_TBL_ARRAY		 keyIdTbl;

	int _player;
	float _pAtackRange;

	DIR dir;
	int _speed;

	VECTOR2 _nowPos;
	VECTOR2 _oldPos;
	bool _moveFlag;
	bool _shotFlag;
	bool _jumpFlag;
	bool _underFlag;
	bool _atackFlag;

	int _colorNum;
	COLOR_TYPE _color;

};

