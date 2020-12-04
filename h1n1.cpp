#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;

int testcase()
{
    int n;
    std::cin >> n;

    if (n == 0)
    {
        return 0;
    }

    //Compute triangulation for infected people, so that we can easily find the nearest vertex for each healty people
    std::vector<K::Point_2> pts_infected;
    pts_infected.reserve(n);
    for (std::size_t i = 0; i < n; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        pts_infected.push_back(K::Point_2(x, y));
    }
    // construct triangulation
    Triangulation t;
    t.insert(pts_infected.begin(), pts_infected.end());

    //Number of "healthy people"
    int m;
    std::cin >> m;

    //Compute if the healty person is far enough from the infected ones. Use function nearest vertex to determine
    //the closet infected people
    for(int i = 0; i < m; i++){
        double x,y, allowed_distance;
        std::cin >> x >> y >> allowed_distance;
        K::Point_2 point(x,y);

        auto nearest_infected_vertex = t.nearest_vertex(point, t.finite_faces_begin());


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