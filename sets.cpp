#include<iostream>
#include<set>

using namespace std;


int main(){
	int t;
	cin >> t;
	for (int i = 0; i < t; i++){
		int q;
		cin >> q;
		set<int> s;

		for(int j = 0; j < q; j++){
			int a, b;
			cin >> a;
			cin >> b;
			
			if(a == 0){
				s.insert(b);	
			}else{
				for(auto it = s.begin(); it != s.end();){
					if(*it == b)
						it = s.erase(it); 						else
						++it;
					}
			}					
		}
		
		for(int s_i : s){
			cout << s_i << " ";		
		}
		if (s.size() == 0){
			cout << "Empty";	
		}
		cout << endl;
	}

	return 0;
}
