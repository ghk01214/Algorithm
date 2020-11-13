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

void Swap(int* a, int* b)
{
	int iTemp = *a;
	*a = *b;
	*b = iTemp;
}

void Heapify(int* iElement, int iSize)
{
	for (int i = 0; i < iSize; ++i)
	{
		int iParent = (i - 1) / 2;

		while (iParent >= 0 && iElement[iParent] < iElement[i])
		{
			Swap(&iElement[iParent], &iElement[i]);

			i = iParent;
			iParent = (i - 1) / 2;
		}
	}
}

void HeapSort(int* iElement, int iSize)
{
	Heapify(iElement, iSize);

	for (int i = iSize - 1; i > 0; --i)
	{
		Swap(&iElement[0], &iElement[i]);

		Heapify(iElement, i);
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

	std::cout << "Èü Á¤·Ä Àü" << std::endl;

	PrintArray(iElement, Num::Size);
	HeapSort(iElement, Num::Size);

	std::cout << "Èü Á¤·Ä ÈÄ" << std::endl;

	PrintArray(iElement, Num::Size);
}