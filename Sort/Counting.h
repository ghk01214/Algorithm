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

void CountingSort(int* iElement, int iSize)
{
	int iMax = iElement[0];
	int iMin = iElement[0];

	for (int i = 1; i < iSize; ++i)
	{
		if (iElement[i] < iMin)
			iMin = iElement[i];

		if (iElement[i] > iMax)
			iMax = iElement[i];
	}

	int* iCount = new int[iMax];

	for (int i = 0; i < iMax; ++i)
	{
		iCount[i] = 0;
	}

	for (int i = 0; i < iSize; ++i)
	{
		++iCount[iElement[i]];
	}

	for (int i = iMin + 1; i < iMax; ++i)
	{
		iCount[i] += iCount[i - 1];
	}

	int* iTemp = new int[iSize];

	for (int i = iSize - 1; i > 0; --i)
	{
		iTemp[iCount[iElement[i]]] = iElement[i];
		--iCount[iElement[i]];
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

	std::cout << "계수 정렬 전" << std::endl;

	PrintArray(iElement, Num::Size);
	CountingSort(iElement, Num::Size);

	std::cout << "계수 정렬 후" << std::endl;

	PrintArray(iElement, Num::Size);
}