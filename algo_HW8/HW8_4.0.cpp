#include<iostream>
#include<fstream>
#include <utility>
#include<algorithm>
#include<vector>
#include<math.h>
#include <map>
using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int minimizeSegment(map<float, float> A, pair<float, float> X) {
	float MAX = 2147483647;
	A.insert({ MAX, MAX });
	float start = X.first;	
	float end = X.first - 1;	
	int cnt = 0;	
	for (auto i = A.begin(); i != A.end();) {
		if (i->first <= start) {
			end = max(i->second, end);
            i++;
		}
		else {
			start = end;
			++cnt;
			if (i->first > end || end >= X.second) {
				break;
			}
		}
	}
	if (end < X.second) {
		return -1;
	}	
	return cnt;
}

int main() {
	int num;
	int l;
	float w;
	
	while (input >> num >> l >> w) {
		
		w /= 2;
		auto p1 = make_pair(0, l);
		vector<int>distance;
		vector<int>radius;
		map <float,float> line;
		for (int i = 0; i < num; i++) {
			int d = 0, r = 0;
			input >> d >> r;
			if (r > w) {
				distance.push_back(d);
				radius.push_back(r);
			}
		}
		for (int i = 0; i < radius.size(); i++) {
			float sheben = 0;
			sheben = (radius[i] * radius[i]) - (w * w);
			sheben = sqrt(sheben);		
			line.insert(make_pair(distance[i] - sheben , distance[i] + sheben));
		}
		int ans = minimizeSegment(line, p1);
		output << ans << endl;
        cout << ans << "\n";
	}
	output.close();
	return 0;
}