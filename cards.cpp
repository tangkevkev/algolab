#include <iostream>
#include <array>
#include <cstdlib>
#include <climits>

void testcase()
{
    long n = 0;
    long k = 0;
    std::cin >> n;
    std::cin >> k;

    std::array<long, 100000> cards;
    for (int i = 0; i < n; i++)
    {
        std::cin >> cards[i];
    }

    long min_dist = LONG_MAX;
    long sum = cards[0];
    int l = 0;
    int r = 0;

    int l_opt = 0;
    int r_opt = 0;

    while (true)
    {
        if (k - sum == 0)
        {
            l_opt = l;
            r_opt = r;
            break;
        }

        long new_dist = std::abs(k - sum);
        //  std::cout << "sum : " << sum << std::endl;

        if (min_dist > new_dist)
        {
            min_dist = new_dist;
            l_opt = l;
            r_opt = r;
        }

        if (k - sum > 0)
        {
            sum += cards[++r];
        }
        else
        {
            sum -= cards[l++];
        }

        if(l >= n || r >= n){
            break;
        }

        //22 59 95 14 62 43 89 27 57 81 90 49 13 38 96 66 98 68 96 11 29
    }
    std::cout << l_opt << " " << r_opt << std::endl;
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