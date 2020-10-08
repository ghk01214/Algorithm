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
		std::cout << "\t������ = { 0, 5, 6, 12, 28, 32, 45, 64, 81, 94 }" << std::endl << std::endl;
		std::cout << "\tã���� �ϴ� �����͸� �Է� : ";
		std::cin >> cInput;

		if (cInput[0] == 'q' || cInput[0] == 'Q')
		{
			std::cout << std::endl << "\t���α׷��� �����մϴ�." << std::endl;
			break;
		}

		iInput = atoi(cInput);
		iPlace = SequentialSearch(iArray, iLength, iInput);

		if (iPlace == -1)
			std::cout << std::endl << "\t�Է��Ͻ� �����Ͱ� �������� �ʽ��ϴ�." << std::endl << "�ٽ� �Է��� �ֽʽÿ�." << std::endl << std::endl;
		else
			std::cout << std::endl << "\t�Է��Ͻ� �����ʹ� " << iPlace << "���� �ֽ��ϴ�." << std::endl << std::endl;

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