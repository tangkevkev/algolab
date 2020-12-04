#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Min_circle_2.h>
#include <deque>
#include <algorithm>


typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef EK::Point_2 Point;
typedef CGAL::Min_circle_2_traits_2<EK> Traits;
typedef CGAL::Min_circle_2<Traits> Min_Circle;

int testcase()
{
    int n = 0;
    std::cin >> n;

    if (n == 0)
    {
        return 0;
    }

    std::deque<Point> points;

    for (int i = 0; i < n; i++)
    {
        long x, y;
        std::cin >> x;
        std::cin >> y;

        points.push_back(Point(x, y));
    }

    Min_Circle mc(points.begin(), points.end(), true);
    Traits::Circle circle = mc.circle();

    long min_distance = CGAL::sqrt(circle.squared_radius()).longValue() + 1;
    

    for (int i = 0; i < n; i++)
    {
        Point frontPoint = points.front();
        points.pop_front();

        Min_Circle mc2(points.begin(), points.end(), true);
        circle = mc2.circle();

        auto new_distance = CGAL::sqrt(circle.squared_radius()).longValue() + 1;
        if (min_distance > new_distance)
        {
            min_distance = new_distance;
        }
        points.push_back(frontPoint);
    }
    if (min_distance == 1)
    {
        std::cout << 0 << std::endl;
    }
    else
    {
        std::cout << min_distance << std::endl;
    }
    return 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while (testcase())
        ;
    return 0;
}