#pragma once
#include "BaseScene.h"
#include "Obj.h"
#include "VECTOR2.h"

class GameCtl;

class GameScene:
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	virtual unique_Base Updata(unique_Base own, const GameCtl& ctl);
	void HitCheck(void);
	void StatusDraw(void);

private:
	virtual int Init(void);
	bool GameDraw(void);
	
	// Player
	int _player;
	bool _atackFlag;
	float _pPosX;
	float _pPosY;
	float _pAtackRange;
	int _damage;
	int hpBox;
	// enemy
	int _enemy;		// 絵
	float _ePosX;	// 座標
	bool _eMoveFlag;	// 動くかどうか　true=動く false=動かない(動かず攻撃)
	bool _eDeathFlag;// 死んでいるかどうか
	int eHP;
	// そのほか
	int stageBack;	// 背景画像
	DIR dir;
	int flamCnt;


	float nowTime;
	float oldTime;
};
