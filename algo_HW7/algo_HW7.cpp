#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <math.h>
using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int wordBreak(string str, vector<string>& set) {
    unordered_set<string> dict;
    for(int i = 0; i < set.size(); i++){
        dict.insert(set[i]);
    }
    
    int max_len = 0;
    for(string s : dict){
        max_len = max(max_len, (int)s.size());
    }
    vector<int> num(str.size() + 1);
    
    for(int i = 0; i < num.size(); i++){
        num[i] = -1;
    }
    num[0] = 0;
    for (int i = 1; i <= str.size(); i++) {
        for (int j = i - 1; j >= max(i - max_len, 0); j--) {
            if(num[j] >= 0){
                string vocab = str.substr(j, i-j);
                if(dict.find(vocab) != dict.end()){
                    num[i] = (num[i] == -1) ? num[j] +1 : min(num[i], num[j] + 1);
                }
            }
            
        }
    }
    return num[str.size()];
}

int main(){
    int cases;
    input >> cases;
    while(cases--){
        int vocabs;
        input >> vocabs;
        vector <string> dict;
        for(int i = 0; i < vocabs; i++){
            string str;
            input >> str;
            dict.push_back(str);
        }
        string target;
        input >> target;
        cout << wordBreak(target, dict) << "\n";
        output << wordBreak(target, dict) << "\n";
    }

    output.close();
    return 0;
}