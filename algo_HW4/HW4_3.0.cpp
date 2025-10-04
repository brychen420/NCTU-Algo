#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int main(){
    int cases;
    input >> cases;
    while(cases--){
        int num;
        input >> num;
        
        vector <long long> v;
        for(int i = 0; i < num; i++){
            long long a;
            input >> a;
            v.push_back(a);
        }
        
        long long count = 0;
        for(int i = 0; i < num-1; i++){
            for(int j = i+1; j < num; j++){
                if(v[j] >= 2*v[i]){
                    count++;
                }
            }
        }
       // cout << count << "\n";
        output << count << "\n";
    }
    output.close();
    return 0;
}
