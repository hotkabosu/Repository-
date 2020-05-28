#pragma once
#include "BaseScene.h"
#include "Obj.h"
#include "color.h"
#include "StageCtl.h"
#include "VECTOR2.h"


// プレイヤーが受けるダメージ種類
enum DAMAGE
{
	// 現在の色が敵の色に対して
	DAMAGE_WEAK,		// 弱い色　例）player青　enemy緑		自分に12ダメージ
	DAMAGE_NORMAL,		// 同じ色　例）player青　enemy青		自分に8ダメージ
	DAMAGE_STRONG,		// 強い色 例）player青　enemy赤		自分に4ダメージ
	DAMAGE_MAX
};

enum class ENEMY_COLOR
{
	NON,
	RED,
	BLUE,
	GREEN,
	MAX
};

enum class ENEMY_TYPE
{
	NON,
	NORMAL,
	BOSS,
	MAX
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
	void NormalEnemy(void);
	void BossCheck(void);
	void StatusDraw(void);
	void StageControl(void);
	void ChangeColor(void);
	void PlayerCtl(void);
	void PlayerDraw(void);

	void AddScore(void);
	void StageDraw(void);

private:
	sharedListObj objList;
	virtual int Init(void);
	bool GameDraw(void);
	
	// Player
	int _player;// 画像
	bool _atackFlag;	// 近距離攻撃
	bool moveFlag;	// 動けるかどうか
	bool jumpFlag;
	int jumpCnt;
	bool underFlag;
	VECTOR2 playerPos;// 座標
	VECTOR2 playerOldPos;
	float _pAtackRange;// 攻撃範囲
	int _damage;
	bool _damageFlag;
	int hpBox;		
	int playerLife;
	// 遠距離攻撃
	int _shot;
	int _shotSpeed;
	int _shotSize;
	bool _shotFlag;
	VECTOR2 _shotPos;
	//float frendPos;
	//bool hitFrend;



	// enemy
	int _enemy;		// 絵
	VECTOR2 enemyAtackRange;
	VECTOR2 enemyPos;
	bool _eMoveFlag;	// 動くかどうか　true=動く false=動かない(動かず攻撃)
	bool _eDeathFlag;// 死んでいるかどうか
	int enemyLife;
	// そのほか
	int stageBack;	// 背景画像
	DIR playerDir;
	int flamCnt;
	int oldFlam;
	int triangle;
	int trianglePosY;
	VECTOR2 mapPos;
//	const GameCtl& test;
	int time;
	STAGE playStage;

	int bgImage;
	int bgPosX1;				// 横サイズ1
	VECTOR2 centerPos;// 画面中央

	VECTOR2 markerPos[3];
	COLOR_TYPE colorType[static_cast<int>(COLOR_TYPE::MAX)];
	int nowColor[3];
	int colorNum;
	int enemyNum;
	ENEMY_TYPE enemyTypetest[static_cast<int>(ENEMY_TYPE::MAX)];

	COLOR_TYPE enemyColor;
	ENEMY_COLOR enemyType;
	COLOR_TYPE playerColor;
	
	int _gBoss;
	VECTOR2 _bossPos;
	int _bossLife;
	bool _bossFlag;
	int score;
	int highScore;
};
