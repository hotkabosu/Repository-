#include "Dxlib.h"
#include "VECTOR2.h"
#include "ImageMng.h"

const VEC_INT& ImageMng::GetID(std::string f_name)
{
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(1); // サイズ1の配列
		imgMap[f_name][0] = LoadGraph(f_name.c_str());
		// [Map分][VEC_INT分]	右　ｴﾗｰの時はｷｬｽﾄできない
	}
	return imgMap[f_name];
	// 返り値としてほしい まずあるかどうかを問い合わせる
}


const VEC_INT& ImageMng::GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt)
{
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(divCnt.x * divCnt.y);
		LoadDivGraph(f_name.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y,
			divSize.x, divSize.y, &imgMap[f_name][0]);
	}
	return imgMap[f_name];
}

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}
