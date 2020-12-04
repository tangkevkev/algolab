#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Finite_edges_iterator Edge_iterator;

int testcase()
{
    int n;
    std::cin >> n;

    if (n == 0)
    {
        return 0;
    }
    //copied the code from the exercise slides for inserting points effectively in the triangulation

    // read points
    std::vector<K::Point_2> pts;
    pts.reserve(n);

    for (int i = 0; i < n; i++)
    {
        int x, y;
        std::cin >> x >> y;
        pts.push_back(K::Point_2(x, y));
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());

    //Delaunay triangles contain the Euclidean Minimum Spanning Tree! (Delaunay property (on the slides))
    //Hence we can find the shortest distance between vertices efficiently

    double min_distance = DBL_MAX;
    //Divide by two as both run towards each other
    for (Edge_iterator f = t.finite_edges_begin(); f != t.finite_edges_end(); ++f)
        min_distance = std::min(min_distance, std::sqrt((t.segment(f).squared_length())) / 2);

    int int_min_distance = min_distance * 100;
    if(int_min_distance < min_distance*100){
        int_min_distance++;
    }
    std::cout << int_min_distance << std::endl;


    return 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while (testcase())
        ;
    return 0;
}