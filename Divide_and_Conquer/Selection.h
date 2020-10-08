#include <iostream>
#include <random>
#define SIZE 10

class Array
{
private:
	int iArray[SIZE];
	int iPivot;
public:
	Array();
	void PrintArray();
	void FindMinAndMax(int*, int*);
	int FindNLeast(int, int, int);
	int SearchPivot(int, int);
	void Swap(int*, int*);
	~Array();
};

void operate()
{
	Array aArray;
	int iMenu;
	int iMin = 0, iMax = 0;
	int iNum = 0, iElement = 0;

	std::cout << "\n\tSelect Menu : ";
	std::cin >> iMenu;

	std::cout << "\n\t배열 원소 목록" << std::endl;
	aArray.PrintArray();

	switch (iMenu)
	{
	case 1:
	{
		aArray.FindMinAndMax(&iMin, &iMax);

		std::cout << "\n\n\tThe Minimum Element = " << iMin << std::endl << std::endl;
		break;
	}
	case 2:
	{
		aArray.FindMinAndMax(&iMin, &iMax);

		std::cout << "\n\n\tThe Minimum Element = " << iMin;
		std::cout << "\n\n\tThe Maximum Element = " << iMax << std::endl << std::endl;
		break;
	}
	case 3:
	{
		std::cout << "\n\n\t찾을 위치 입력 : ";
		std::cin >> iNum;

		iElement = aArray.FindNLeast(0, SIZE - 1, iNum);

		std::cout << "\n\n\tn번째 작은 원소 = " << iElement << std::endl << std::endl;
		break;
	}
	default:
		break;
	}
}

Array::Array()
{
	Array::iPivot = 0;

	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<int> uDis(0, 100);

	for (int i = 0; i < SIZE; ++i)
	{
		Array::iArray[i] = uDis(mGen);
	}
}

Array::~Array()
{

}

void Array::PrintArray()
{
	std::cout << "\t";

	for (int i = 0; i < SIZE; ++i)
		std::cout << Array::iArray[i] << " ";

	std::cout << std::endl;
}

void Array::FindMinAndMax(int* iMin, int* iMax)
{
	if (Array::iArray[0] < Array::iArray[1])
	{
		*iMin = Array::iArray[0];
		*iMax = Array::iArray[1];
	}
	else
	{
		*iMin = Array::iArray[1];
		*iMax = Array::iArray[0];
	}

	for (int i = 2; i < SIZE; ++i)
	{
		if (*iMin > Array::iArray[i])
		{
			*iMin = Array::iArray[i];
		}
		else if (*iMax < Array::iArray[i])
		{
			*iMax = Array::iArray[i];
		}
	}
}

int Array::FindNLeast(int iLeft, int iRight, int iNum)
{
	if (iLeft >= iRight)
		return -1;

	int iPivot = Array::SearchPivot(iLeft, iRight);

	if (iPivot + 1 == iNum)
	{
		return Array::iArray[iPivot];
	}
	else if (iPivot + 1 < iNum)
	{
		Array::FindNLeast(iPivot + 1, iRight, iNum);
	}
	else
	{
		Array::FindNLeast(iLeft, iPivot - 1, iNum);
	}
}

int Array::SearchPivot(int iStart, int iEnd)
{
	int iIndex = iStart;

	for (int i = iStart; i < iEnd; ++i)
	{
		if (Array::iArray[i] <= Array::iArray[iEnd])
		{
			Array::Swap(&i, &iIndex);
			++iIndex;
		}
	}

	Array::Swap(&iIndex, &iEnd);

	return iIndex;
}

void Array::Swap(int* iLeft, int* iRight)
{
	int iTemp = Array::iArray[*iLeft];
	Array::iArray[*iLeft] = Array::iArray[*iRight];
	Array::iArray[*iRight] = iTemp;
}