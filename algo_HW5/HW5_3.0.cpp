#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <math.h>
#include <map>
using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int main(){
    int cases;
    input >> cases;
    while(cases--){
        int vertex, target;
        input >> vertex >> target;
        vector <pair<int,int> > v;
        map <int,int> m;
        map <int,int>::iterator it;
        for(int i = 0; i < vertex-1; i++){
            int a, b;
            input >> a >> b;
            v.push_back(make_pair(a,b));
            if(m.find(a) != m.end()) m[a]++;
            else m[a] = 1;
            if(m.find(b) != m.end()) m[b]++;
            else m[b] = 1;
        }
        int head = -20000000;
        for(it = m.begin(); it != m.end(); it++){
            if(it->second == 1)
                head = max(head, it->first);        
        }
        vector<int> list;
        int end = head;
        for(int i = 0; i < v.size(); i++){
            if(v[i].first == head){
                end = v[i].second;
                list.insert(list.begin(), v[i].second);
                list.insert(list.begin(), v[i].first);
                v.erase(v.begin()+i);
                break;
            }
            else if(v[i].second == head){
                end = v[i].first;
                list.insert(list.begin(), v[i].first);
                list.insert(list.begin(), v[i].second);
                v.erase(v.begin()+i);
                break;
            }
        }
        while(!v.empty()){
            for(int i = 0; i < v.size(); i++){
                if(v[i].first == end){
                    end = v[i].second;
                    list.push_back(v[i].second);
                    v.erase(v.begin()+i);
                    break;
                }
                else if(v[i].second == end){
                    end = v[i].first;
                    list.push_back(v[i].first);
                    v.erase(v.begin()+i);
                    break;
                }
            }
        }
        output << list[target] << "\n";
    }
    output.close();
    return 0;
}