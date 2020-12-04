#include <iostream>
#include <array>
#include <cstdlib>
#include <climits>
#include <vector>

typedef std::vector<int> Vector1D;
typedef std::vector<Vector1D> Matrix;

void testcase()
{
    int n;
    std::cin >> n;

    Matrix M(n, Vector1D(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> M[i][j];
        }
    }

    Matrix S(n, Vector1D(n, 0));
    S[0][0] = M[0][0];

    for (int i = 1; i < n; i++)
    {
        S[i][0] = M[i][0] + S[i - 1][0];
        S[0][i] = M[0][i] + S[0][i - 1];
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            S[i][j] = M[i][j] + S[i][j - 1] + S[i - 1][j] - S[i - 1][j - 1];
        }
    }
 
    int even_count = 0;

    for (int x_1 = 0; x_1 < n; x_1++)
    {
        for (int x_2 = x_1; x_2 < n; x_2++)
        {
            for (int y_1 = 0; y_1 < n; y_1++)
            {
                for (int y_2 = y_1; y_2 < n; y_2++)
                {
                    int parity = 0;
                    if (x_1 == 0 && y_1 == 0)
                    {
                        parity = S[x_2][y_2];
                    }
                    else if (x_1 == 0)
                    {
                        parity = S[x_2][y_2] - S[x_2][y_1 - 1];
                    }
                    else if (y_1 == 0)
                    {
                        parity = S[x_2][y_2] - S[x_1 - 1][y_2];
                    }
                    else
                    {
                        parity = S[x_2][y_2] +  S[x_1 - 1][y_1 - 1] - S[x_2][y_1 - 1] - S[x_1 - 1][y_2];
                    }
                    if (parity % 2 == 0)
                    {
                        even_count++;
                    }
                }
            }
        }
    }
    std::cout << even_count << std::endl;
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