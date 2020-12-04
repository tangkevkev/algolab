#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

typedef IK::Point_2 IK_Point;
typedef IK::Segment_2 IK_Segment;
typedef IK::Ray_2 IK_Ray;

int testcase()
{
    int n;
    std::cin >> n;

    if (n == 0)
    {
        return 0;
    }

    long x, y, a, b;
    std::cin >> x >> y >> a >> b;

    IK_Ray ray(IK_Point(x, y), IK_Point(a, b));

    bool hits = false;

    for (int i = 0; i < n; i++)
    {
        long r, s, t, u;
        std::cin >> r >> s >> t >> u;

        IK_Segment newSegment(IK_Point(r, s), IK_Point(t, u));

        if (!hits && CGAL::do_intersect(ray, newSegment))
        {
            hits = true;
        }
    }

    if (hits)
    {
        std::cout << "yes" << std::endl;
    }
    else
    {
        std::cout << "no" << std::endl;
    }
    return 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while (testcase())
        ;
}