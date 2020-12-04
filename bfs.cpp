#include <iostream>
#include <array>
#include <iterator>
#include <map>
#include <set>
#include <vector>


//NOT WORKING!!!
using namespace std;

void testcase()
{
	typedef std::vector<bool> VI;
	typedef std::vector<VI> VVI;

	int n, m, v;
	cin >> n >> m >> v;

	std::array<int, 1000> distance;
	std::array<bool, 1000> visited;

	distance.fill(-1);
	visited.fill(false);

	VVI adjM(n, VI(n, false));

	for (int m_i = 0; m_i < m; m_i++)
	{
		int a, b;
		cin >> a >> b;
		adjM[a][b] = true;
	}

	int d = 0;
	std::set<int> set_s;
	set_s.insert(v);
	while (set_s.size() > 0)
	{
		std::set<int> new_s;

		for (int s_i : set_s)
		{
			visited[s_i] = true;
			distance[s_i] = d;
		}

		for (int s_i : set_s)
		{
			v = s_i;
			for (int i = 0; i < n; i++)
			{
				if (visited[i] == false && adjM[v][i] == true)
				{
					new_s.insert(i);
				}
			}
		}
		set_s.clear();
		set_s = new_s;
		d++;
	}
	for (int i = 0; i < n; i++)
	{
		cout << distance[i] << " ";
	}
	cout << endl;
}

int main()
{
	std::ios_base::sync_with_stdio(false); // Always!
	int t;
	std::cin >> t; // Read the number of test cases
	for (int i = 0; i < t; ++i)
	{
		testcase();
	}
}
