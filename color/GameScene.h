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
	int _enemy;		// ŠG
	float _ePosX;	// À•W
	bool _eMoveFlag;	// “®‚­‚©‚Ç‚¤‚©@true=“®‚­ false=“®‚©‚È‚¢(“®‚©‚¸UŒ‚)
	bool _eDeathFlag;// €‚ñ‚Å‚¢‚é‚©‚Ç‚¤‚©
	int eHP;
	// ‚»‚Ì‚Ù‚©
	int stageBack;	// ”wŒi‰æ‘œ
	DIR dir;
	int flamCnt;


	float nowTime;
	float oldTime;
};
