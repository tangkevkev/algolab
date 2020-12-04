#include <iostream>
#include <array>
#include <cstdlib>
#include <climits>

void testcase()
{
    int n;
    std::cin >> n;

    std::array<int,10> A;
    int sum = 0;
    for(int i = 0; i < n; i++){
        std::cin >> A[i];
        sum += A[i];
    }

    std::cout << sum << std::endl;

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