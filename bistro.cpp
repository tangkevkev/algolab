#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;

double floor_to_double(const K::FT &x)
{
    double a = std::floor(CGAL::to_double(x));
    while (a > x)
        a -= 1;
    while (a + 1 <= x)
        a += 1;
    return a;
}

int testcase()
{
    int n;
    std::cin >> n;
    if (n == 0)
        return 0;

    //Slides code for delaunay triangulation
    std::vector<K::Point_2> pts;
    pts.reserve(n);

    for (std::size_t i = 0; i < n; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        pts.push_back(K::Point_2(x, y));
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());

    //Reading possible position
    int m;
    std::cin >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y;
        std::cin >> x >> y;
        auto q = K::Point_2(x, y);

        auto distance = CGAL::squared_distance(q, t.nearest_vertex(q, t.finite_faces_begin())->point());
        std::cout <<std::fixed << std::setprecision(0) << floor_to_double(distance) << std::endl;
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