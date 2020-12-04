#include<iostream>

using namespace std;

int main(){
	int t;
 	cin >> t;
	
	for(int i = 0; i < t ; i++){
		string a, b;
		cin >> a;
		cin >> b;

		cout << a.size() << " " << b.size() << endl;
		cout << a << b << endl;
		
		char c[a.size()];
		a.copy(c, sizeof(c));
		c[a.size()] = '\0'; 

		char d[b.size()];
		b.copy(d, sizeof(d));
		d[b.size()] = '\0';


		for(int i = 0; i < a.size(); i++){
			c[i] = a[a.size()-i-1];
		}
		c[0] = b[b.size()-1];

		for(int i = 0; i < b.size(); i++){
			d[i] = b[b.size()-i-1];
		}
		d[0] = a[a.size()-1];

		cout << c << " " << d << endl;
	}

	return 0;
}
