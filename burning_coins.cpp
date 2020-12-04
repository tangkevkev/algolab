#include <iostream>
#include <vector>
#include <array>

typedef std::vector<std::array<int, 2>> VI;
typedef std::vector<VI> Matrix;

std::array<int, 2> rec(std::vector<int> &V, Matrix &DP, int left, int right, bool myTurn)
{
    std::array<int, 2> result;
    if (left == right)
    {
        int value = V[left];
        result = {(myTurn) ? value : 0, (myTurn) ? 0 : value};
    }
    else
    {
        if (DP[left][right][0] != -1 && DP[left][right][1] != -1)
        {
            auto elem_dp = DP[left][right];
       //     std::cout << "DP: left, right: " << left << " " << right << ". Result: " << elem_dp[0] << " " << elem_dp[1] << std::endl;

            return DP[left][right];
        }
        else
        {
            bool nextTurn = !myTurn;
            auto leftResult = rec(V, DP, left + 1, right, nextTurn);
            auto rightResult = rec(V, DP, left, right - 1, nextTurn);

            if (myTurn) //Player turn
            {
                auto leftValue = leftResult[0];
                auto rightValue = rightResult[0];

                if (leftValue + V[left] > rightValue + V[right])
                {
                    result = {leftValue + V[left], leftResult[1]};
                }
                else
                {
                    result = {rightValue + V[right], rightResult[1]};
                }
            }
            else //Adversary turn
            {
                auto leftValue = leftResult[1];
                auto rightValue = rightResult[1];

                if (leftValue + V[left] > rightValue + V[right])
                {
                    result = {leftResult[0], leftValue+V[left]};
                }
                else
                {
                    result = {rightResult[0], rightValue + V[right]};
                }
            }
        }
    }
  //  std::cout << "My turn : " << myTurn << std::endl;
  //  std::cout << "left, right: " << left << " " << right << ". Result: " << result[0] << " " << result[1] << std::endl;
    DP[left][right] = result;
    return result;
}

void testcase()
{

    int n;
    std::cin >> n;

    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }

    if (n == 1)
    {
        std::cout << v[0] << std::endl;
        return;
    }

    if (n == 2)
    {
        int max = std::max(v[0], v[1]);
        std::cout << max << std::endl;
        return;
    }

    Matrix DP(n, VI(n, {-1, -1}));
    auto result = rec(v, DP, 0, n - 1, true);

    std::cout << DP[0][n - 1][0] << std::endl;
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