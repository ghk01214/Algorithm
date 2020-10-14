#include <iostream>
#include <string>

class EString
{
private:
	std::string sString[2];
	int iLength[2];
	int** iEdit;
	int iDelete;
	int iInsert;
	int iChange;
public:
	EString();
	void Input();
	int EditDistance();
	int Minimum(int, int, int);
	void Output();
	~EString();
};

EString::EString()
{
	EString::iDelete = EString::iInsert = 1;
	EString::iChange = 2;
}

EString::~EString()
{
	for (int i = 0; i < EString::iLength[1]; ++i)
	{
		delete[] EString::iEdit[i];
	}

	delete[] EString::iEdit;
}

void EString::Input()
{
	std::cout << "1번 문자열 : ";
	std::cin >> EString::sString[0];

	std::cout << "2번 문자열 : ";
	std::cin >> EString::sString[1];

	EString::iLength[0] = EString::sString[0].length();
	EString::iLength[1] = EString::sString[1].length();

	EString::iEdit = new int* [EString::iLength[0] + 1];

	for (int i = 0; i < EString::iLength[0] + 1; ++i)
	{
		EString::iEdit[i] = new int[EString::iLength[1] + 1];
	}
}

int EString::EditDistance()
{
	//2차원 배열의 첫 열에 삭제 비용 초기화
	for (int i = 0; i < EString::iLength[0] + 1; ++i)
	{
		EString::iEdit[i][0] = i;
	}

	//2차원 배열의 첫 행에 삽입 비용 초기화
	for (int i = 0; i < EString::iLength[1] + 1; ++i)
	{
		EString::iEdit[0][i] = i;
	}

	int c;

	for (int i = 1; i < EString::iLength[0] + 1; ++i)
	{
		for (int j = 1; j < EString::iLength[1] + 1; ++j)
		{
			if (EString::sString[0][i - 1] == EString::sString[1][j - 1])
			{
				c = 0;
			}
			else
			{
				c = EString::iChange;
			}

			EString::iEdit[i][j] = EString::Minimum(EString::iEdit[i - 1][j] + EString::iDelete, EString::iEdit[i][j - 1] + EString::iInsert, EString::iEdit[i - 1][j - 1] + c);
		}
	}

	return EString::iEdit[EString::iLength[0]][EString::iLength[1]];
}

int EString::Minimum(int i, int j, int k)
{
	int iTemp;

	if (i < j)
	{
		iTemp = i;
	}
	else
	{
		iTemp = j;
	}

	if (iTemp < k)
	{
		return iTemp;
	}
	else
	{
		return k;
	}
}

void EString::Output()
{
	std::cout << std::endl << std::endl << "리벤슈테인 거리 : " << EString::EditDistance() << std::endl;

	std::cout << "\n편집 테이블" << std::endl;

	for (int i = 0; i < EString::iLength[0] + 1; ++i)
	{
		for (int j = 0; j < EString::iLength[1] + 1; ++j)
		{
			std::cout << EString::iEdit[i][j] << "\t";
		}

		std::cout << std::endl;
	}
}

void operate()
{
	EString eString;

	eString.Input();
	eString.Output();
}