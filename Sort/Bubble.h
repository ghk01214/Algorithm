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

void BuubleSort(int* iElement, int iSize)
{
	for (int i = 0; i < iSize - 1; ++i)
	{
		bool bExchange = false;

		for (int j = 0; j < iSize - 1 - i; ++j)
		{
			if (iElement[j] > iElement[j + 1])
			{
				int iTemp = iElement[j + 1];
				iElement[j + 1] = iElement[j];
				iElement[j] = iTemp;

				bExchange = true;
			}
		}

		if (bExchange == false)
			break;
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

	std::cout << "버블 정렬 전" << std::endl;

	PrintArray(iElement, Num::Size);
	BuubleSort(iElement, Num::Size);

	std::cout << "버블 정렬 후" << std::endl;

	PrintArray(iElement, Num::Size);
}