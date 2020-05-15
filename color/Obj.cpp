#include "Dxlib.h"
#include "ImageMng.h"
#include "Obj.h"

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)
{
	dir = DIR_DOWN;	// DOWNは0
	visible = true;		// 最初は絶対true

}

Obj::Obj()
{
	dir = DIR_DOWN;
	visible = true;		// 最初は絶対true
}

// ｲﾝｽﾀﾝｽでくる　ここを呼ばないと描画できない
bool Obj::init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
//	lpImageMng.GetID(fileName, divSize, divCnt);	// ﾀｲﾐﾝｸﾞをｺﾝﾄﾛｰﾙして呼び出したい
	// 代入		色が逆になると逆に代入している　濃い　薄い
	imageName = fileName;
	this->divSize = divSize;
	this->divCnt = divCnt;
	return true;
}

bool Obj::init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos)
{
	init(fileName, divSize, divCnt);
	SetPos(pos);
	return true;
}

Obj::~Obj()
{
}

void Obj::Update(const GameCtl& ctl, weakListObj objList)
{
	SetMove(ctl, objList);	// 継承先にある 純粋仮想関数
}

void Obj::Draw(void)	 // 描画 何の画像のどこのｺﾏを描画するのか　
{
	if (imageName.length() == 0)
	{
		return;
	}
	unsigned int id = 0;	// idは0番
	if (animTable.find(animName) != animTable.end())
	{
		// ﾛｰｶﾙ変数 求める値はanimcount の割り算(/)の結果
		// 全体で3コマなら0，1，2　☆01222～にする
		int count = (animCnt / animTable[animName][ANIM_TBL_INV]);

		// (ﾙｰﾌﾟかどうか||ｶｳﾝﾄがﾌﾚｰﾑ数より小さいかどうか)
		if (animTable[animName][ANIM_TBL_LOOP]
			|| count < animTable[animName][ANIM_TBL_FRAME])
		{
			// 012,012を繰り返す つまり01はelseと同じになるからこちらで処理する
			count %= animTable[animName][ANIM_TBL_FRAME];
		}
		else
		{
			// 値が012222の処理が入る 都合上1つ大きい 
			count = animTable[animName][ANIM_TBL_FRAME] - 1;
			animEndFlag = true;//最終ｺﾏに到達
			visible = false;

		}
		// 加算する値は0だから影響がない
		// ANIM_TBL_START_IDが起点 FRAMEは-1でも大丈夫

		id = animTable[animName][ANIM_TBL_START_ID] + (int)dir
			+ count * divCnt.x;

		//id = animTable[animName][ANIM_TBL_START_ID] +(int)dir
		//	+ ((animCnt / animTable[animName][ANIM_TBL_INV])
		//	% animTable[animName][ANIM_TBL_FRAME])*divCnt.x; 同じ
	}
	animCnt++;
	if (id < IMAGE_ID(imageName).size())	// idが配列の範囲内かどうかのﾁｪｯｸ
	{
		if (visible)
		{
			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y,
				IMAGE_ID(imageName)[id], true);	// posのﾎﾟｼﾞｼｮﾝに描画 [id番号]
		}
	}
	// ファイルが読み込まれているか 有効な値かどうかもチェック

}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())	// idが配列の範囲内かどうかのﾁｪｯｸ
	{
		if (visible)
		{

			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y,
				IMAGE_ID(imageName)[id], true);
			// drawOffset追加で左上からﾏｽ目上に
		}
	}
}

const VECTOR2& Obj::GetPos(void)
{
	return pos;
}

bool Obj::AddAnim(std::string animName, int id_x, int id_y, int frame, int inv, bool loop)
{
	// ｷｰになる値をかく　animnameというstring型のものを使う
	animTable[animName][ANIM_TBL_START_ID] = divCnt.x * id_y + id_x;
	animTable[animName][ANIM_TBL_FRAME] = frame;
	animTable[animName][ANIM_TBL_INV] = inv;
	animTable[animName][ANIM_TBL_LOOP] = loop;
	return true;
}

bool Obj::SetAnim(std::string animName)
{
	if (Obj::animName == animName)	// 重複ﾁｪｯｸをしたほうが良い 
	{
		return true;
	}
	// find存在するかどうか 存在しない場合
	if (animTable.find(animName) == animTable.end())
	{
		return false;
	}
	// 重複してなく存在していた場合
	Obj::animName = animName;
	Obj::animCnt = 0;				// Obj::はどちらでもよい ﾛｰｶﾙ変数と誤解しないように
	animEndFlag = false;		// 2個目のif文の下　ｱﾆﾒｰｼｮﾝを切り替えない限りtrue
	 // ﾃﾞｰﾀが存在したらﾛｰｶﾙのanimNameに　存在しない場合はfalse
	return false;
}

std::string Obj::GetAnim(void)
{
	return animName;
}

void Obj::SetPos(VECTOR2 pos)
{
	Obj::pos = pos;
}