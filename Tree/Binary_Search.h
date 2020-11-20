#include <iostream>
#include <random>

template<typename T>
struct Node
{
	Node* nLeft;
	Node* nRight;
	T tData;
};

template<typename T>
class Tree
{
private:
	Node<T>* nRoot;
public:
	Tree();
	~Tree();
public:
	void PreOrder(Node<T>* nCurrent);
	void InOrder(Node<T>* nCurrent);
	void PostOrder(Node<T>* nCurrent);
	Node<T>* MaxNode(Node<T>* nNode);
	Node<T>* RemoveSequence(Node<T>* nNode, T tData);
public:
	void AddNode(T tValue);
	bool SearchNode(T tValue);
	void RemoveNode(T tValue);

	Node<T>* ReturnRoot() { return nRoot; }
};

template<typename T>
inline Tree<T>::Tree() : nRoot(nullptr)
{
}

template<typename T>
inline void Tree<T>::PreOrder(Node<T>* nCurrent)
{
	if (nCurrent != nullptr)
	{
		std::cout << " " << nCurrent->tData;
		PreOrder(nCurrent->nLeft);
		PreOrder(nCurrent->nRight);
	}
}

template<typename T>
inline void Tree<T>::InOrder(Node<T>* nCurrent)
{
	if (nCurrent != nullptr)
	{
		InOrder(nCurrent->nLeft);
		std::cout << " " << nCurrent->tData;
		InOrder(nCurrent->nRight);
	}
}

template<typename T>
inline void Tree<T>::PostOrder(Node<T>* nCurrent)
{
	if (nCurrent != nullptr)
	{
		PostOrder(nCurrent->nLeft);
		PostOrder(nCurrent->nRight);
		std::cout << " " << nCurrent->tData;
	}
}

template<typename T>
inline Node<T>* Tree<T>::MaxNode(Node<T>* nNode)
{
	if (nNode == nullptr)
		return nNode;
	
	while (nNode->nRight != nullptr)
		nNode = nNode->nRight;

	return nNode;
}

template<typename T>
inline Node<T>* Tree<T>::RemoveSequence(Node<T>* nNode, T tData)
{
	if (nNode == nullptr)
		return nNode;
	else if (nNode->tData > tData)
		nNode->nLeft = RemoveSequence(nNode->nLeft, tData);
	else if (nNode->tData < tData)
		nNode->nRight = RemoveSequence(nNode->nRight, tData);
	else
	{
		Node<T>* tempNode = nNode;

		if (nNode->nLeft == nullptr && nNode->nRight == nullptr)
		{
			delete nNode;
			nNode = nullptr;
		}
		else if (nNode->nLeft == nullptr)
		{
			nNode = nNode->nRight;
			delete tempNode;
		}
		else if (nNode->nRight == nullptr)
		{
			nNode = nNode->nLeft;
			delete tempNode;
		}
		else
		{
			tempNode = MaxNode(nNode->nLeft);
			nNode->tData = tempNode->tData;
			nNode->nLeft = RemoveSequence(nNode->nLeft, tempNode->tData);
		}
	}

	return nNode;

}

template<typename T>
inline void Tree<T>::AddNode(T tData)
{
	Node<T>* nNode = new Node<T>();
	Node<T>* tempRoot = nullptr;

	nNode->tData = tData;

	if (nRoot == nullptr)
		nRoot = nNode;
	else
	{
		Node<T>* tempNode = nRoot;

		while (tempNode != nullptr)
		{
			tempRoot = tempNode;

			if (nNode->tData < tempNode->tData)
				tempNode = tempNode->nLeft;
			else
				tempNode = tempNode->nRight;
		}

		if (nNode->tData < tempRoot->tData)
			tempRoot->nLeft = nNode;
		else
			tempRoot->nRight = nNode;
	}
}

template<typename T>
inline bool Tree<T>::SearchNode(T tData)
{
	Node<T>* nNode = nRoot;
	Node<T>* tempRoot = nullptr;

	while (nNode != nullptr)
	{
		if (nNode->tData == tData)
		{
			std::cout << tData << " 발견" << std::endl;

			return true;
		}
		else if (nNode->tData > tData)
			nNode = nNode->nLeft;
		else
			nNode = nNode->nRight;
	}

	std::cout << tData << " 미발견" << std::endl;

	return false;
}

template<typename T>
inline void Tree<T>::RemoveNode(T tData)
{
	Node <T>* nNode = nRoot;
	RemoveSequence(nNode, tData);
}

template<typename T>
inline Tree<T>::~Tree()
{
}

void operate()
{
	Tree<int>* tBinaryTree = new Tree<int>;

	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<int> uDis(0, 100);

	for (int i = 0; i < 10; ++i)
		tBinaryTree->AddNode(uDis(mGen));

	std::cout << "전위 순회 :";
	tBinaryTree->PreOrder(tBinaryTree->ReturnRoot());

	std::cout << "\n중위 순회 :";
	tBinaryTree->InOrder(tBinaryTree->ReturnRoot());

	std::cout << "\n후위 순회 :";
	tBinaryTree->PostOrder(tBinaryTree->ReturnRoot());
	std::cout << std::endl;
	std::cout << "\n메뉴 :\n" << "1. 노드 추가\n" << "2. 노드 탐색\n" << "3. 노드 삭제\n"
		<< "4. 전위 순회 출력\n" << "5. 전위 순회 출력\n" << "6. 전위 순회 출력\n" << "0. 종료" << std::endl;

	bool bBreak = false;
	while (!bBreak)
	{
		int iMenu, iData;
		std::cout << "\n메뉴 선택 : ";
		std::cin >> iMenu;

		switch (iMenu)
		{
		case 1:
		{
			std::cout << "추가할 값 입력 : ";
			std::cin >> iData;

			tBinaryTree->AddNode(iData);

			break;
		}
		case 2:
		{
			std::cout << "탐색할 값 입력 : ";
			std::cin >> iData;

			tBinaryTree->SearchNode(iData);

			break;
		}
		case 3:
		{
			std::cout << "삭제할 값 입력 : ";
			std::cin >> iData;

			tBinaryTree->RemoveNode(iData);

			break;
		}
		case 4:
		{
			std::cout << "전위 순회 :";
			tBinaryTree->PreOrder(tBinaryTree->ReturnRoot());
			std::cout << std::endl;

			break;
		}
		case 5:
		{
			std::cout << "\n중위 순회 :";
			tBinaryTree->InOrder(tBinaryTree->ReturnRoot());
			std::cout << std::endl;

			break;
		}
		case 6:
		{
			std::cout << "\n후위 순회 :";
			tBinaryTree->PostOrder(tBinaryTree->ReturnRoot());
			std::cout << std::endl;

			break;
		}
		case 0:
		{
			bBreak = true;
			break;
		}
		default:
			std::cout << "잘못된 메뉴를 입력하였으므로 다시 입력 요망" << std::endl;
			break;
		}
	}
}