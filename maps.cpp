#include <iostream>
#include <map>
#include <string>
#include <list>

using namespace std;

int main()
{
	int t;
	cin >> t;

	for (int i = 0; i < t; i++)
	{
		multimap<string, int> mm;
		int q;
		cin >> q;
		for (int j = 0; j < q; j++)
		{
			int a;
			string b;

			cin >> a;
			cin >> b;
			if (a > 0)
				mm.emplace(b, a);
			else
			{
				for (auto it = mm.begin(); it != mm.end();)
					if (!it->first.compare(b))
						it = mm.erase(it);
					else
						++it;
			}
		}
		string s;
		cin >> s;

		list<int> res;
		for (auto it = mm.begin(); it != mm.end();)
		{
			if (!it->first.compare(s))
			{
				res.push_front(it->second);
			}
			++it;
		}

		res.sort();
		for (int r : res)
		{
			cout << r << " ";
		}
		if (res.size() == 0)
			cout << "Empty";
		cout << endl;
	}
	return 0;
}
