#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Finite_vertices_iterator Vertex_Iterator;

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

    //No testcase left
    if (n == 0)
    {
        return 0;
    }

    //Dish coordiantes
    int l, b, r, t;
    std::cin >> l >> b >> r >> t;

    //Use triangulation to compute the shortest distance from one germ to another
    //Distance can be used to compute the moment of death (as one germ dies as sonn as it hits another germ (which also grows simultaneously))

    //Use tutorial slide code for the triangulation setup
    // read points
    std::vector<K::Point_2> pts;
    pts.reserve(n);

    //Store the minimum distance for each germ
    std::map<K::Point_2, double> germ_min_distance;

    for (int i = 0; i < n; ++i)
    {
        double x, y;
        std::cin >> x >> y;
        K::Point_2 point(x, y);
        pts.push_back(point);

        //Compute distance to the boundaries to determine which boundary it hits first
        int dist_l = std::abs(x - l), dist_r = std::abs(x - r), dist_t = std::abs(y - t), dist_b = std::abs(y - b);
        int dist_horizontal = std::min(dist_l, dist_r);
        int dist_vertical = std::min(dist_t, dist_b);

        K::Point_2 boarder_point;
        if (dist_horizontal < dist_vertical)
        {
            if (dist_l < dist_r)
            {
                boarder_point = K::Point_2(l, y);
            }
            else
            {
                boarder_point = K::Point_2(r, y);
            }
        }
        else
        {
            if (dist_t < dist_b)
            {
                boarder_point = K::Point_2(x, t);
            }
            else
            {
                boarder_point = K::Point_2(x, b);
            }
        }
        germ_min_distance.emplace(point, std::sqrt(CGAL::squared_distance(point, boarder_point))*2);
    }
    Triangulation trg;
    trg.insert(pts.begin(), pts.end());

    for (auto it = trg.finite_edges_begin(); it != trg.finite_edges_end(); ++it)
    {
        auto v1 = it->first->vertex((it->second + 1) % 3), v2 = it->first->vertex((it->second + 2) % 3);
        double distance = std::sqrt(CGAL::squared_distance(v1->point(), v2->point()));
        germ_min_distance[v2->handle()->point()] = std::min(germ_min_distance[v2->handle()->point()], distance);
        germ_min_distance[v1->handle()->point()] = std::min(germ_min_distance[v1->handle()->point()], distance);
    }

    std::vector<double> distances;
    for (auto elem : germ_min_distance)
    {
        distances.push_back(elem.second);
    }

    std::sort(distances.begin(), distances.end());
    //Compute the growth time of the germ with shortest distance, the one in the median and the largest distance
    //growth(t) = t² + 0.5; Given distance d: d = t² + 0.5 --> sqrt(d-0.5) = t. If d = 0 <=> t = 0;
    int size = distances.size();

    std::vector<double> sml_dist;
    //We need to take the half as both germ approach towards each other(for boarder distances we first multiplied by 2)
    sml_dist.push_back((distances[0])/2);
    sml_dist.push_back((distances[size / 2])/2);
    sml_dist.push_back((distances[size - 1])/2);
    int count = 0;
    for(auto d: sml_dist){
        if(d == 0){
            std::cout << "0 ";
        }else{
            double time = std::ceil(std::sqrt(d-0.5));
            std::cout << time;
        }
        count++;
        if(count < 3){
            std::cout << " ";
        }
    }
    std::cout << std::endl;


   

    return 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while (testcase())
        ;
    return 0;
}