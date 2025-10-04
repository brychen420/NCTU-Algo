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
    int n, length, width;
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
        map <int, int>::iterator left = list.end();
        int leftpos = -1;
        for(auto i = list.begin(); i != list.end(); i++){
            int p = i->first;
            int r = i->second;
            if(left == list.end()){
                left = i;
                leftpos = i->first;
            }
            else if(4*r*r >= 4*p*p + width*width && left->second < i->second + i->first - left->first){
                leftpos = i->first;
                left = i;
            }
        }
        if(leftpos >= 0){
            while(list.begin()->first != leftpos){
                list.erase(list.begin()->first);
            }
        }
        map <int, int>::reverse_iterator right = list.rend();
        int rightpos = -1;
        for(auto i = list.rbegin(); i != list.rend(); i++){
            int p = length - i->first;
            int r = i->second;
            if(right == list.rend()){
                right = i;
                rightpos = i->first;
            }
            else if(4*r*r >= 4*p*p + width*width && right->second < i->second + right->first - i->first){
                rightpos = i->first;
                right = i;
            }
        }
        if(rightpos >= 0){
            while(list.rbegin()->first != rightpos){
                list.erase(list.rbegin()->first);
            }
        }
        if(leftpos == -1 || rightpos == -1) list.clear();
        
        for(auto i = list.begin(); i != list.end(); i++){
            cout << i->first << " " << i->second << "\n";
        }
        cout << "\n";
        
        int count = 0;
        map <int, int>::reverse_iterator last = list.rend();
        if(list.size() > 0) count++;
        for(auto i = list.begin(); i != list.end();){
            bool found = false;
            for(auto j = list.rbegin(); j->first != i->first; j++){
                int d = j->first - i->first;
                int r1 = i->second;
                int r2 = j->second;
                int s = r1 + r2 + d;
                if(s*(s-2*r1)*(s-2*r2)*(s-2*d) >= d*d*width*width){
                    i = list.find(j->first);
                    count++;
                    found = true;
                    cout << "found : " << i->first << "\n";
                    last = j;
                    break;
                }
            } 
            if(!found){
                i++;
            }
        }
        
        for(auto i = list.begin(); i != list.end(); i++){
            cout << i->first << " " << i->second << "\n";
        }
        cout << "\n";
        int result = -1;
        if(list.size() == 0) result = -1;
        else if(list.size() == 1){
            int p = list.begin()->first;
            int r = list.begin()->second;
            int M = max(length-p, p);
            if(4*r*r >= 4*M*M + width*width){
                result = 1;
            }
            else result = -1;
        }
        else if(list.size() == 2){
            map <int, int>::iterator a = list.begin();
            map <int, int>::iterator b = a; b++;
            int p1 = a->first;
            int p2 = b->first;
            int d = p2-p1;
            int r1 = a->second;
            int r2 = b->second;
            int s = r1 + r2 + d;
            if(s*(s-r1)*(s-r2)*(s-d) >= d*d*width*width){
                result = 2;
            }
            else result = -1;
        }
        else if(list.size() >= 3){
            if(last == list.rbegin()) result = count;
            else result = -1;
        }
        
        output << result << "\n";
        cout << result << "\n";
    }
    output.close();
    return 0;
}