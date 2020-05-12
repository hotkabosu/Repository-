#pragma once
#include <memory>


// ｵﾌｾｯﾄの位置
#define GAME_SCREEN_X 40	// ｹﾞｰﾑｴﾘｱの横表示ｵﾌｾｯﾄ
#define GAME_SCREEN_Y 75	// ｹﾞｰﾑｴﾘｱの縦表示ｵﾌｾｯﾄ

// ｹﾞｰﾑのﾌﾟﾚｲｴﾘｱ
#define GAME_SCREEN_SIZE_X 640	// ｹﾞｰﾑｴﾘｱの横ｻｲｽﾞ
#define GAME_SCREEN_SIZE_Y 480	// ｹﾞｰﾑｴﾘｱの縦ｻｲｽﾞ

#define CHIP_SIZE 20

class BaseScene; // ﾌﾟﾛﾄﾀｲﾌﾟ宣言
class GameCtl;

using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	// ｺﾝｽﾄﾗｸﾀはいらない 必要なのはﾃﾞｽﾄﾗｸﾀ
	virtual ~BaseScene();

	virtual unique_Base Updata(unique_Base own, const GameCtl&ctl) = 0;// own自分自身 純粋仮想関数に
	// 純粋仮想関数→継承するｼｰﾝは必ず用意しろよっていう脅し、忘れることがないように
	virtual bool CheckEditMode(void) {	return false;};

private:

	virtual int Init(void) = 0;
};