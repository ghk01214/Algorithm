#include <iostream>
#include <random>
#define END 10

class Sort
{
private:
	int iArray[END];
	int iPivot;
public:
	Sort();
	void PrintArray();
	void QuickSort(int, int);
	void Swap(int*, int*);
	~Sort();
};

Sort::Sort()
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<unsigned int> uDis(0, 9999);

	for (int i = 0; i < END; ++i)
	{
		Sort::Sort::iArray[i] = uDis(mGen);
	}
}

void Sort::PrintArray()
{
	std::cout << "\tiArray[" << END << "] = { ";

	for (int i = 0; i < END; ++i)
	{
		std::cout << Sort::iArray[i] << ", ";
	}

	std::cout << " }" << std::endl << std::endl;
}

void Sort::QuickSort(int iLeft, int iRight)
{
	if (iLeft >= iRight)
		return;

	Sort::iPivot = iLeft;
	int iStart = iLeft + 1;
	int iEnd = iRight;

	while (iStart <= iEnd)
	{
		while (Sort::iArray[Sort::iPivot] >= Sort::iArray[iStart] && iStart <= iRight)
			++iStart;

		while (Sort::iArray[Sort::iPivot] <= Sort::iArray[iEnd] && iEnd > iLeft)
			--iEnd;

		if (iStart > iEnd)
			Sort::Swap(&Sort::iArray[Sort::iPivot], &Sort::iArray[iEnd]);
		else
			Sort::Swap(&Sort::iArray[iStart], &Sort::iArray[iEnd]);
	}

	Sort::QuickSort(iLeft, iEnd - 1);
	Sort::QuickSort(iEnd + 1, iRight);
}

void Sort::Swap(int* iLeft, int* iRight)
{
	int iTemp = *iLeft;
	*iLeft = *iRight;
	*iRight = iTemp;
}

Sort::~Sort()
{

}

void operate()
{
	Sort sSort;

	std::cout << "\n\t퀵 정렬" << std::endl;

	std::cout << "\n\n\t정렬 전" << std::endl;
	sSort.PrintArray();
	sSort.QuickSort(0, END - 1);

	std::cout << "\n\n\t정렬 후" << std::endl;
	sSort.PrintArray();
}