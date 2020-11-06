#pragma once
#include <iostream>
#include <random>

enum Num
{
	Size = 10
};

void PrintArray(int* iElement, int iSize)
{
	for (int i = 0; i < iSize; ++i)
	{
		std::cout << iElement[i] << " ";
	}

	std::cout << std::endl << std::endl;
}

void InsertionSort(int* iElement, int iSize)
{
	for (int i = 1; i < iSize; ++i)
	{
		int iKey = iElement[i];
		int j;

		for (j = i; j > 0 && iElement[j - 1] > iKey; --j)
		{
			iElement[j] = iElement[j - 1];
		}

		iElement[j] = iKey;
	}
}

void operate()
{
	int iElement[Num::Size];

	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<int> uDis(0, 100);

	for (int i = 0; i < Num::Size; ++i)
	{
		iElement[i] = uDis(mGen);
	}

	std::cout << "»ðÀÔ Á¤·Ä Àü" << std::endl;

	PrintArray(iElement, Num::Size);
	InsertionSort(iElement, Num::Size);

	std::cout << "»ðÀÔ Á¤·Ä ÈÄ" << std::endl;

	PrintArray(iElement, Num::Size);
}