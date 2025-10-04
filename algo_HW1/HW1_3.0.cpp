#include <iostream>
#include <fstream>
#include "data.hpp" 
using namespace std;

void solve(tTestData* test_data){
    ofstream output("output.txt");
    int num = test_data->cnt;
    int size[num];
    int data[num][20000];
    for(int i = 0; i < num; i++){
        size[i] = test_data->seq_size[i];
        for(int j = 0; j < 20000; j++){
            data[i][j] = test_data->data[i][j];
        }
    }
    int sorting[num][20001];
    for(int i = 0; i < num; i++){
        for(int j = 0; j < 20001; j++){
            sorting[i][j] = 0;
        }
        for(int j = 0; j < size[i]; j++){
            int tmp = data[i][j];
            sorting[i][tmp]++;
        }
        for(int j = 1; j <= 20000; j++){
            while(sorting[i][j] > 0){
                output << j << " ";
                sorting[i][j]--;
            }
        }
        output << "\n";
    }
    output.close();
}