#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

typedef struct node
{
	char cVertex;
	char cNext;
	int iEdge;
} Node;

class Graph
{
private:
	Node nNode;
public:
	Graph(char, char, int);
	bool operator <(Graph&);
	char Vertex();
	char Next();
	int Distance();
	void Print();
	~Graph();
};

Graph::Graph(char a, char b, int e)
{
	Graph::nNode.cVertex = a;
	Graph::nNode.cNext = b;
	Graph::nNode.iEdge = e;
}

bool Graph::operator<(Graph& graph)
{
	return Graph::nNode.iEdge < graph.Distance();
}

char Graph::Vertex()
{
	return Graph::nNode.cVertex;
}

char Graph::Next()
{
	return Graph::nNode.cNext;
}

int Graph::Distance()
{
	return Graph::nNode.iEdge;
}

void Graph::Print()
{
	std::cout << Graph::nNode.cVertex << "-" << Graph::nNode.cNext << " 가중치 : " << Graph::nNode.iEdge << std::endl;
}

Graph::~Graph()
{

}

bool DiscriminateVertex(char*, char, char);
char VertexNode(char*, char);
char ConnectVertex(char*, char, char);

void operate()
{
	std::vector<Graph> vGraph;

	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<int> uDis(1, 20);

	vGraph.push_back(Graph('a', 'b', uDis(mGen)));
	vGraph.push_back(Graph('a', 'c', uDis(mGen)));
	vGraph.push_back(Graph('b', 'c', uDis(mGen)));
	vGraph.push_back(Graph('b', 'd', uDis(mGen)));
	vGraph.push_back(Graph('b', 'e', uDis(mGen)));
	vGraph.push_back(Graph('c', 'd', uDis(mGen)));
	vGraph.push_back(Graph('c', 'e', uDis(mGen)));
	vGraph.push_back(Graph('d', 'e', uDis(mGen)));
	vGraph.push_back(Graph('d', 'f', uDis(mGen)));
	vGraph.push_back(Graph('e', 'f', uDis(mGen)));

	for_each(vGraph.begin(), vGraph.end(), [&](Graph& n)
		{
			n.Print();
		});

	std::sort(vGraph.begin(), vGraph.end());

	std::cout << std::endl;

	for_each(vGraph.begin(), vGraph.end(), [&](Graph& n)
		{
			n.Print();
		});

	char cVertex[6];
	char a = 'a';
	for (int i = 0; i < 6; ++i)
	{
		cVertex[i] = a + i;
	}

	int iSum = 0;

	for (int i = 0; i < vGraph.size(); ++i)
	{
		if (DiscriminateVertex(cVertex, vGraph[i].Vertex(), vGraph[i].Next()))
		{
			iSum += vGraph[i].Distance();

			ConnectVertex(cVertex, vGraph[i].Vertex(), vGraph[i].Next());
		}
	}

	std::cout << "\n가중치 최소 합 : " << iSum << std::endl;
}

bool DiscriminateVertex(char* cVertex, char cX, char cY)
{
	cX = VertexNode(cVertex, cX);
	cY = VertexNode(cVertex, cY);

	if (cX == cY)
	{
		return false;
	}
	else
	{
		return true;
	}
}

char VertexNode(char* cVertex, char cNode)
{
	char a = 'a';

	if (cVertex[cNode - a] == cNode)
	{
		return cNode;
	}
	else
	{
		return VertexNode(cVertex, cVertex[cNode - a]);
	}
}

char ConnectVertex(char* cVertex, char cX, char cY)
{
	char a = 'a';

	cX = VertexNode(cVertex, cX);
	cY = VertexNode(cVertex, cY);

	if (cX < cY)
	{
		cVertex[cY - a] = cX;

		return cX;
	}
	else
	{
		cVertex[cX - a] = cY;

		return cY;
	}
}