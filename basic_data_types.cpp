#include<iostream>
#include<stdlib.h>
#include<math.h>
#include <iomanip>

using namespace std;


int main(){
	int t;
	cin >> t;

	for(int i = 0; i < t; i++){
		int v_int;
		long long v_long;
		string v_string;
		double v_double;

		cin >> v_int;
		cin >> v_long;
		cin >> v_string;
		cin >> v_double;
		
		cout << setprecision(2);
		cout << v_int << " " << v_long << " " << v_string << " " << fixed << (v_double) << endl;
		
	}

	return 0;
}
