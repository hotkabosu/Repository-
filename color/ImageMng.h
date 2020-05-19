#pragma once
#include <vector>
#include <map>
#include <mutex>

class VECTOR2;
using VEC_INT = std::vector<int>;
#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

class ImageMng
{
public:
	// static void Destroy(void);
	static ImageMng& GetInstance(void)
	{
		// std::call_once(initFlag, Create);
		static ImageMng s_Instance;
		return (s_Instance);
	}

	const VEC_INT& GetID(std::string f_name);
	const VEC_INT& GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt);

private:
	// static void Create(void);
	ImageMng();
	~ImageMng();

	bool(ImageMng::* ImagePtr)(void);
	std::map<std::string, VEC_INT> imgMap;
};


