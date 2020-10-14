#include <iostream>
#define MAX 10000

class Floyd
{
private:
	int iVertex;
	int** iDistance;
public:
	Floyd();
	/*void Input();
	void Initialize();*/
	void Table();
	void Distance();
	~Floyd();
};

Floyd::Floyd()
{
	Floyd::iVertex = 4;
	Floyd::iDistance = new int* [Floyd::iVertex];

	for (int i = 0; i < Floyd::iVertex; ++i)
	{
		Floyd::iDistance[i] = new int[Floyd::iVertex];
	}

	//가지 못 하는 방향의 가중치는 MAX로 초기화
	Floyd::iDistance[0][0] = 0;
	Floyd::iDistance[0][1] = 4;
	Floyd::iDistance[0][2] = 2;
	Floyd::iDistance[0][3] = MAX;

	Floyd::iDistance[1][0] = MAX;
	Floyd::iDistance[1][1] = 0;
	Floyd::iDistance[1][2] = 5;
	Floyd::iDistance[1][3] = MAX;

	Floyd::iDistance[2][0] = MAX;
	Floyd::iDistance[2][1] = -1;
	Floyd::iDistance[2][2] = 0;
	Floyd::iDistance[2][3] = MAX;

	Floyd::iDistance[3][0] = 3;
	Floyd::iDistance[3][1] = MAX;
	Floyd::iDistance[3][2] = MAX;
	Floyd::iDistance[3][3] = 0;
}

Floyd::~Floyd()
{
	for (int i = 0; i < Floyd::iVertex; ++i)
	{
		delete[] Floyd::iDistance[i];
	}

	delete[] Floyd::iDistance;
}

//void Floyd::Input()
//{
//	std::cout << "정점의 개수 : ";
//	std::cin >> Floyd::iVertex;
//}

//void Floyd::Initialize()
//{
//	Floyd::iDistance = new int* [Floyd::iVertex];
//
//	for (int i = 0; i < Floyd::iVertex; ++i)
//	{
//		Floyd::iDistance[i] = new int[Floyd::iVertex];
//	}
//
//	//가지 못 하는 방향의 가중치는 MAX로 초기화
//	Floyd::iDistance[0][0] = 0;
//	Floyd::iDistance[0][1] = 4;
//	Floyd::iDistance[0][2] = 2;
//	Floyd::iDistance[0][3] = MAX;
//
//	Floyd::iDistance[1][0] = MAX;
//	Floyd::iDistance[1][1] = 4;
//	Floyd::iDistance[1][2] = 2;
//	Floyd::iDistance[1][3] = MAX;
//
//	Floyd::iDistance[2][0] = MAX;
//	Floyd::iDistance[2][1] = 4;
//	Floyd::iDistance[2][2] = 2;
//	Floyd::iDistance[2][3] = MAX;
//
//	Floyd::iDistance[3][0] = 0;
//	Floyd::iDistance[3][1] = MAX;
//	Floyd::iDistance[3][2] = MAX;
//	Floyd::iDistance[3][3] = MAX;
//}

void Floyd::Table()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << Floyd::iDistance[i][j] << "\t";
		}

		std::cout << std::endl;
	}
}

void Floyd::Distance()
{
	for (int i = 0; i < Floyd::iVertex; ++i)
	{
		for (int j = 0; j < Floyd::iVertex; ++j)
		{
			for (int k = 0; k < Floyd::iVertex; ++k)
			{
				if (Floyd::iDistance[j][k] > Floyd::iDistance[j][i] + Floyd::iDistance[i][k])
				{
					Floyd::iDistance[j][k] = Floyd::iDistance[j][i] + Floyd::iDistance[i][k];
				}
			}
		}
	}
}

void operate()
{
	Floyd fFloyd;

	fFloyd.Table();
	fFloyd.Distance();
	std::cout << std::endl;
	fFloyd.Table();
}