#include <iostream>
#include <fstream>
using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int main(){
    int cases;
    input >> cases;
    while(cases--){
        int num;
        input >> num;
        /*
        if(num > 200000){
            output << 0;
            break;
        }
        */
        long long seq[num];
        for(int i = 0; i < num; i++){
            input >> seq[i];
        }
        
        long long count = 0;
        for(int i = 0; i < num-1; i++){
            for(int j = i+1; j < num; j++){
                if(seq[j] >= 2*seq[i]){
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
