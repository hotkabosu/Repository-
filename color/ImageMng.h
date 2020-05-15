#pragma once
#include <vector>
#include <map>
#include <mutex>

class VECTOR2;
using VEC_INT = std::vector<int>;
#define lpImageMng ImageMng::GetInstance()
//#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

// KEY���w�� GET
#define IMAGE_ID(KEY)(ImageMng::GetInstance().GetID(KEY))
// KEY��FILE_NAME�w��SET KEY=���O�@F_NAME=̫��ނ̖��O
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
		// GetInstance�Ȃ�new���������ŕԂ�(return)����

		// �s��l�ɂȂ邩��null������ nullptr�̎��Ͳݽ�ݽ���Ă悢�@�Ȃ��Ȃ�_��
		// GetInstance��ImageMng������ݽ�׸����Ăׂ�
		// ���łɍ���Ă���ǂ񂶂Ⴞ�߂����ǂȁ@�܂�����ĂȂ��Ƃ������ݽ�ݽ���Ă悢
		// �ݽ�׸����=�ݽ�ݽ����@���I�ݸ���݁@�K�v�ɂȂ�܂���؏��۰�ނ���Ȃ�
		if (s_Instance == nullptr)		// nullptr�̎��ɂ��
		{
			// s_Instance�̍ۃ|�C���^���i�[
			s_Instance = new ImageMng();
		}

		// this�͂܂����݂��Ă��Ȃ����珑���Ȃ��@
		// *�Ȃ�s_Instance�����ł��ǂ���
		// �Q�ƕԂ������� *������@�ƃ|�C���^�̐�̎��Ԏw�肪����@���̎Q�ƂŕԂ�
		return 	(*s_Instance);
	}

	const VEC_INT& GetID(const std::string& key);		// ID�擾�p�֐�
	// �ǂݍ��ނƂ��̖��O�A�L�[�ɂ��������O��ς������
	const VEC_INT& GetID(const std::string& key, const std::string& fileName);		// ID�擾�p�֐�
	// �����T�C�Y�ƕ������𑫂����ް�ޮ� ���ŃA�N�Z�X���Ă�ƃf�[�^��������\��������
	//�@�������Ă���Œ��Ńf�[�^�����������Ȃ��߰
	const VEC_INT& GetID(const std::string& key, const std::string& fileName,
		const VECTOR2& divSize, const VECTOR2& divCnt);


	~ImageMng();

private:
	ImageMng();

	bool(ImageMng::* ImagePtr)(void);

	std::map<std::string, VEC_INT> imgMap;

	// �ϐ� �ݸ���݂̲ݽ�ݽ	���̂�cpp���ɏ���
	static ImageMng* s_Instance;

};
