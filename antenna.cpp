#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <vector>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef EK::Point_2 Point;

typedef CGAL::Min_circle_2_traits_2<EK> Traits;
typedef CGAL::Min_circle_2<Traits> Min_Circle;


int testcase()
{
    long n;
    std::cin >> n;

    if (n == 0)
    {
        return 0;
    }

    std::vector<Point> points;

    for (int i = 0; i < n; i++)
    {
        long x, y;
        std::cin >> x;
        std::cin >> y;

        points.push_back(Point(x, y));
        points.
    }

    Min_Circle mc(points.begin(), points.end(), true);
    Traits::Circle circle = mc.circle();
    std::cout << CGAL::sqrt(circle.squared_radius()).longValue()+1 << std::endl;

    return 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while (testcase())
        ;
    return 0;
}