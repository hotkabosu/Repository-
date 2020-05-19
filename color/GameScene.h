#pragma once
#include "BaseScene.h"
#include "Obj.h"
#include "VECTOR2.h"


// プレイヤーが受けるダメージ種類
enum DAMAGE
{
	DAMAGE_WEAK,// 弱い色　例）player青　enemy緑
	DAMAGE_NORMAL,// 同じ色　例）player青　enemy青
	DAMAGE_STRONG,// 強い色 例）player青　enemy赤
	DAMAGE_MAX
};

class GameCtl;
class Obj;

class GameScene:
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	virtual unique_Base Updata(unique_Base own, const GameCtl& ctl);
	void HitCheck(void);
	void StatusDraw(void);
	void StageControl(void);

	void PlayerColor(void);

private:
	sharedListObj objList;
	virtual int Init(void);
	bool GameDraw(void);
	
	// Player
	int _player;// 画像
	bool _atackFlag;
	VECTOR2 playerPos;// 座標
	float _pAtackRange;// 攻撃範囲
	int _damage;
	int hpBox;
	int playerLife;

	float frendPos;
	bool hitFrend;
	// enemy
	int _enemy;		// 絵
	float _ePosX;	// 座標
	bool _eMoveFlag;	// 動くかどうか　true=動く false=動かない(動かず攻撃)
	bool _eDeathFlag;// 死んでいるかどうか
	int enemyLife;
	// そのほか
	int stageBack;	// 背景画像
	DIR dir;
	int flamCnt;

	VECTOR2 mapPos;

	int time;
};
