#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

class Graph
{
private:
    int vertices;
    bool colorable;
    vector<vector<int>> list;
    vector<int> color;
    vector<int> same_color;

public:
    Graph(int num)
    {
        this->vertices = num;
        this->colorable = true;
        list.resize(this->vertices);
        color.resize(this->vertices);
        same_color.resize(0);
    }
    void print()
    {
        if (colorable)
        {
            sort(same_color.begin(), same_color.end());
            for (int i = 0; i < same_color.size() - 1; i++)
            {
                output << same_color[i] << ",";
                cout << same_color[i] << ",";
            }
            cout << same_color[same_color.size() - 1];
            output << same_color[same_color.size() - 1];
        }
        else
        {
            cout << -1;
            output << -1;
        }
        cout << "\n";
        output << "\n";
    }
    void addedge(int a, int b)
    {
        list[a].push_back(b);
    }
    void BFS(int start);
};

int main()
{
    int num;
    while (input >> num)
    {
        vector<pair<int, int>> edges;
        int max = 0;
        while (num--)
        {
            int a, b;
            input >> a >> b;
            edges.push_back(make_pair(a, b));
            if (max < a)
                max = a;
            if (max < b)
                max = b;
        }
        Graph g(max + 1);
        for (int i = 0; i < edges.size(); i++)
        {
            g.addedge(edges[i].first, edges[i].second);
            g.addedge(edges[i].second, edges[i].first);
        }
        g.BFS(0);
        g.print();
    }
    output.close();
    return 0;
}

void Graph::BFS(int start)
{
    for (int i = 0; i < vertices; i++)
    {
        color[i] = 0;
    }
    queue<int> q;
    q.push(start);
    color[start] = 1;
    same_color.push_back(start);
    while (!q.empty())
    {
        int u = q.front();
        for (auto it = list[u].begin(); it != list[u].end(); it++)
        {
            if (color[*it] == 0)
            {
                if (color[u] == 1)
                    color[*it] = 2;
                else if (color[u] == 2)
                {
                    color[*it] = 1;
                    same_color.push_back(*it);
                }
                q.push(*it);
            }
            else
            {
                if (color[*it] == color[u])
                {
                    colorable = false;
                    return;
                }
            }
        }
        q.pop();
    }
}