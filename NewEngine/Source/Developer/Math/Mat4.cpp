#include "NewEngine/Header/Developer/Math/Mat4.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include "NewEngine/Header/Developer/Debug/DebugText.h"

Mat4::Mat4() :
	mat{
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0 }
{
}

Mat4::Mat4(
	float _00, float _01, float _02, float _03,
	float _10, float _11, float _12, float _13,
	float _20, float _21, float _22, float _23,
	float _30, float _31, float _32, float _33) :
	mat{
		_00,_01,_02,_03,
		_10,_11,_12,_13,
		_20,_21,_22,_23,
		_30,_31,_32,_33 }
{
}

Mat4 Mat4::Zero()
{
	return Mat4();
}

Mat4 Mat4::Identity()
{
	return
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
}

Mat4 Mat4::Inverse(const Mat4& mat)
{
	float sweepMat[4][8] = {};
	float tmpNum = 0;

	// �|���o���s��̏�����
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// �����ł�������s��i�� 4 * 4�j
			sweepMat[i][j] = mat.mat[i][j];

			// �P�ʍs��i�E 4 * 4�j
			sweepMat[i][j + 4] = (i == j) ? 1.0f : 0.0f;
		}
	}

	// �|���o���@
	for (int i = 0; i < 4; i++)
	{
		// �ő听����T������
		float max = MathUtil::Absolut(sweepMat[i][i]);
		int maxIndex = i;
		for (int j = i + 1; j < 4; j++)
		{
			if (max < MathUtil::Absolut(sweepMat[i][i]))
			{
				max = MathUtil::Absolut(sweepMat[i][i]);
				maxIndex = j;
			}
		}
		// �t�s�񋁂߂邩�ǂ���
		if (MathUtil::Absolut(sweepMat[maxIndex][i]) <= 0.000001f)
		{
			// ���߂�Ȃ��ꍇ�͒P�ʍs���Ԃ�
			return Identity();
		}

		// �ΏۂƂȂ�s��̑Ίp������1�ɂ���
		tmpNum = 1 / sweepMat[i][i];
		for (int j = 0; j < 8; j++)
		{
			sweepMat[i][j] *= tmpNum;
		}

		// �ΏۂƂȂ�s��̑Ίp�����ȊO��0�ɂ��邽��
		for (int j = 0; j < 4; j++)
		{
			if (i == j) continue;

			tmpNum = -sweepMat[j][i];
			for (int k = 0; k < 8; k++)
			{
				sweepMat[j][k] += sweepMat[i][k] * tmpNum;
			}
		}
	}

	// �t�s���Ԃ�
	Mat4 inverseMat = Mat4::Identity();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			inverseMat.mat[i][j] = sweepMat[i][j + 4];
		}
	}

	return inverseMat;
}

void Mat4::PrintMat(float x, float y, const Mat4& mat, const char* str)
{
	DebugText::GetInstance()->
		Printf(x, y, Color::white, str);
	DebugText::GetInstance()->
		Printf(x, y + 20, Color::white, "%f, %f, %f, %f",
			mat.mat[0][0], mat.mat[0][1], mat.mat[0][2], mat.mat[0][3]);
	DebugText::GetInstance()->
		Printf(x, y + 40, Color::white, "%f, %f, %f, %f",
			mat.mat[1][0], mat.mat[1][1], mat.mat[1][2], mat.mat[1][3]);
	DebugText::GetInstance()->
		Printf(x, y + 60, Color::white, "%f, %f, %f, %f",
			mat.mat[2][0], mat.mat[2][1], mat.mat[2][2], mat.mat[2][3]);
	DebugText::GetInstance()->
		Printf(x, y + 80, Color::white, "%f, %f, %f, %f",
			mat.mat[3][0], mat.mat[3][1], mat.mat[3][2], mat.mat[3][3]);
}

Mat4 Mat4::operator*(const Mat4& other) const
{
	return {
		mat[0][0] * other.mat[0][0] + mat[0][1] * other.mat[1][0] + mat[0][2] * other.mat[2][0] + mat[0][3] * other.mat[3][0],
		mat[0][0] * other.mat[0][1] + mat[0][1] * other.mat[1][1] + mat[0][2] * other.mat[2][1] + mat[0][3] * other.mat[3][1],
		mat[0][0] * other.mat[0][2] + mat[0][1] * other.mat[1][2] + mat[0][2] * other.mat[2][2] + mat[0][3] * other.mat[3][2],
		mat[0][0] * other.mat[0][3] + mat[0][1] * other.mat[1][3] + mat[0][2] * other.mat[2][3] + mat[0][3] * other.mat[3][3],

		mat[1][0] * other.mat[0][0] + mat[1][1] * other.mat[1][0] + mat[1][2] * other.mat[2][0] + mat[1][3] * other.mat[3][0],
		mat[1][0] * other.mat[0][1] + mat[1][1] * other.mat[1][1] + mat[1][2] * other.mat[2][1] + mat[1][3] * other.mat[3][1],
		mat[1][0] * other.mat[0][2] + mat[1][1] * other.mat[1][2] + mat[1][2] * other.mat[2][2] + mat[1][3] * other.mat[3][2],
		mat[1][0] * other.mat[0][3] + mat[1][1] * other.mat[1][3] + mat[1][2] * other.mat[2][3] + mat[1][3] * other.mat[3][3],

		mat[2][0] * other.mat[0][0] + mat[2][1] * other.mat[1][0] + mat[2][2] * other.mat[2][0] + mat[2][3] * other.mat[3][0],
		mat[2][0] * other.mat[0][1] + mat[2][1] * other.mat[1][1] + mat[2][2] * other.mat[2][1] + mat[2][3] * other.mat[3][1],
		mat[2][0] * other.mat[0][2] + mat[2][1] * other.mat[1][2] + mat[2][2] * other.mat[2][2] + mat[2][3] * other.mat[3][2],
		mat[2][0] * other.mat[0][3] + mat[2][1] * other.mat[1][3] + mat[2][2] * other.mat[2][3] + mat[2][3] * other.mat[3][3],

		mat[3][0] * other.mat[0][0] + mat[3][1] * other.mat[1][0] + mat[3][2] * other.mat[2][0] + mat[3][3] * other.mat[3][0],
		mat[3][0] * other.mat[0][1] + mat[3][1] * other.mat[1][1] + mat[3][2] * other.mat[2][1] + mat[3][3] * other.mat[3][1],
		mat[3][0] * other.mat[0][2] + mat[3][1] * other.mat[1][2] + mat[3][2] * other.mat[2][2] + mat[3][3] * other.mat[3][2],
		mat[3][0] * other.mat[0][3] + mat[3][1] * other.mat[1][3] + mat[3][2] * other.mat[2][3] + mat[3][3] * other.mat[3][3]
	};
}

Mat4& Mat4::operator*=(const Mat4& other)
{
	*this = *this * other;
	return *this;
};
