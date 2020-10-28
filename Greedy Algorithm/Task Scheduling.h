#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#define TASK 8

struct Time
{
	int iStart, iEnd;
};

bool compare(std::pair<int, Time>, std::pair<int, Time>);

class Machine
{
private:
	std::vector<std::pair<int, Time>> vTask;									//�۾� ���
	std::vector<std::vector<int>> vMachine;			//�۾��� �Ҵ�� ����
	int iNum;
public:
	Machine();
	void Sort();
	void PrintTaskList();
	void Scheduling();
	int AllocateTask(int);
	void PrintMachineList();
	~Machine();
};

Machine::Machine()
{
	//�۾� �ð� ���� ����
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<int> uDis(0, TASK);

	int iStart;
	int iEnd;

	for (int i = 0; i < TASK; ++i)
	{
		//�۾� ���� �ð��� ��ü �۾� ���� �ð����� �۵��� ����
		do
		{
			iStart = uDis(mGen);
		} while (iStart == TASK);

		//�۾� ���� �ð��� ���� �ð����� ũ���� ����
		do
		{
			iEnd = uDis(mGen);
		} while (iStart >= iEnd);

		Time iTime = { iStart, iEnd };

		this->vTask.push_back(std::make_pair(i + 1, iTime));

		std::vector<int> vTemp(0);
		this->vMachine.push_back(vTemp);
	}

	this->iNum = 0;
}

void Machine::Sort()
{
	std::sort(vTask.begin(), vTask.end(), compare);
}

void Machine::PrintTaskList()
{
	for (int i = 0; i < TASK; ++i)
	{
		std::cout << "t" << this->vTask[i].first << " = (" << this->vTask[i].second.iStart << ", " << this->vTask[i].second.iEnd << ")" << std::endl;
	}
}

void Machine::Scheduling()
{
	for (int i = 0; i < TASK; ++i)
	{
		this->vMachine[this->AllocateTask(this->vTask[i].second.iStart)].push_back(i);
	}
}

int Machine::AllocateTask(int Start)
{
	if (this->iNum > 0)
	{
		int i;

		for (i = 0; i < this->iNum; ++i)
		{
			if (this->vMachine[i].size() > 0 && this->vTask[this->vMachine[i].back()].second.iEnd <= Start)
			{
				return i;
			}
		}

		++this->iNum;
		return i;
	}
	else
	{
		++this->iNum;
		return 0;
	}
}

void Machine::PrintMachineList()
{
	for (int i = 0; i < TASK; ++i)
	{
		if (this->vMachine[i].size() != 0)
		{
			std::cout << "\n��� ��ȣ : " << i + 1 << std::endl;

			for (int j = 0; j < this->vMachine[i].size(); ++j)
			{
				std::cout << "�۾� ��ȣ : t" << this->vTask[this->vMachine[i][j]].first << ", ( " << this->vTask[this->vMachine[i][j]].second.iStart << ", " << this->vTask[this->vMachine[i][j]].second.iEnd << " )" << std::endl;
			}
		}
	}
}

Machine::~Machine()
{

}

void operate()
{
	Machine mMachine;

	std::cout << "�۾� ���" << std::endl;
	mMachine.PrintTaskList();
	mMachine.Sort();

	mMachine.Scheduling();
	mMachine.PrintMachineList();
}

bool compare(std::pair<int, Time> a, std::pair<int, Time> b)
{
	if (a.second.iEnd == b.second.iEnd)
	{
		return a.second.iStart < b.second.iStart;
	}
	else
	{
		return a.second.iEnd < b.second.iEnd;
	}
}