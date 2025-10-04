#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <fstream>
#include <math.h>
using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int main(){
    int n, length;
    double width;
    while(input >> n >> length >> width){
        map <int, int> list;
        while(n--){
            int p, r;
            input >> p >> r;
            if(2*r > width){
                map <int, int>::iterator target = list.find(p);
                if((target != list.end() && r > target->second) || target == list.end()){
                    list.insert(make_pair(p,r));
                }
            }
        }
        cout << "\n";
        int leftpos = -1;
        for(auto i = list.begin(); i != list.end(); i++){
            int p = i->first;
            int r = i->second;
            if(p - sqrt(r*r - (width/2)*(width/2)) <= 0){
                leftpos = i->first;
            }
        }
        bool coverable = true;
        int result = -1;
        if(leftpos == -1) coverable = false;
        else{
            while(list.begin()->first != leftpos){
                list.erase(list.begin()->first);
            }
            for(auto i = list.begin(); i != list.end(); i++){
                cout << i->first << " " << i->second << "\n";
            }
            cout << "\n";
            map <int,int>::iterator it = list.begin();
            vector <pair <int, int> > circles;
            circles.push_back(*it);
            cout << it->first << " " << it->second << "\n";
            while(it != list.end()){
                pair<int,int> last = circles[circles.size() - 1];
                int p1 = last.first;
                int r1 = last.second;
                if(p1 + sqrt(r1*r1 - (width/2)*(width/2) ) >= length){
                    cout << p1 + sqrt(r1*r1 - (width/2)*(width/2) ) << "\n";
                    cout << "Last circle : " << p1 << " " << r1 << "\n";
                    break;
                }
                double edge = p1 + sqrt(r1*r1 - (width/2)*(width/2) );
                cout << "Edge: " << edge << "\n\n";
                pair <int,int> next = *it;
                bool check = false;
                it++;
                for(auto i = it; i != list.end(); i++){
                    int p2 = i->first;
                    int r2 = i->second;
                    if(edge >= p2 - sqrt(r2*r2 - (width/2)*(width/2))){
                        cout << p2 <<  " " << r2 << "\n";
                        check = true;
                        next = *i;
                    }
                }
                if(!check) {
                    coverable = false;
                    break;
                }
                edge = next.first + sqrt(next.second*next.second - (width/2)*(width/2));
                cout << "New edge: " << edge << "\n\n";
                circles.push_back(next);
                it = list.find(next.first);
            }
            if(coverable){
                result = circles.size();
            }
            for(int i = 0; i < circles.size(); i++){
                cout << circles[i].first << " " << circles[i].second << "\n";
            }
            cout << "\n";
        }
        output << result << "\n";
        cout << result << "\n";
    }
    output.close();
    return 0;
}