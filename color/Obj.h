#pragma once
#include <map>
#include <mutex>
#include "VECTOR2.h"
#include "classObj.h"

enum DIR {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
};

enum ANIM_TBL {			// ｱﾆﾒｰｼｮﾝﾃｰﾌﾞﾙ
	ANIM_TBL_START_ID,	// 開始位置
	ANIM_TBL_FRAME,		// ｺﾏ数
	ANIM_TBL_INV,		// 間隔（ｲﾝﾀｰﾊﾞﾙ
	ANIM_TBL_LOOP,		// ﾙｰﾌﾟするかどうか
	ANIM_TBL_MAX,
};

enum OBJ_TYPE {
	OBJ_TYPE_PLAYER,
	OBJ_TYPE_ENEMY,
	OBJ_TYPE_MAX
};

class GameCtl;

class Obj
{
public:
	Obj(VECTOR2 drawOffset);
	Obj();
	// Drawするだけで画像が表示できるように
	bool init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt);
	bool init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos);
	virtual bool initAnim(void) { return true; };
	~Obj();
	void Update(const GameCtl& ctl, weakListObj objList);	// voidをGameCtlクラスの参照に変ええる

	// 関数ー 仮想関数 死んでるかどうかの判定関数 死んでた場合真を返す =通常は死んでない
	virtual bool CheckDeath(void) { return false; };

	// 指定した型と同じかどうか見る
	virtual bool CheckObjType(OBJ_TYPE type) = 0;// 叙述関数は真偽だから返り値は基本的にbool

	virtual void Draw(void);	// 描画
	void Draw(unsigned int id);	// id指定
	const VECTOR2& GetPos(void);// 座標
	// IDをどう指定するか id,id,ﾌﾚｰﾑ数,ｲﾝﾀｰﾊﾞﾙ(間隔),ﾙｰﾌﾟするかどうか
	bool AddAnim(std::string animName, int id_x, int id_y, int frame, int inv, bool loop);
	bool SetAnim(std::string animName);
	std::string GetAnim(void);

private:
	virtual void SetMove(const GameCtl& ctl, weakListObj objList) = 0;	// ｱﾄﾞﾚｽなし　純粋仮想関数

	std::map <std::string, int[ANIM_TBL_MAX]>animTable;		// ｱﾆﾒｰｼｮﾝが始まったらｶｳﾝﾄｱｯﾌﾟする
	std::string animName;		// 表示ｱﾆﾒｰｼｮﾝ名

protected:
	bool animEndFlag;			// ｱﾆﾒｰｼｮﾝ最終ｺﾏ到達ﾌﾗｸﾞ
	unsigned int animCnt;		// ｱﾆﾒｰｼｮﾝｶｳﾝﾀ
	const VECTOR2 drawOffset;	// 描画ｵﾌｾｯﾄ
	VECTOR2 pos;				// 座標	
	// pos &pos どちらでもよい 参照元が消える可能性があるなら&はいらない
	void SetPos(VECTOR2 pos);

	std::string imageName;		// 表示画像ﾌｧｲﾙ名
	VECTOR2 divSize;			// 分割ｻｲｽﾞ　ﾏｽ目のｻｲｽﾞと同じ
	VECTOR2 divCnt;				// 分割数
	DIR dir;					// 向き
	bool visible;				// 表示・非表示

};