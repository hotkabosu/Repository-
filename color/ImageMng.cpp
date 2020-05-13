#include "Dxlib.h"
#include "VECTOR2.h"
#include "ImageMng.h"

const VEC_INT& ImageMng::GetID(std::string f_name)
{
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(1); // �T�C�Y1�̔z��
		imgMap[f_name][0] = LoadGraph(f_name.c_str());
		// [Map��][VEC_INT��]	�E�@�װ�̎��ͷ��Ăł��Ȃ�
	}
	return imgMap[f_name];
	// �Ԃ�l�Ƃ��Ăق��� �܂����邩�ǂ�����₢���킹��
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
