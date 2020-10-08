#include <iostream>

int SequentialSearch(int*, int, int);

void operate()
{
	int iArray[] = { 28, 32, 12, 94, 64, 5, 0, 6, 81, 45 };
	int iLength = sizeof(iArray) / sizeof(iArray[0]);
	char cInput[5];
	int iInput;
	int iPlace;

	while (true)
	{
		std::cout << "\t데이터 = { 0, 5, 6, 12, 28, 32, 45, 64, 81, 94 }" << std::endl << std::endl;
		std::cout << "\t찾고자 하는 데이터를 입력 : ";
		std::cin >> cInput;

		if (cInput[0] == 'q' || cInput[0] == 'Q')
		{
			std::cout << std::endl << "\t프로그램을 종료합니다." << std::endl;
			break;
		}

		iInput = atoi(cInput);
		iPlace = SequentialSearch(iArray, iLength, iInput);

		if (iPlace == -1)
			std::cout << std::endl << "\t입력하신 데이터가 존재하지 않습니다." << std::endl << "다시 입력해 주십시오." << std::endl << std::endl;
		else
			std::cout << std::endl << "\t입력하신 데이터는 " << iPlace << "번에 있습니다." << std::endl << std::endl;

		system("pause");
		system("cls");
	}
}

int SequentialSearch(int* iArray, int iLength, int iInput)
{
	for (int i = 0; i < iLength; ++i)
	{
		if (iArray[i] == iInput)
			return i + 1;
	}

	return -1;
}