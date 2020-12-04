#include <iostream>
#include <array>
#include <cstdlib>
#include <climits>

void testcase()
{
    int n;
    std::cin >> n;

    int h;
    std::cin >> h;

    int dominos = 1;
    bool finished = false;

   // std::cout << "dominos: " << dominos << " h: " << h << std::endl;

    for (int i = 1; i < n; i++)
    {
        int new_h;
        std::cin >> new_h;

        if (finished)
            continue;

        if (h > 1)
        {
            dominos++;
            if (new_h >= h)
            {
                h = new_h;
            }
            else
            {
                h--;
            }
        }
        else
        {
            finished = true;
        }
   //     std::cout << "dominos: " << dominos << " h: " << h << std::endl;
    }

    std::cout << dominos << std::endl;
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