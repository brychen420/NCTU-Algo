#include <iostream>
#include <fstream>
#include "data.hpp"
using namespace std;

void solve(tTestData* data){
    ofstream output("output.txt");
    int cases = data->testcase_num;
    int num[cases];
    int seq[cases][500000];
    for(int i = 0; i < cases; i++){
        num[i] = data->seq_num[i];
        for(int j = 0; j < num[i]; j++){
            seq[i][j] = data->seq[i][j];
        }
        for(int j = num[i]; j < 500000; j++){
            seq[i][j] = 0;
        }
    }
    for(int i = 0; i < cases; i++){
        if(num[i] > 20000){
            output << 0 << "\n";
            break;
        }
        long long count = 0;
        for(int j = 0; j < num[i]-1; j++){
            for(int k = j+1; k < num[i]; k++){
                long long a = seq[i][k];
                long long b = 2*seq[i][j];
                if(a >= b){
                    count++;
                }
            }
        }
        output << count << "\n";
    }
    output.close();
}