#include <iostream>
#include <vector>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void rec(int left_index, int right_index, int player_index, int m, int k, std::vector<int> &sovereigns, VVI &DP)
{
    //If already visited, no need to recompute
    if (DP[left_index][right_index] != -1)
        return;

    if (left_index == right_index)
    {
        if (player_index == k)
        {
            DP[left_index][right_index] = sovereigns[left_index];
        }
        else
        {
            DP[left_index][right_index] = 0;
        }
        return;
    }

    //The next player's index
    int next_player_index = (player_index + 1) % m;

    //Compute the outcoming when taking the left coin
    rec(left_index + 1, right_index, next_player_index, m, k, sovereigns, DP);
   
    //Compute the outcomings when taking the right coin
    rec(left_index, right_index - 1, next_player_index, m, k, sovereigns, DP);

    //Store the results 
    int left_value = DP[left_index + 1][right_index];
    int right_value = DP[left_index][right_index - 1];

    //Play optimally for k
    if (player_index == k)
    {
        //If taking the left coin is better than taking the right
        if (left_value + sovereigns[left_index] > right_value + sovereigns[right_index])
        {
            DP[left_index][right_index] = left_value + sovereigns[left_index];
        }
        else
        {
            DP[left_index][right_index] = right_value + sovereigns[right_index];
        }
    }
    else
    {
        //Play for the worst outcome of player k
        if (left_value > right_value)
        {
            DP[left_index][right_index] = right_value;
        }
        else
        {
            DP[left_index][right_index] = left_value;
        }
    }
}

void testcase()
{
    int n, m, k;

    std::cin >> n;
    std::cin >> m;
    std::cin >> k;

    std::vector<int> sovereigns;

    for (int i = 0; i < n; i++)
    {
        int val;
        std::cin >> val;
        sovereigns.push_back(val);
    }

    //create n x n Matrix initialized with -1
    //Entry DP(i,j) is equal to the earning of player k, assuming k has played optimally for himself and all other player
    //play such that k earns minimal, for the remaining sovereigns between index i and j
    VVI DP(n, VI(n, -1));
    rec(0, n - 1, 0, m, k, sovereigns, DP);

    std::cout << DP[0][n - 1] << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;

    for (int i = 0; i < t; i++)
    {
        testcase();
    }
}