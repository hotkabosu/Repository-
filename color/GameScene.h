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
	int _enemy;		// �G
	float _ePosX;	// ���W
	bool _eMoveFlag;	// �������ǂ����@true=���� false=�����Ȃ�(�������U��)
	bool _eDeathFlag;// ����ł��邩�ǂ���
	int eHP;
	// ���̂ق�
	int stageBack;	// �w�i�摜
	DIR dir;
	int flamCnt;


	float nowTime;
	float oldTime;
};
