#pragma once
#include "BaseScene.h"

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
	bool _atackFlag;
	float _pPosX;
	float _pPosY;
	float _pAtackRange;

	// enemy
	int _enemy;		// 絵
	float _ePosX;	// 座標
	bool _eMoveFlag;	// 動くかどうか　true=動く false=動かない(動かず攻撃)
	bool _eDeathFlag;// 死んでいるかどうか

	// そのほか
	int stageBack;	// 背景画像

};
