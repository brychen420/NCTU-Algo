#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <fstream>
#include <math.h>
using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int main()
{
    int n, length;
    double width;
    while (input >> n >> length >> width)
    {
        map<int, int> list;
        while (n--)
        {
            int p, r;
            input >> p >> r;
            if (2 * r > width)
            {
                auto target = list.find(p);
                if ((target != list.end() && r > target->second) || target == list.end())
                {
                    list.insert(make_pair(p, r));
                }
            } 
        }

        bool coverable = true;
        if (list.size() == 0) coverable = false;
        vector<pair<int, int>> circles;
        double edge = 0;
        for (auto it = list.begin(); it != list.end(); it++)
        {
            pair<int, int> next = *it;
            bool check = false;
            for (auto i = it; i != list.end(); i++)
            {
                int p2 = i->first;
                int r2 = i->second;
                if (edge >= p2 - sqrt(r2 * r2 - (width / 2) * (width / 2)))
                {
                    check = true;
                    next = *i;
                }
            }
            if (!check)
            {
                coverable = false;
                break;
            }
            circles.push_back(next);
            int p1 = next.first;
            int r1 = next.second;
            cout << p1 << " " << r1 << "\n";
            edge = p1 + sqrt(r1 * r1 - (width / 2) * (width / 2));
            if (edge >= length)
            {
                cout << "Last edge : " << edge << "\n";
                cout << "Last circle : " << p1 << " " << r1 << "\n";
                break;
            }
            cout << "New edge: " << edge << "\n";

            it = list.find(next.first);
        }

        int result = -1;
        if (coverable)
        {
            result = circles.size();
        }
        for (int i = 0; i < circles.size(); i++)
        {
            cout << circles[i].first << " " << circles[i].second << "\n";
        }

        output << result << "\n";
        cout << "result : " << result << "\n\n";
    }
    output.close();
    return 0;
}