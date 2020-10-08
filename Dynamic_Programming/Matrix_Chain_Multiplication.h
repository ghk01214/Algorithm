#include <iostream>
#define MAX 999999

int MinMatMult(int, int*);
int min(int, int);

void operate()
{
	int iNumber;

	std::cout << "���� ��� ���� : ";
	std::cin >> iNumber;

	int* iSize = new int[iNumber + 1];

	std::cout << "����� ũ�� �Է�(�Է� ���� + 1 ��ŭ) : ";

	for (int i = 0; i < iNumber + 1; ++i)
		std::cin >> iSize[i];

	std::cout << "���� ��� �ּ� ���� ȸ�� = " << MinMatMult(iNumber, iSize) << std::endl;

	delete[] iSize;
}

int MinMatMult(int iNumber, int* iSize)
{
	int** C = new int* [iNumber + 1];

	for (int i = 0; i < iNumber + 1; ++i)
	{
		C[i] = new int[iNumber + 1];
	}

	for (int i = 1; i <= iNumber; ++i)
	{
		C[i][i] = 0;
	}

	for (int s = 0; s < iNumber; ++s)
	{
		for (int i = 1; i <= iNumber - s; ++i)
		{
			int j = i + s;

			if (j == i)
			{
				C[i][j] = 0;
				continue;
			}
			else
			{
				C[i][j] = MAX;

				for (int k = i; k <= j - 1; ++k)
				{
					C[i][j] = min(C[i][j], C[i][k] + C[k + 1][j] + iSize[i - 1] * iSize[k] * iSize[j]);
				}
			}
		}
	}

	int result = C[1][iNumber];

	for (int i = 0; i < iNumber + 1; ++i)
	{
		delete[] C[i];
	}

	delete[] C;

	return result;
}

int min(int a, int b)
{
	if (a > b)
		return b;
	else
		return a;
}