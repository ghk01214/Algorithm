#include <iostream>
#include <vector>
#include <queue>
#define INF INT_MAX
#define VERTEX_NUM 6
#define A 97

enum Vertex
{
	a, b, c, d, e, f
};

void Dijkstra(std::vector<std::pair<char, int>> *vEdge, int *iDistance, char cVertex)
{
	std::priority_queue<std::pair<char, int>> pHeap;
	pHeap.push(std::make_pair(cVertex, 0));

	while (!pHeap.empty())
	{
		char cCurrentVertex = pHeap.top().first;
		int iCurrentDistance = -pHeap.top().second;
		pHeap.pop();

		if (iDistance[cCurrentVertex - A] < iCurrentDistance)
		{
			continue;
		}

		for (int i = 0; i < vEdge[cCurrentVertex - A].size(); ++i)
		{
			char cNextVertex = vEdge[cCurrentVertex - A][i].first;
			int iNextDistance = iCurrentDistance + vEdge[cCurrentVertex - A][i].second;

			if (iNextDistance < iDistance[cNextVertex - A])
			{
				iDistance[cNextVertex - A] = iNextDistance;
				pHeap.push(std::make_pair(cNextVertex, -iNextDistance));
			}
		}
	}
}

void operate()
{
	std::vector<std::pair<char, int>> vEdge[VERTEX_NUM];
	int iDistance[VERTEX_NUM];

	for (int i = 0; i < VERTEX_NUM; ++i)
	{
		iDistance[i] = INF;
	}

	iDistance[Vertex::a] = 0;

	vEdge[Vertex::a].push_back(std::make_pair('b', 1));
	vEdge[Vertex::a].push_back(std::make_pair('c', 6));

	vEdge[Vertex::b].push_back(std::make_pair('a', 1));
	vEdge[Vertex::b].push_back(std::make_pair('c', 2));
	vEdge[Vertex::b].push_back(std::make_pair('d', 5));
	vEdge[Vertex::b].push_back(std::make_pair('e', 4));

	vEdge[Vertex::c].push_back(std::make_pair('a', 6));
	vEdge[Vertex::c].push_back(std::make_pair('b', 2));
	vEdge[Vertex::c].push_back(std::make_pair('d', 2));
	vEdge[Vertex::c].push_back(std::make_pair('e', 3));

	vEdge[Vertex::d].push_back(std::make_pair('b', 5));
	vEdge[Vertex::d].push_back(std::make_pair('c', 2));
	vEdge[Vertex::d].push_back(std::make_pair('e', 1));
	vEdge[Vertex::d].push_back(std::make_pair('f', 4));

	vEdge[Vertex::e].push_back(std::make_pair('b', 4));
	vEdge[Vertex::e].push_back(std::make_pair('c', 3));
	vEdge[Vertex::e].push_back(std::make_pair('d', 1));
	vEdge[Vertex::e].push_back(std::make_pair('f', 7));

	vEdge[Vertex::f].push_back(std::make_pair('d', 4));
	vEdge[Vertex::f].push_back(std::make_pair('e', 7));

	Dijkstra(vEdge, iDistance, 'a');

	char cStart = 'a';
	std::cout << "정점 a로부터 각 정점까지의 최단거리\n" << std::endl;

	for (int i = 0; i < VERTEX_NUM; ++i)
	{
		std::cout << "a - " << cStart++ << " : " << iDistance[i] << std::endl;
	}
}