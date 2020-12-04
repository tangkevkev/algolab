#include<iostream>

using namespace std;

int main(){
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		int n;
		cin >> n;
		long long sum = 0;		
		for(int j = 0; j < n; j++){
			long long read;
			cin >> read;
			sum = sum + read;
		}	
		cout << sum << endl;
	}
	return 0;
}
