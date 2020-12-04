#include <iostream>
#include <array>

void testcase()
{
    int n = 0;
    std::cin >> n;

    std::array<int, 50001> x;
    int even_pairs = 0;

    for (int i = 0; i < n; i++)
    {
        std::cin >> x[i];
    }

    std::array<int, 50001> S;

    int p_sum = 0;
    for (int i = 0; i <= n; i++)
    {
        p_sum += x[i];
        S[i+1] = p_sum;
    }
    S[0] = 0;

    for (int j = n ; j > 0; j--)
    {
        for (int i = 0; i < j; i++)
        {
            if( (S[j]-S[i])%2 == 0){
                even_pairs++;
            }
        }
    }

    std::cout << even_pairs << std::endl;
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