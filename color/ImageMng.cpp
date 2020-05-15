#include "Dxlib.h"
#include "VECTOR2.h"
#include "ImageMng.h"

ImageMng* ImageMng::s_Instance = nullptr;	// �����ʒu


//const VEC_INT& ImageMng::GetID(std::string f_name)
//{
//	if (imgMap.find(f_name) == imgMap.end())
//	{
//		imgMap[f_name].resize(1); // �T�C�Y1�̔z��
//		imgMap[f_name][0] = LoadGraph(f_name.c_str());
//		// [Map��][VEC_INT��]	�E�@�װ�̎��ͷ��Ăł��Ȃ�
//	}
//	return imgMap[f_name];
//	// �Ԃ�l�Ƃ��Ăق��� �܂����邩�ǂ�����₢���킹��
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
	GetID(key, key);// ����key�͂�����filename�Ƃ��Ĉ�����


	return imgMap[key];	// VecInt���Ă������Ԃ� 0�Ƃ���int������_��
}

const VEC_INT& ImageMng::GetID(const std::string& key, const std::string& fileName)
{
	if (imgMap.find(key) == imgMap.end())
	{
		// resize����
		imgMap[key].resize(1);
		imgMap[key][0] = LoadGraph(fileName.c_str());	// �����Ńf�[�^�����
	}
	//loaddivgraph�̂�1�C1�Œ肷��
	return imgMap[key];
}

const VEC_INT& ImageMng::GetID(const std::string& key, const std::string& fileName,
	const VECTOR2& divSize, const VECTOR2& divCnt)
{
	// char�摜�Ŏg�����炩������Ȃ�
	if (imgMap.find(key) == imgMap.end())
	{
		// resize�t�v�f�̑�����LoadDivGraph�̑��R�}��
		imgMap[key].resize(divCnt.x * divCnt.y);
		// [0]����player��0�ɂ����Ƃ��ɉ����łȂ��Ȃ�
		LoadDivGraph(
			fileName.c_str(),
			divCnt.x * divCnt.y,		// ���R�}��
			divCnt.x, divCnt.y,		// ���}�X���@�c�}�X��
			divSize.x, divSize.y,	// �T�C�YX�@�T�C�YY
			&imgMap[key][0]);		// �z��@�擪���߲��������imgMap��0�Ԗ�
	}
	return imgMap[key];
}
