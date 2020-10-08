#include <iostream>
#include <random>
#define END 10

class Sort
{
private:
	int iArray[END];
public:
	Sort();
	void PrintArray();
	void MergeSort(int, int);
	void Merge(int, int, int);
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

void Sort::MergeSort(int iLeft, int iRight)
{
	if (iLeft < iRight)
	{
		int iMiddle = (iLeft + iRight) / 2;

		Sort::MergeSort(iLeft, iMiddle);
		Sort::MergeSort(iMiddle + 1, iRight);
		Sort::Merge(iLeft, iMiddle, iRight);
	}
}

void Sort::Merge(int iLeft, int iMiddle, int iRight)
{
	int i = iLeft;
	int j = iMiddle + 1;
	int k = iLeft;
	int iTempArray[END] = {};

	while (i <= iMiddle && j <= iRight)
	{
		if (Sort::iArray[i] <= Sort::iArray[j])
		{
			iTempArray[k++] = Sort::iArray[i++];
		}
		else
		{
			iTempArray[k++] = Sort::iArray[j++];
		}
	}

	if (i > iMiddle)
	{
		for (int a = j; a <= iRight; ++a)
		{
			iTempArray[k++] = Sort::iArray[a];
		}
	}
	else
	{
		for (int a = i; a <= iMiddle; ++a)
		{
			iTempArray[k++] = Sort::iArray[a];
		}
	}

	for (int a = iLeft; a <= iRight; ++a)
	{
		Sort::iArray[a] = iTempArray[a];
	}
}

Sort::~Sort()
{

}

void operate()
{
	Sort sSort;

	std::cout << "\n\t합병 정렬" << std::endl;

	std::cout << "\n\n\t정렬 전" << std::endl;
	sSort.PrintArray();
	sSort.MergeSort(0, END - 1);

	std::cout << "\n\n\t정렬 후" << std::endl;
	sSort.PrintArray();
}