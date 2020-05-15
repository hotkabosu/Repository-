#include "Dxlib.h"
#include "VECTOR2.h"
#include "ImageMng.h"

ImageMng* ImageMng::s_Instance = nullptr;	// 初期位置


//const VEC_INT& ImageMng::GetID(std::string f_name)
//{
//	if (imgMap.find(f_name) == imgMap.end())
//	{
//		imgMap[f_name].resize(1); // サイズ1の配列
//		imgMap[f_name][0] = LoadGraph(f_name.c_str());
//		// [Map分][VEC_INT分]	右　ｴﾗｰの時はｷｬｽﾄできない
//	}
//	return imgMap[f_name];
//	// 返り値としてほしい まずあるかどうかを問い合わせる
//}


//const VEC_INT& ImageMng::GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt)
//{
//	if (imgMap.find(f_name) == imgMap.end())
//	{
//		imgMap[f_name].resize(divCnt.x * divCnt.y);
//		LoadDivGraph(f_name.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y,
//			divSize.x, divSize.y, &imgMap[f_name][0]);
//	}
//	return imgMap[f_name];
//}

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}


const VEC_INT& ImageMng::GetID(const std::string& key)
{
	GetID(key, key);// 後ろのkeyはしたのfilenameとして扱われる


	return imgMap[key];	// VecIntっていう塊を返す 0とかがintだからダメ
}

const VEC_INT& ImageMng::GetID(const std::string& key, const std::string& fileName)
{
	if (imgMap.find(key) == imgMap.end())
	{
		// resizeする
		imgMap[key].resize(1);
		imgMap[key][0] = LoadGraph(fileName.c_str());	// ここでデータを作る
	}
	//loaddivgraphのを1，1固定する
	return imgMap[key];
}

const VEC_INT& ImageMng::GetID(const std::string& key, const std::string& fileName,
	const VECTOR2& divSize, const VECTOR2& divCnt)
{
	// char画像で使うからかもしれない
	if (imgMap.find(key) == imgMap.end())
	{
		// resize葉要素の総数＝LoadDivGraphの総コマ数
		imgMap[key].resize(divCnt.x * divCnt.y);
		// [0]あとplayerを0にしたときに何もでなくなる
		LoadDivGraph(
			fileName.c_str(),
			divCnt.x * divCnt.y,		// 総コマ数
			divCnt.x, divCnt.y,		// 横マス数　縦マス数
			divSize.x, divSize.y,	// サイズX　サイズY
			&imgMap[key][0]);		// 配列　先頭のﾎﾟｲﾝﾀだからimgMapの0番目
	}
	return imgMap[key];
}
