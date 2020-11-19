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

	for (int i = 1; i < iSize; ++i)
	{
		if (iElement[i] > iMax)
			iMax = iElement[i];
	}

	int* iCount = new int[iMax + 1] {};
	int* iSort = new int[iSize] {};

	for (int i = 0; i < iSize; ++i)
		++iCount[iElement[i]];

	for (int i = 1; i <= iMax; ++i)
		iCount[i] += iCount[i - 1];

	for (int i = 0; i < iSize; ++i)
	{
		iSort[iCount[iElement[i]] - 1] = iElement[i];
		--iCount[iElement[i]];
	}

	for (int i = 0; i < iSize; ++i)
		iElement[i] = iSort[i];

	delete[] iCount;
	delete[] iSort;

	iCount = nullptr;
	iSort = nullptr;
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