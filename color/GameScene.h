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
	int _enemy;		// ŠG
	float _ePosX;	// À•W
	bool _eMoveFlag;	// “®‚­‚©‚Ç‚¤‚©@true=“®‚­ false=“®‚©‚È‚¢(“®‚©‚¸UŒ‚)
	bool _eDeathFlag;// €‚ñ‚Å‚¢‚é‚©‚Ç‚¤‚©

	// ‚»‚Ì‚Ù‚©
	int stageBack;	// ”wŒi‰æ‘œ

};
