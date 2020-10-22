#include <iostream>
#include <vector>

int Prim(std::vector<std::pair<int, int>>& vSelect, std::vector<std::pair<int, int>>* vVertex)
{
    int INF = 1000;
    vSelect.clear();

    std::vector<bool> vAdd(6, false);
    std::vector<int> vWeight(6, INF), vParent(6, -1);

    int iMinimum = 0;
    vWeight[0] = vParent[0] = 0;

    for (int i = 0; i < 6; i++)
    {
        int k = -1;

        for (int j = 0; j < 6; j++)
        {
            if (!vAdd[j] && (k == -1 || vWeight[k] > vWeight[j]))
            {
                k = j;
            }
        }

        if (vParent[k] != k)
        {
            vSelect.push_back(std::make_pair(vParent[k], k));
        }

        iMinimum += vWeight[k];
        vAdd[k] = true;

        for (int i = 0; i < vVertex[k].size(); i++)
        {
            int iVertex = vVertex[k][i].first;
            int iWeight = vVertex[k][i].second;

            if (!vAdd[iVertex] && vWeight[iVertex] > iWeight) {
                vParent[iVertex] = k;
                vWeight[iVertex] = iWeight;
            }
        }
    }

    return iMinimum;
}

void operate()
{
    std::vector<std::pair<int, int> > vVertex[100];

    vVertex[0].push_back(std::make_pair(1, 5));
    vVertex[1].push_back(std::make_pair(0, 5));

    vVertex[1].push_back(std::make_pair(2, 3));
    vVertex[2].push_back(std::make_pair(1, 3));

    vVertex[2].push_back(std::make_pair(3, 4));
    vVertex[3].push_back(std::make_pair(2, 4));

    vVertex[1].push_back(std::make_pair(4, 3));
    vVertex[4].push_back(std::make_pair(1, 3));

    vVertex[0].push_back(std::make_pair(3, 7));
    vVertex[3].push_back(std::make_pair(0, 7));

    vVertex[2].push_back(std::make_pair(4, 2));
    vVertex[4].push_back(std::make_pair(2, 2));

    vVertex[3].push_back(std::make_pair(5, 1));
    vVertex[5].push_back(std::make_pair(3, 1));

    vVertex[4].push_back(std::make_pair(5, 4));
    vVertex[5].push_back(std::make_pair(4, 4));

    std::vector<std::pair<int, int>> selected;
    std::cout << "가중치 최소 합 : " << Prim(selected, vVertex) << std::endl << std::endl;

    for (int i = 0; i < selected.size(); i++)
    {
        std::cout << selected[i].first << "-" << selected[i].second << std::endl;
    }
}