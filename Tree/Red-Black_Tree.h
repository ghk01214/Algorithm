#include <iostream>
#include <string>

struct Node
{
	Node* nLeft;
	Node* nRight;
	Node* nParent;
	int iData;
	std::string sColor;
};

class Tree
{
private:
	Node* nRoot;
public:
	Tree();
	~Tree();
public:
	Node* Grandparent(Node* nCurrent);
	Node* Uncle(Node* nCurrent);
	Node* Sibling(Node* nCurrent);
public:
	void AddNode(int iData);
	void AddCase1(Node* nCurrent);
	void AddCase2(Node* nCurrent);
	void AddCase3(Node* nCurrent);
	void AddCase4(Node* nCurrent);
	void AddCase5(Node* nCurrent);

	void RotateLeft(Node* nCurrent);
	void RotateRight(Node* nCurrent);
public:
	bool IsLeaf(Node* nCurrent);
	void ReplaceNode(Node* nCurrent, Node* nChild);

	void DeleteNode(Node* nCurrent);
	void DeleteCase1(Node* nCurrent);
	void DeleteCase2(Node* nCurrent);
	void DeleteCase3(Node* nCurrent);
	void DeleteCase4(Node* nCurrent);
	void DeleteCase5(Node* nCurrent);
	void DeleteCase6(Node* nCurrent);

	void RemoveNode(int iData);
	Node* RemoveSequence(Node* nNode, int iData);
public:
	bool SearchNode(int iData);

	Node* ReturnRoot() { return nRoot; }
public:
	void PreOrder(Node* nCurrent);
	void InOrder(Node* nCurrent);
	void PostOrder(Node* nCurrent);
	Node* MaxNode(Node* nNode);
};

inline Tree::Tree() : nRoot(nullptr)
{

}

Node* Tree::Grandparent(Node* nCurrent)
{
	if ((nCurrent != nullptr) && (nCurrent->nParent != nullptr))
		return nCurrent->nParent->nParent;
	else
		return nullptr;
}
Node* Tree::Uncle(Node* nCurrent)
{
	struct Node* g = Grandparent(nCurrent);

	if (g == nullptr)
		return nullptr;

	if (nCurrent->nParent == g->nLeft)
		return g->nRight;
	else
		return g->nLeft;
}
Node* Tree::Sibling(Node* nCurrent)
{
	if (nCurrent == nCurrent->nParent->nLeft)
		return nCurrent->nParent->nRight;
	else
		return nCurrent->nParent->nLeft;
}

inline void Tree::AddNode(int iData)
{
	Node* nNode = new Node();
	Node* tempRoot = nullptr;

	nNode->iData = iData;
	nNode->sColor = "black";

	if (nRoot == nullptr)
		nRoot = nNode;
	else
	{
		Node* tempNode = nRoot;

		while (tempNode != nullptr)
		{
			tempRoot = tempNode;

			if (nNode->iData < tempNode->iData)
				tempNode = tempNode->nLeft;
			else
				tempNode = tempNode->nRight;
		}

		if (nNode->iData < tempRoot->iData)
		{
			tempRoot->nLeft = nNode;
			tempRoot->nLeft->nParent = tempRoot;
			tempRoot->nLeft->sColor = "red";
		}
		else
		{
			tempRoot->nRight = nNode;
			tempRoot->nRight->nParent = tempRoot;
			tempRoot->nRight->sColor = "red";
		}

		AddCase1(nNode);
	}
}
inline void Tree::AddCase1(Node* nCurrent)
{
	if (nCurrent->nParent == nullptr)
		nCurrent->sColor = "black";
	else
		AddCase2(nCurrent);
}
inline void Tree::AddCase2(Node* nCurrent)
{
	if (nCurrent->nParent->sColor == "red")
		AddCase3(nCurrent);
}
inline void Tree::AddCase3(Node* nCurrent)
{
	Node* nUncle = Uncle(nCurrent), * nGrandparent;

	if ((nUncle != nullptr) && (nUncle->sColor == "red"))
	{
		nCurrent->nParent->sColor = "black";
		nUncle->sColor = "black";
		nGrandparent = Grandparent(nCurrent);
		nGrandparent->sColor = "red";
		AddCase1(nGrandparent);
	}
	else
		AddCase4(nCurrent);
}
inline void Tree::AddCase4(Node* nCurrent)
{
	Node* nGrandparent = Grandparent(nCurrent);

	if ((nCurrent == nCurrent->nParent->nRight) && (nCurrent->nParent == nGrandparent->nLeft))
	{
		RotateLeft(nCurrent->nParent);
		nCurrent = nCurrent->nLeft;
	}
	else if ((nCurrent == nCurrent->nParent->nLeft) && (nCurrent->nParent == nGrandparent->nRight))
	{
		RotateRight(nCurrent->nParent);
		nCurrent = nCurrent->nRight;
	}

	AddCase5(nCurrent);
}
inline void Tree::AddCase5(Node* nCurrent)
{
	Node* nGrandparent = Grandparent(nCurrent);

	nCurrent->nParent->sColor = "black";
	nGrandparent->sColor = "red";

	if (nCurrent == nCurrent->nParent->nLeft)
		RotateRight(nGrandparent);
	else
		RotateLeft(nGrandparent);
}

inline void Tree::RotateLeft(Node* nCurrent)
{
	Node* nChild = nCurrent->nRight;
	Node* nParent = nCurrent->nParent;

	if (nChild->nLeft != nullptr)
		nChild->nLeft->nParent = nCurrent;

	nCurrent->nRight = nChild->nLeft;
	nCurrent->nParent = nChild;
	nChild->nLeft = nCurrent;
	nChild->nParent = nParent;

	if (nParent != nullptr)
	{
		if (nParent->nLeft == nCurrent)
			nParent->nLeft = nChild;
		else
			nParent->nRight = nChild;
	}
	else
		nRoot = nChild;
}
inline void Tree::RotateRight(Node* nCurrent)
{
	Node* nChild = nCurrent->nLeft;
	Node* nParent = nCurrent->nParent;

	if (nChild->nRight != nullptr)
		nChild->nRight->nParent = nCurrent;

	nCurrent->nLeft = nChild->nRight;
	nCurrent->nParent = nChild;
	nChild->nRight = nCurrent;
	nChild->nParent = nParent;

	if (nParent != nullptr)
	{
		if (nParent->nRight == nCurrent)
			nParent->nRight = nChild;
		else
			nParent->nLeft = nChild;
	}
	else
		nRoot = nChild;
}

inline bool Tree::IsLeaf(Node* nCurrent)
{
	if (nCurrent->nLeft == nullptr && nCurrent->nRight == nullptr)
		return true;
	else
		return false;
}
inline void Tree::ReplaceNode(Node* nCurrent, Node* nChild)
{
	nChild->nParent = nCurrent->nParent;

	if (nCurrent->nParent->nLeft == nCurrent)
		nCurrent->nParent->nLeft = nChild;
	else if (nCurrent->nParent->nRight == nCurrent)
		nCurrent->nParent->nRight = nChild;
}

inline void Tree::DeleteNode(Node* nCurrent)
{
	Node* nChild;

	if (IsLeaf(nCurrent->nRight))
		nChild = nCurrent->nLeft;
	else
		nChild = nCurrent->nRight;

	ReplaceNode(nCurrent, nChild);

	if (nCurrent->sColor == "black")
	{
		if (nChild->sColor == "red")
			nChild->sColor = "black";
		else
			DeleteCase1(nChild);
	}
}
inline void Tree::DeleteCase1(Node* nCurrent)
{
	if (nCurrent->nParent != nullptr)
		DeleteCase2(nCurrent);
}
inline void Tree::DeleteCase2(Node* nCurrent)
{
	Node* nSibling = Sibling(nCurrent);

	if (nSibling->sColor == "red")
	{
		nCurrent->nParent->sColor = "red";
		nSibling->sColor = "black";

		if (nCurrent == nCurrent->nParent->nLeft)
			RotateLeft(nCurrent->nParent);
		else
			RotateRight(nCurrent->nParent);
	}

	DeleteCase3(nCurrent);
}
inline void Tree::DeleteCase3(Node* nCurrent)
{
	Node* nSibling = Sibling(nCurrent);

	if ((nCurrent->nParent->sColor == "black") && (nSibling->sColor == "black") && (nSibling->nLeft->sColor == "black") && (nSibling->nRight->sColor == "black"))
	{
		nSibling->sColor = "red";
		DeleteCase1(nCurrent->nParent);
	}
	else
		DeleteCase4(nCurrent);
}
inline void Tree::DeleteCase4(Node* nCurrent)
{
	Node* nSibling = Sibling(nCurrent);

	if ((nCurrent->nParent->sColor == "red") && (nSibling->sColor == "black") && (nSibling->nLeft->sColor == "black") && (nSibling->nRight->sColor == "black"))
	{
		nSibling->sColor = "red";
		nCurrent->nParent->sColor = "black";
	}
	else
		DeleteCase5(nCurrent);
}
inline void Tree::DeleteCase5(Node* nCurrent)
{
	Node* nSibling = Sibling(nCurrent);

	if (nSibling->sColor == "black")
	{
		if ((nCurrent == nCurrent->nParent->nLeft) && (nSibling->nLeft->sColor == "red") && (nSibling->nRight->sColor == "black"))
		{
			nSibling->sColor = "red";
			nSibling->nLeft->sColor = "black";
			RotateRight(nSibling);
		}
		else if ((nCurrent == nCurrent->nParent->nRight) && (nSibling->nLeft->sColor == "black") && (nSibling->nRight->sColor == "red"))
		{
			nSibling->sColor = "red";
			nCurrent->nRight->sColor = "black";
			RotateLeft(nSibling);
		}
	}

	DeleteCase6(nCurrent);
}
inline void Tree::DeleteCase6(Node* nCurrent)
{
	Node* nSibling = Sibling(nCurrent);

	nSibling->sColor = nCurrent->nParent->sColor;
	nCurrent->nParent->sColor = "black";

	if (nCurrent == nCurrent->nParent->nLeft)
	{
		nSibling->nRight->sColor = "black";
		RotateLeft(nCurrent->nParent);
	}
	else
	{
		nSibling->nLeft->sColor = "black";
		RotateRight(nCurrent->nParent);
	}
}

inline void Tree::RemoveNode(int iData)
{
	Node * nNode = nRoot;
	RemoveSequence(nNode, iData);
}
inline Node* Tree::RemoveSequence(Node* nNode, int iData)
{
	if (nNode == nullptr)
		return nNode;
	else if (nNode->iData > iData)
		nNode->nLeft = RemoveSequence(nNode->nLeft, iData);
	else if (nNode->iData < iData)
		nNode->nRight = RemoveSequence(nNode->nRight, iData);
	else
	{
		Node* tempNode = nNode;

		DeleteNode(nNode);

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
			nNode->iData = tempNode->iData;
			nNode->nLeft = RemoveSequence(nNode->nLeft, tempNode->iData);
		}
	}

	return nNode;
}

inline bool Tree::SearchNode(int iData)
{
	Node* nNode = nRoot;
	Node* tempRoot = nullptr;

	while (nNode != nullptr)
	{
		if (nNode->iData == iData)
		{
			std::cout << iData << " 발견" << std::endl;

			return true;
		}
		else if (nNode->iData > iData)
			nNode = nNode->nLeft;
		else
			nNode = nNode->nRight;
	}

	std::cout << iData << " 미발견" << std::endl;

	return false;
}

inline void Tree::PreOrder(Node* nCurrent)
{
	if (nCurrent != nullptr)
	{
		std::cout << " " << nCurrent->iData;
		PreOrder(nCurrent->nLeft);
		PreOrder(nCurrent->nRight);
	}
}
inline void Tree::InOrder(Node* nCurrent)
{
	if (nCurrent != nullptr)
	{
		InOrder(nCurrent->nLeft);
		std::cout << " " << nCurrent->iData << "(" << nCurrent->sColor << ")";
		InOrder(nCurrent->nRight);
	}
}
inline void Tree::PostOrder(Node* nCurrent)
{
	if (nCurrent != nullptr)
	{
		PostOrder(nCurrent->nLeft);
		PostOrder(nCurrent->nRight);
		std::cout << " " << nCurrent->iData;
	}
}
inline Node* Tree::MaxNode(Node* nNode)
{
	if (nNode == nullptr)
		return nNode;

	while (nNode->nRight != nullptr)
		nNode = nNode->nRight;

	return nNode;
}

inline Tree::~Tree()
{
}

void operate()
{
	Tree* tBinaryTree = new Tree;

	int array[10] = { 13, 8, 1, 6, 11, 17, 15, 25, 22, 27 };

	for (int i = 0; i < 10; ++i)
		tBinaryTree->AddNode(array[i]);

	//std::cout << "전위 순회 :";
	//tBinaryTree->PreOrder(tBinaryTree->ReturnRoot());

	std::cout << "\n중위 순회 :";
	tBinaryTree->InOrder(tBinaryTree->ReturnRoot());

	//std::cout << "\n후위 순회 :";
	//tBinaryTree->PostOrder(tBinaryTree->ReturnRoot());
	std::cout << std::endl;
	std::cout << "\n메뉴 :\n" << "1. 노드 추가\n" << "2. 노드 탐색\n" << "3. 노드 삭제\n"
		<< "4. 전위 순회 출력\n" << "5. 중위 순회 출력\n" << "6. 후위 순회 출력\n" << "0. 종료" << std::endl;

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