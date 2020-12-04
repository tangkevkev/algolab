#include <iostream>
#include <array>
#include <iterator>
#include <map>
#include <stack>

using namespace std;

//NOT WORKING!!!

void testcase()
{

	int n, m, v;
	cin >> n >> m >> v;

	std::array<bool, 1000> visited;
	visited.fill(false);
	std::array<int, 1000> discovery;
	discovery.fill(-1);
	std::array<int, 1000> finish;
	finish.fill(-1);

	bool adjM[n][n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			adjM[i][j] = false;
		}
	}

	for (int m_i = 0; m_i < m; m_i++)
	{
		int a, b;
		cin >> a >> b;
		adjM[a][b] = true;
	}

	int timestamp = 0;
	stack<int> st;

	while (true)
	{
		visited[v] = true;

		if (discovery[v] == -1)
		{
			discovery[v] = timestamp;
		}

		finish[v] = timestamp + 1;

		bool hasNeighbor = false;

		for (int i = 0; i < n; i++)
		{
			if (adjM[v][i] && !visited[i])
			{
				st.push(v);
				v = i;
				hasNeighbor = true;
				break;
			}
		}

		if (!hasNeighbor)
		{
			if (st.size() == 0)
			{
				break;
			}
			else
			{
				v = st.top();
				st.pop();
			}
		}
		timestamp++;
	}
	for (int i = 0; i < n; i++)
	{
		cout << discovery[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << finish[i] << " ";
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
