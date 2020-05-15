#pragma once
#include <vector>
#include <map>
#include <mutex>

class VECTOR2;
using VEC_INT = std::vector<int>;
#define lpImageMng ImageMng::GetInstance()
//#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

// KEYを指定 GET
#define IMAGE_ID(KEY)(ImageMng::GetInstance().GetID(KEY))
// KEYとFILE_NAME指定SET KEY=名前　F_NAME=ﾌｫﾙﾀﾞの名前
#define SET_IMAGE_ID(KEY,F_NAME)(ImageMng::GetInstance().GetID(KEY,F_NAME))

class ImageMng
{
public:
	//static ImageMng& GetInstance(void)
	//{
	//	static ImageMng s_Instance;
	//	return (s_Instance);
	//}
	static ImageMng& GetInstance()
	{
		// GetInstanceならnewしたうえで返す(return)する

		// 不定値になるからnullを入れる nullptrの時はｲﾝｽﾀﾝｽしてよい　ないならダメ
		// GetInstanceはImageMngだからｺﾝｽﾄﾗｸﾀを呼べる
		// すでに作ってたら読んじゃだめだけどな　まだ作ってないときだけｲﾝｽﾀﾝｽしてよい
		// ｺﾝｽﾄﾗｸﾀよべ=ｲﾝｽﾀﾝｽしろ　動的ｼﾝｸﾞﾙﾄﾝ　必要になるまでﾒﾓﾘ上にﾛｰﾄﾞされない
		if (s_Instance == nullptr)		// nullptrの時によぶ
		{
			// s_Instanceの際ポインタを格納
			s_Instance = new ImageMng();
		}

		// thisはまだ存在していないから書けない　
		// *ならs_Instanceだけでも良いが
		// 参照返しだから *をつける　とポインタの先の実態指定がある　実体参照で返す
		return 	(*s_Instance);
	}

	const VEC_INT& GetID(const std::string& key);		// ID取得用関数
	// 読み込むときの名前、キーにしたい名前を変えれるやつ
	const VEC_INT& GetID(const std::string& key, const std::string& fileName);		// ID取得用関数
	// 分割サイズと分割数を足したﾊﾞｰｼﾞｮﾝ 生でアクセスしてるとデータが消える可能性がある
	//　動かしている最中でデータが書き換わるならｺﾋﾟｰ
	const VEC_INT& GetID(const std::string& key, const std::string& fileName,
		const VECTOR2& divSize, const VECTOR2& divCnt);


	~ImageMng();

private:
	ImageMng();

	bool(ImageMng::* ImagePtr)(void);

	std::map<std::string, VEC_INT> imgMap;

	// 変数 ｼﾝｸﾞﾙﾄﾝのｲﾝｽﾀﾝｽ	実体をcpp側に書く
	static ImageMng* s_Instance;

};
