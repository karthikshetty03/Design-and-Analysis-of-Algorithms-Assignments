#include <bits/stdc++.h>
using namespace std;

int main() {
	ofstream out;
	out.open("points.txt");
	int n;
	cin >> n;
	int m = 1;
	int k = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 5; j++) {
			float x = k++;
			float y = m*x + 10*i + (rand()%10)*0.02;
			out << x << " " << y << endl;
		}
	}
	
	return 0;
}