#include <vector>
#include <iostream>
#include <algorithm>


void testcase()
{
    int n, m, h, w;
    std::cin >> n >> m >> h >> w;

    //fn = free nails, on = occupied nails
    std::vector<std::vector<double>> fn;
    std::vector<std::vector<double>> on;

    for (int i = 0; i < n; i++)
    {
        double x, y;
        std::cin >> x >> y;
        fn.push_back({x, y});
    }

    for (int i = 0; i < m; i++)
    {
        double x, y;
        std::cin >> x >> y;
        on.push_back({x, y});
    }

    //Compute for each free nail, the minimal distance to all other nail
    //Distinct between free and occupied nails, free nails can grow towards each other, while growing to a occupied nail is only onesided
    //Compute minimal distance in terms of height and width

    double min_height = __DBL_MAX__, min_width = __DBL_MAX__;

    for (int i = 0; i < n; i++)
    {
        auto freeNail = fn[i];
        for (int j = 0; j < m; j++)
        {
            auto occNail = on[j];
            double scale_x = (std::abs(occNail[0] - freeNail[0]) - w/2)/w;
            double scale_y = (std::abs(occNail[1] - freeNail[1]) - h/2)/h;


        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while (t-- > 0)
        testcase();
    return 0;
}
