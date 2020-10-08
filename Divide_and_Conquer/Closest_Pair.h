#include <iostream>
#include <random>
#include <cmath>
#define NUM 20

typedef struct Coordinate
{
	double dX;
	double dY;
} Pos;

class Position
{
private:
	Pos* pPosition;
	Pos* pPairs;
	double dDistance;
	int iPivot;
public:
	Position(int);
	void PrintPos(int);
	double FindClosest(int, int, int);
	void PrintPairs();
	double Distance(Pos, Pos);
	void QuickSort(int, int);
	void Swap(Pos*, Pos*);
	double ReturnDistance();
	void ReturnPos(Pos*);
	~Position();
};

void operate()
{
	int iNum;

	std::cout << "생성할 점의 개수 : ";
	std::cin >> iNum;

	Position pPos(iNum);
	Pos* pTemp = new Pos[2];

	pPos.PrintPos(iNum);
	//pPos.QuickSort(0, iNum - 1);
	pPos.FindClosest(iNum, 0, iNum - 1);
	pPos.ReturnPos(pTemp);

	std::cout << "좌표 : \n{ " << pTemp[0].dX << ", " << pTemp[0].dY << " }" << std::endl << "{ " << pTemp[1].dX << ", " << pTemp[1].dY << " }" << std::endl;;
	std::cout << "길이 : " << pPos.ReturnDistance() << std::endl;
}

Position::Position(int iSize)
{
	Position::pPosition = new Pos[iSize]();
	Position::pPairs = new Pos[2]();
	Position::dDistance = -1;

	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<double> uDis(0.0, 100.0);

	for (int i = 0; i < iSize; ++i)
	{
		Position::pPosition[i] = { uDis(mGen), uDis(mGen) };
	}
}

Position::~Position()
{
	delete[] pPosition;
	delete[] pPairs;
}

void Position::PrintPos(int iSize)
{
	for (int i = 0; i < iSize; ++i)
	{
		std::cout << "{ " << Position::pPosition[i].dX << ", " << Position::pPosition[i].dY << " }" << std::endl;
	}
}

double Position::FindClosest(int iSize, int iLeft, int iRight)
{
	if (iSize == 2)
	{
		for (int i = 0; i < 2; ++i)
			Position::pPairs[i] = Position::pPosition[i];

		Position::dDistance = Position::Distance(Position::pPairs[0], Position::pPairs[1]);

		return Position::dDistance;
	}
	else if (iSize == 3)
	{
		Pos* pTemp = new Pos[iSize];

		double dDistance[3], dMin;

		dDistance[0] = Position::Distance(Position::pPosition[0], Position::pPosition[1]);
		dDistance[1] = Position::Distance(Position::pPosition[0], Position::pPosition[2]);
		dDistance[2] = Position::Distance(Position::pPosition[1], Position::pPosition[2]);

		if (dDistance[0] < dDistance[1])
		{
			dMin = dDistance[0];

			for (int i = 0; i < 1; ++i)
				pTemp[i] = Position::pPosition[i];
		}
		else
		{
			dMin = dDistance[1];

			pTemp[0] = Position::pPosition[0];
			pTemp[1] = Position::pPosition[2];
		}

		if (dDistance[2] < dMin)
		{
			dMin = dDistance[2];

			for (int i = 1; i < 3; ++i)
				pTemp[i] = Position::pPosition[i];
		}

		for (int i = 0; i < 2; ++i)
			Position::pPairs[i] = pTemp[i];

		Position::dDistance = dMin;
		delete[] pTemp;

		return dMin;
	}
	else
	{
		int iMiddle = (iLeft + iRight) / 2;
		double dLeft, dRight, dRange;

		dLeft = Position::FindClosest(iMiddle - iLeft + 1, iLeft, iMiddle);
		dRight = Position::FindClosest(iRight - iMiddle, iMiddle + 1, iRight);

		if (dLeft < dRight)
			dRange = dLeft;
		else
			dRange = dRight;

		Pos* pTemp = new Pos[iSize];
		int iTemp = 0;

		double dTemp = -1;

		for (int i = iLeft; i <= iRight; ++i)
		{
			if (abs((Position::pPosition + i)->dX - (Position::pPosition + iMiddle)->dX) < dRange)
			{
				(pTemp + iTemp)->dX = (Position::pPosition + i)->dX;
				(pTemp + iTemp)->dY = (Position::pPosition + i)->dY;
				++iTemp;
			}
		}

		for (int i = 0; i < iTemp; ++i)
		{
			for (int j = i + 1; j < iTemp; ++j)
			{
				if (dRange < Distance(*(pTemp + i), *(pTemp + j)))
				{
					dTemp = dRange;
				}
				else
				{
					dTemp = Distance(*(pTemp + i), *(pTemp + j));
				}

				if (dTemp < dRange)
				{
					dRange = dTemp;

					if (dTemp < Position::dDistance)
					{
						*Position::pPairs = *(pTemp + i);
						*(Position::pPairs + 1) = *(pTemp + j);
					}
				}
			}
		}

		Position::dDistance = dRange;
		delete[] pTemp;

		return dRange;
	}
}

void Position::PrintPairs()
{
	for (int i = 0; i < 2; ++i)
		std::cout << Position::pPairs[i].dX << ", " << Position::pPairs[i].dY << std::endl;
}

double Position::Distance(Pos pA, Pos pB)
{
	double dDistance;

	dDistance = sqrt(pow(pA.dX - pB.dX, 2) + pow(pA.dY - pB.dY, 2));

	if (Position::dDistance == -1 || dDistance < Position::dDistance)
	{
		Position::pPairs[0] = pA;
		Position::pPairs[1] = pB;

		Position::dDistance = dDistance;
	}

	return dDistance;
}

void Position::QuickSort(int iLeft, int iRight)
{
	if (iLeft >= iRight)
		return;

	Position::iPivot = iLeft;
	int iStart = iLeft + 1;
	int iEnd = iRight;

	while (iStart <= iEnd)
	{
		while (Position::pPosition[Position::iPivot].dX >= Position::pPosition[iStart].dX && iStart <= iRight)
			++iStart;

		while (Position::pPosition[Position::iPivot].dX <= Position::pPosition[iEnd].dX && iEnd > iLeft)
			--iEnd;

		if (iStart > iEnd)
			Position::Swap(&Position::pPosition[Position::iPivot], &Position::pPosition[iEnd]);
		else
			Position::Swap(&Position::pPosition[iStart], &Position::pPosition[iEnd]);
	}

	Position::QuickSort(iLeft, iEnd - 1);
	Position::QuickSort(iEnd + 1, iRight);
}

void Position::Swap(Pos* iLeft, Pos* iRight)
{
	Pos iTemp = *iLeft;
	*iLeft = *iRight;
	*iRight = iTemp;
}

double Position::ReturnDistance()
{
	return Position::dDistance;
}

void Position::ReturnPos(Pos* pTemp)
{
	pTemp[0] = pPairs[0];
	pTemp[1] = pPairs[1];
}